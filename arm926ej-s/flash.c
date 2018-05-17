/**flash.c
* This file contains the API for flashes
 */

/* Contain configuration */
#include "mloader.h"
#include "env.h"

#include "hostmux.h"
#include "mhif_regs.h"
#include "qcc_regs.h"
#include "reset.h"
#include "mb3000_regs.h"
#include "exceptions.h"
#include "ioctrl.h"
#include "ddr_regs.h"


#ifdef CONFIG_NOR

/**nor_init
* Initialize MHIF for a 16bits NOR connected to chip select in parameter
* It will configure the MHIF with the slowest timings possible
* and configure the Hostmux. If the size is above 8MB it will use
* chipselect 5 as an extra address line.
 */
int nor_init(void)
{	
	mhif_t *mhif=(mhif_t *)(MERLIN_MHIF_BASE+MERLIN_MHIF_REGS_OFFSET);
	mhifreg_Config_t Config;

	uint8_t cs, a23_cs;
	uint32_t chipsize;

	/* add one to skip over devID */
	env_seek(device_driver_offset[BOOT_DEVICE_NOR] + 1, ENV_SEEK_SET); 
	cs = env_read(1);
	a23_cs = env_read(1);

	/* chip size codes are 0-7, from 4Mb to 512Mb
	*  0x00800000 is size for 4Mb chip */
	chipsize = 0x00100000 << env_read(1);

	/* Set Host interface IO strength */
	ioctrl_set_strength(IOCTRL_GRP_HOSTIF, IOCTRL_SLEWRATE_FASTEST, IOCTRL_DRIVESTRENGTH_12ma);
	/* Remove MHIF from reset */
	reset_clear(RESET_ID_MHIF);
	/* First setup the MHIF for the requested chip-select */
	Config.A.r=0;	/* Default to 0 */
	Config.A.b.AddrBase=0;
	Config.A.b.AddrMask=(~((chipsize-1)>>12)) & 0xFFF;
	Config.A.b.DWB=1;
	Config.A.b.AddrInc=1;
	Config.B.r=0xFFFFFFFF;	/* For timings default to 1 */
	Config.B.b.TOEn=0;
	mhif->Config[cs].A.r=Config.A.r;
	mhif->Config[cs].B.r=Config.B.r;
	mhif->ChipSelectEnable.r= 1<<cs;
	/* Now that the MHIF is properly initialized, configure the HostMux */
	chipselect_enable(cs, CSINTF_MHIF16_CSX);

	if(chipsize > 0x800000)
		chipselect_enable(a23_cs, CSINTF_HADDR_23);

	/* We are now ready, return the boot address */
	return 0;
}

/**nor_load
* Copy data from a NOR to a buffer. Since the bus is 16bits we read 2 byte
* at a time. It is assumed size will be a modulo of 2.
 */
int nor_load_img(uint32_t addr, unsigned char *buf, int size)
{
	int c=size;
	uint16_t val;
	volatile uint16_t *p=(uint16_t *)(MERLIN_MHIF_BASE+addr);

	if(size & 1) {	
		BUG();
		return -EINVAL;
	};
	for(c=0; c<size; c+=2) {	
		/* Stupid compiler does not know about ldrh ???? it uses ldrb twice instead ! */
		asm volatile("\tldrh %0, [%1]\n" : "=r"(val) : "r"(p++));
		buf[c]=val & 0xFF;
		buf[c+1]=(val>>8) & 0xFF;
	};
	return size;
}


#endif


#ifdef CONFIG_NAND

static int nand_badecc_exccb(addr_t instr);
static volatile int mark_as_bad;
/**
* nand_init
* Initialize the NAND controller with conservative timings
 */
int nand_init()
{	
	qccbridge_t *qcc=(qccbridge_t *)MERLIN_QCCBRIDGE_BASE;
	mb3000_nand_t *nand=(mb3000_nand_t *)MERLIN_MB3000_REGS_BASE;
	qccreg_SysConfig_t SysConfig;
	mb3000reg_nand_ctrl_t Control;
	mb3000reg_nand_cmd_t Command;
	uint32_t npages, i;

	uint8_t cs, buswidth;
	uint16_t pagesize;
	uint32_t chipsize;

	/* sets read ptr to start of driver section, value saved during env parse */
	/* add one to skip devID */
	env_seek(device_driver_offset[BOOT_DEVICE_NAND] + 1, ENV_SEEK_SET); 
	cs = env_read(1);
	buswidth = env_read(1);
	pagesize = env_read(2);
	/* chip size codes are 0-7, from 65M to 8G, 
	*  0x00800000 is size for 65M chip */
	chipsize = 0x00800000 << env_read(1);

	/* Set the block hardware configuration */
	SysConfig.r=qcc->SysConfig.r;
	SysConfig.b.nand_flash_reg=1;		/* Set block in NAND mode */
	SysConfig.b.nand_2k_pg_reg=(pagesize==512) ? 0 : 1;
	SysConfig.b.nand_nor_ram_en_reg=1;	/* Enable the RAM used by this IP */
	qcc->SysConfig.r=SysConfig.r;

	npages=chipsize/pagesize;

	dputs("NAND init\n");
	dputs("cs ");dputint(cs);dputs("\n");
	dputs("buswidth ");dputint(buswidth);dputs("\n");
	dputs("pagesize ");dputint(pagesize);dputs("\n");
	dputs("chipsize ");dputhex(chipsize);dputs("\n");
	dputs("npages ");dputint(npages);dputs("\n");

	/* Set Host interface IO strength */
	ioctrl_set_strength(IOCTRL_GRP_HOSTIF, IOCTRL_SLEWRATE_FASTEST, IOCTRL_DRIVESTRENGTH_12ma);
	/* Remove Flash controller from reset */
	reset_clear(RESET_ID_NANDNOR);
	/* Wait for the controller to be ready ... */
	do {	
		Command.r=nand->Command.r;
	} while(Command.b.cmd!=MB3000_NANDCMD_NOP);
	/* Configure the NAND controller */
	Control.r=0;/* default is clear for all fields, then we set the one we need */
	Control.b.se=1;	/* We want ECC */
	if(pagesize>512) {	
		Control.b.c2=1;
		Control.b.i4=1;
	};
	if(npages>65536)	/* With 2 page address cycles we cannot have more than 65536 */
		Control.b.p3=1;	/* pages == 128MB with large pages and 32MB with small pages */

	Control.b.rc=1;				/* Who doesn't ? */
	Control.b.ec=2;				/* All ECC checks are enabled */
	Control.b.eg=2;				/* All ECC checks are enabled */
	Control.b.wp=1;				/* WP# pin is high: we only want to read ! */
	if(buswidth==16) {	
		Control.b.xs=1;
		Control.b.wd=1;
	};
	/* Calculate size field ... */
	for(i=0; i<8; i++)
		if(1<<(i+23)>=chipsize)
			break;

	Control.b.sz=i;
	Control.b.eb=0;
	nand->Control.r=Control.r;
	nand->Timing0.r=env_read(4);
	nand->Timing1.r=env_read(4);
	nand->Timing2.r=env_read(4);
	nand->Timing3.r=env_read(4);
	nand->Timing4.r=env_read(4);
	nand->Timing5.r=env_read(4);

	/* Configure the host mux (MUST BE DONE AFTER NAND CONTROLLER STATE MACHINE IS DONE WITH RESET) */
	chipselect_enable(cs, CSINTF_NAND_CE0);
	/* done */
	return 0;
}

/**nand_check_block
* Check if block is a bad block. To do so this API
* read the Bad Block Information field of the spare area
* for the 2 first pages of the block.
 */
int nand_check_block(uint32_t block)
{
	mb3000_nand_t *nand=(mb3000_nand_t *)MERLIN_MB3000_REGS_BASE;
	volatile unsigned char *nandptr=(unsigned char *)MERLIN_MB3000_DATA_BASE;
	mb3000reg_nand_ctrl_t Control;
	uint32_t page, pagesize, buswidth, val;

	Control.r=nand->Control.r;
	if(Control.b.c2)	/* large pages */
	{	
		pagesize=2048;
		nandptr+=block<<17;	/* block*pageperblk*pagesize */
	}
	else
	{	
		pagesize=512;
		nandptr+=block<<14;	/* block*pageperblk*pagesize */
	};
	if(Control.b.xs) 
		buswidth=16;
	else 
		buswidth=8;

	Control.b.sa=1;
	nand->Control.r=Control.r;
	for(page=0; page<2; page++, nandptr+=pagesize)
	{	
		if((pagesize>512) && (buswidth==16))	/* large page 16bits NAND */
		{	
			val=nandptr[0];
			if(val!=0xFF) 
				return -EFAULT;
			val=nandptr[1];
			if(val!=0xFF) 
				return -EFAULT;
		} 
		else if((pagesize>512) && (buswidth==8))	/* large page 8bits NAND */
		{	
			val=nandptr[0];
			if(val!=0xFF)
				return -EFAULT;
		} 
		else if((pagesize==512) && (buswidth==16))	/* small page 16bits NAND */
		{	
			val=nandptr[11];	/* only 8 bits */
			if(val!=0xFF)
				return -EFAULT;
		} 
		else if((pagesize==512) && (buswidth==8))	/* small page 8bits NAND */
		{	
			val=nandptr[5];
			if(val!=0xFF)
				return -EFAULT;
		};
	};
	return 0;
}

/* Copy a page, if size is bigger than page size it will only copy pagesize byte
* and return the number of bytes copied */
int nand_copy_page(uint32_t block, uint32_t page, unsigned char *buf, int size)
{	
	mb3000_nand_t *nand=(mb3000_nand_t *)MERLIN_MB3000_REGS_BASE;
	volatile unsigned char *nandptr=(unsigned char *)MERLIN_MB3000_DATA_BASE;
	mb3000reg_nand_ctrl_t Control;
	uint32_t c, pagesize, pageperblock;
	int ret;

	/* Configure the NAND controller */
	Control.r=nand->Control.r;
	if(Control.b.c2)	/* large pages */
	{	
		pagesize = 2048;
		pageperblock = 64;
		nandptr += ((block<<6)+page)<<11;
	} 
	else
	{	
		pagesize = 512;
		pageperblock = 32;
		nandptr += ((block<<5)+page)<<9;
	};
	dputs("---- copy_page -----\n");
	dputs("block: ");dputint(block);dputs(" page: ");dputint(page);dputs("\n");
	dputs("src nandptr: ");dputhex(nandptr);
	dputs(" dst buf: ");dputhex(buf);dputs("\n");

	if(page >= pageperblock)
	{	
		BUG();
		return -EINVAL;
	};
	if(size>pagesize)
		size=pagesize;

	
	ret=size;
	/* Select the main area */
	Control.b.sa=0;
	nand->Control.r=Control.r;
	/* A data abort exception will be generated if the NAND controller detect a non
	   recoverable ECC error. We use a callback to handle the situation */
	mark_as_bad=0;
	exception_setcb(EXCEPTION_DATA_ABORT, nand_badecc_exccb);
	/* Copy data from main area (will generate a data abort if ECC bad) */
	for(c=0; c<size; c+=4) 
	{	
		uint32_t val=*(uint32_t *)(nandptr+c);
		if(mark_as_bad)
		{	
			ret=-EFAULT;
			break;
		};
		*buf++=(val>>24) & 0xFF;
		*buf++=(val>>16) & 0xFF;
		*buf++=(val>>8) & 0xFF;
		*buf++=val & 0xFF;
	};
	nandptr+=size;
	/* We don't want to listen to data abort exceptions anymore */
	exception_setcb(EXCEPTION_DATA_ABORT, NULL);
	return ret;
}

/**nand_load
* Copy data from a NAND to a buffer. 
* NOTE: This API assume size is equal or less than a block size.
* It will first check if a block is valid, then copy the data. 
* If an error is encountered (bad block or ECC error), it will jump 
* to the next block. Bad blocks are easy because they should have been 
* marked bad already when the flash was written, so we just skip the bad
* block.  An ECC error is not as easy.  If multiple copies of an image are
* stored in the flash, we will just to the same page in the next copy of 
* the image.  That's why we need to 'size' of the current copy and the
* full size of the image that we are dealing with.
 */
int nand_load_img(uint32_t blk_addr, uint32_t start_page, unsigned char *buf, 
		int size, uint8_t num_copies, uint32_t stride)
{	
	int ret = 0;
	mb3000_nand_t *nand=(mb3000_nand_t *)MERLIN_MB3000_REGS_BASE;
	mb3000reg_nand_ctrl_t Control;
	uint32_t page, pagesize;
	uint32_t block, blocksize, pagesperblock;
	uint32_t nremains;
	uint8_t cur_copy = 1;

	dputs("------ load_img begin -------\n");
	/* Configure the NAND controller */
	Control.r=nand->Control.r;
	if(Control.b.c2) {
		pagesize=2048;	/* large pages */
		pagesperblock=64;
	}
	else {
		pagesize=512;
		pagesperblock=32;
	}

	/* determine what the first block is */
	blocksize = pagesperblock*pagesize;
	block = blk_addr/blocksize;

	/* 
	*  how to determine how many blocks an images takes up
	blocks_per_img = img_size/blocksize;
	if (img_size & blocksize)
		blocks_per_img++;
	}
	 */
	dputs("block: ");dputint(block);dputs(" start_page: ");dputint(start_page);
	dputs(" size: ");dputint(size);dputs("\n");

	/* outer for loop take care of blocks, inner do/while does pages within the blocks */
	for(page=start_page, nremains=size; nremains!=0; block++, page=0) {	

		/* Check for bad block first: look at the first 2 page 
		*  Bad Block Information fields => if not 0xFF BAD */
		if(nand_check_block(block)<0) {	
			warn("Bad block ");
			putint(block);
			warn(". Skip to next block.\n");
			continue;
		};
		/* Block is good, now we start copying pages until we have all we need */

		/* copy a blocks worth of pages */
		do
		{	

			dputs("------ load_img -------\n");
			dputs("block: ");dputint(block);dputs(" page: ");dputint(page);
			dputs(" nremains: ");dputint(nremains);dputs("\n");

			do {
				if ((ret=nand_copy_page(block, page, buf, nremains)) < 0) {

					dputs("Unrecoverable ECC error block ");dputint(block);
					dputs(" page ");dputint(page);dputs("\n");

					cur_copy++;

					/* the layout of our images will be like this
					*  kernel
					*  kernel
					*  initrd
					*  initrd
					*  
					*  each image will be on a block boundry.  if we have 
					*  multiple copies then we already calculated how many 
					*  block we have to skip if we get an ecc error, so just
					*  do it!
					 */
					if (cur_copy <= num_copies) {
						debug("Skipping to next available copy\n");
						block += stride;
						debug("Now try block ");dputint(block);
						debug(" page ");dputint(page);debug("\n");
					}
					else {
						error("No valid copies remain, imminent failure\n");
					}
				}
			} while (ret < 0 && cur_copy <= num_copies);

			/* if true, we ran out of good copies, so get out of here! */
			if (ret < 0) {
				size = ret;
				break;
			}
			else {
				nremains -= ret;
				buf += pagesize;
				page++;
			}

		} while(page < pagesperblock && nremains != 0);
	};
	/* done, we return size */
	return size;
}

static int nand_badecc_exccb(addr_t instr)
{	
	mark_as_bad=1;
	/* Must skip the ECC error, we don't handle it */
	return 0;
}
#endif

#if defined(CONFIG_NAND) || defined(CONFIG_NOR)
int flash_load(void)
{
	int ret = 0;

#ifdef CONFIG_NAND
	/* for NAND */
	mb3000_nand_t *nand=(mb3000_nand_t *)MERLIN_MB3000_REGS_BASE;
	mb3000reg_nand_ctrl_t Control;
	uint32_t pagesize;
#endif
	/* shared */
	uint8_t i, img_copies;
	uint32_t img_src, img_dst, *img_size, img_stride;
	image_header_t *hdr = NULL;

	/* 0 for the kernel, 1 for initrd(if it exist) */
	for (i=0;i<2;i++) {

		if (i == 0) {
			img_src = bootparams_defs.kern_addr;
			img_dst = linux_defs.kern_addr;
			img_size = &bootparams_defs.kern_size;
			img_copies = bootparams_defs.kern_copies;
			img_stride = bootparams_defs.kern_stride;
			dputs("\nloading kernel from ");
		}
		else {
			img_src = bootparams_defs.initrd_addr;
			img_dst = linux_defs.initrd_addr;
			img_size = &bootparams_defs.initrd_size;
			img_copies = bootparams_defs.initrd_copies;
			img_stride = bootparams_defs.initrd_stride;
			dputs("\nloading initrd from ");
		}
		if (bootparams_defs.devID == BOOT_DEVICE_NAND)
			dputs("NAND");
		else
			dputs("NOR");

		dputs("(");
		dputhex(img_src);
		dputs(") into DDR(");
		dputhex(img_dst);
		dputs(")\n");

		/* if no initrd then we are out of here */
		if(img_dst == 0)
			break;

		if (bootparams_defs.devID == BOOT_DEVICE_NAND) {
#ifdef CONFIG_NAND
			/* configure the nand controller */
			Control.r=nand->Control.r;
			if(Control.b.c2) 
				pagesize=2048;	/* large pages */
			else 
				pagesize=512;

			/* load the first page so i can read the header */
			ret = nand_load_img(img_src, 0, 
					(uint8_t*)img_dst,
					pagesize, 
					img_copies, img_stride); 
#endif
		}
		else {
#ifdef CONFIG_NOR
			/* copy just the img header */
			ret = nor_load_img(img_src, 
					(uint8_t*)img_dst, 
					sizeof(image_header_t));
#endif
		}

		if (ret <= 0)
			return(-1);

		hdr = (image_header_t*)img_dst;
		if (SWAP32(hdr->ih_magic) != IH_MAGIC) {
			error("Bad Magic Number\n");
			//error("Bad Magic Number: ");puthex(hdr->ih_magic);error("\n");
			return(-1);
		}
		*img_size = SWAP32(hdr->ih_size);
		dputs("Image name: ");dputs(hdr->ih_name);dputs("\n");
		dputs("Image size: ");dputint(*img_size);dputs("\n");

		/* this is important, so need to check if it is the kernel */
		if (bootparams_defs.kern_addr == img_src && img_dst != SWAP32(hdr->ih_ep)) {
			error("Kernel entry point != environment setting\n");
			return(-1);
		}

		if (bootparams_defs.devID == BOOT_DEVICE_NAND) {
#ifdef CONFIG_NAND
			/* ok, now move the first page to it's final location, skipping the hdr */
			memcpy((char*)img_dst,
					(char*)(img_dst+sizeof(image_header_t)),
					pagesize-sizeof(image_header_t));

			/* now copy everything remaining, adjust the addresses and size to 
			*  skip the first page
			 */
			ret = nand_load_img(img_src, 1,
					(uint8_t*)img_dst+(pagesize-sizeof(image_header_t)),
					*img_size-(pagesize-sizeof(image_header_t)),
					img_copies, img_stride);
#endif
		}
		else {
#ifdef CONFIG_NOR
			/* now copy everything except the img header */
			ret = nor_load_img(img_src+sizeof(image_header_t),
					(uint8_t*)img_dst,
					*img_size);
#endif
		}

		if (ret <= 0)
			return(-1);
	}

	return(ret);
}

#endif
