/**main.c
* This file contains main which is the BootROM C code entry point.
 */

/*******************************************************************************
* 
* The content of this file or document is CONFIDENTIAL and PROPRIETARY
* to Mobilygen Corp.  It is subject to the terms of a
* License Agreement between Licensee and Mobilygen Corp.
* restricting among other things, the use, reproduction, distribution
* and transfer.  Each of the embodiments, including this information and
* any derivative work shall retain this copyright notice.
* 
* Copyright 2007 Mobilygen Corp.
* All rights reserved.
* 
******************************************************************************/

#include "mloader.h"
#include "env.h"
#include "ddr_regs.h"
#include "uart.h"
#include "gpio.h"
#include "memtest.h"
#include "gpio_regs.h"

#include "mach-types.h"
#include "setup.h"

/**main_stack
* Stack for the loader
 */
int main_stack[MAINSTACK_SIZE/sizeof(int)];

/* very simple so we don't take up extra space */
struct bootdevice {
	int (*init)();
	int (*load)();
};

struct bootdevice boot_devs[] = {
#ifdef CONFIG_DDR
	{
		.init = NULL,
		.load = ddr_load,
	},
#else
	{
		.init = NULL,
		.load = NULL,
	},
#endif

#ifdef CONFIG_NAND
	{
		.init = nand_init,
		.load = flash_load,
	},
#else
	{
		.init = NULL,
		.load = NULL,
	},
#endif

#ifdef CONFIG_NOR
	{
		.init = nor_init,
		.load = flash_load,
	},
#else
	{
		.init = NULL,
		.load = NULL,
	},
#endif

#ifdef CONFIG_XMODEM
	{
		.init = xmodem_init,
		.load = xmodem_load,
	},
#else
	{
		.init = NULL,
		.load = NULL,
	},
#endif

/* usb and enet are just place holder for now */
#ifdef CONFIG_USB
	{
		.init = NULL,
		.load = NULL,
	},
#else
	{
		.init = NULL,
		.load = NULL,
	},
#endif

#ifdef CONFIG_ENET
	{
		.init = NULL,
		.load = NULL,
	},
#else
	{
		.init = NULL,
		.load = NULL,
	},
#endif

#ifdef CONFIG_MEMTEST
	{
		.init = memtest_init,
		.load = NULL,
	},
#else
	{
		.init = NULL,
		.load = NULL,
	},
#endif

#ifdef CONFIG_JTAG
	{
		.init = NULL,
		.load = ddr_load,
	},
#else
	{
		.init = NULL,
		.load = NULL,
	},
#endif

};

void *bi_boot_params=MERLIN_DMABRIDGE_BASE|0x100;
static struct tag *params;

static void setup_start_tag()
{
	params = (struct tag *) bi_boot_params;

	/* tag header is 2 32-bit words */
	/* tag_core is 3 32-bit words */
	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size(tag_core);
	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;
	params = tag_next(params);
}

static void setup_commandline_tag()
{
	char *p;

	/* tag header is 2 32-bit words */
	/* cmdline tag is strllen of cmdline */

	/* eat leading white space */
	for (p = linux_defs.cmdline; *p == ' '; p++);

	/* skip non-existent command lines so the kernel will still
	* use its default command line.
	 */
	if (*p == '\0')
		return;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof(struct tag_header) + strlen(p) + 1 + 4) >> 2;

	strcpy(params->u.cmdline.cmdline, p);
	params = tag_next(params);
}

static void setup_initrd_tag()
{
	/* tag header is 2 32-bit words */
	/* tag_initrd is 2 words */
	params->hdr.tag = ATAG_INITRD2;
	params->hdr.size = tag_size(tag_initrd);
	params->u.initrd.start = linux_defs.initrd_addr;
	params->u.initrd.size  = bootparams_defs.initrd_size;
	params = tag_next(params);
}

static void setup_end_tag()
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}

/* 
*  the kern should be relocated into the final location by here
*  so setup the tags structures and jump!
 */
int boot_linux()
{

	void (*theKernel)(int zero, int arch, uint32_t params);

	theKernel = (void (*)(int, int, uint32_t))linux_defs.kern_addr;

	setup_start_tag();
	setup_commandline_tag();
	setup_initrd_tag();
	setup_end_tag();

	/* 
	*  NOTE: the following comment is useful so I left it but now the boot
	* params are always in DDR to save BSS
	*  the kernel can't see the tags in the DTCM when calling setup_arch
	*  from start_kernel.  I believe, this early in the process the pages tables
	*  are not setup enough to access the DTCM.  However, if I look at 
	*  create_page_tables in head.S the following comment appears:
	*
	*  "Then map first 1MB of ram in case it contains our boot params."
	*
	*  also, copy via the second bridge since I have not disabled the 
	*  ICTM yet
	*
	*  also also, the board definition in board-merlin puts the boot_params
	*  at MMU_BRIDGE_ARM_BASE + 0x100
	 */
	/*
	memset((void*)(MERLIN_DMABRIDGE_BASE|0x100), 0x0, sizeof(bi_boot_params));
	memcpy((void*)(MERLIN_DMABRIDGE_BASE|0x100), bi_boot_params, sizeof(bi_boot_params));
	*/
	
	/* disable ICTM */
	asm volatile(
			"mrc p15, 0, r1, c9, c1, 1\n\t"
			"bic r1, r1, #1\n\t"
			"mcr p15, 0, r1, c9, c1, 1");

	debug("\nMerlinloader booting linux from ");dputhex(linux_defs.kern_addr);
	debug(", initrd at ");dputhex(linux_defs.initrd_addr);debug("\n\n");
	theKernel(0, MACH_TYPE_MERLIN, (uint32_t)(MERLIN_DMABRIDGE_BASE|0x100));

	return(0);
}

bootrom_config_t get_config(void)
{       
	bootrom_config_t config;
	dwc_gpio_t *gpio;

	/* We configure the CONFIG_* pins as inputs with pull-ups */
	gpio_select(GPIOFUNC_GPIO_IN_PULLUP, CONFIG_GPIO_BANK, CONFIG_GPIO_MASK);
	/* wait 1us for the pull-ups to pull the pins if they are floating */
	udelay(1);
	/* Now read the configuration and save it */
	//config=gpio_bank_read(CONFIG_GPIO_BANK, CONFIG_GPIO_MASK)>>CONFIG_0_GPIO_SHIFT;
	// hack in hardcode bank_read so can comment out code for space */
	gpio=(dwc_gpio_t *)MERLIN_GPIOBANK2_BASE;
	config = ((gpio->extdata & CONFIG_GPIO_MASK) >> CONFIG_0_GPIO_SHIFT);
	/* Release the GPIO pull-ups */
	gpio_select(GPIOFUNC_GPIO_IN, CONFIG_GPIO_BANK, CONFIG_GPIO_MASK);
	/* done */
	switch (config) {
		case CONFIG_LOAD_NAND_CS1_08L01G:
		case CONFIG_LOAD_NAND_CS1_08L02G:
		case CONFIG_LOAD_NAND_CS1_16L01G:
		case CONFIG_LOAD_NAND_CS1_16L02G:
		case CONFIG_LOAD_NAND_CS1_08S256M:
		case CONFIG_LOAD_NAND_CS1_08S512M:
			return BOOT_DEVICE_NAND;
			break;
		case CONFIG_LOAD_USB_PID0:
		case CONFIG_LOAD_USB_PID1:
			return BOOT_DEVICE_USB;
			break;
			//case CONFIG_LOAD_USB_SPIID:
			//case CONFIG_LOAD_SPI:
		case CONFIG_LOAD_BOOTP:
			return BOOT_DEVICE_ENET;
			break;
		case CONFIG_LOAD_XMODEM:
			return BOOT_DEVICE_XMODEM;
			break;
		case CONFIG_BOOT_DDR:
			return BOOT_DEVICE_DDR;
			break;
		case CONFIG_LOAD_NOR_CS0:
		case CONFIG_BOOT_NOR_CS0_16MB:
			return BOOT_DEVICE_NOR;
			break;
		case CONFIG_NONE:
		case CONFIG_BOOT_DISABLE:
		default:
			/* shut it down ! */
			asm volatile ("mcr p15, 0, %0, c7, c0, 4\n" : : "r" (0) );
			break;
	}
	return(0);
}

/**
* merlinloader C code entry point. main is called from start.S.
* \return NEVER RETURNS
 */
addr_t merlinloader_main(void)
{	
	int ret = 0;
	struct bootdevice *bootdev;

	/* if there is no env, don't init it but don't ask me how it's 
	*  going to work if there is no env!
	 */
	if (MERLINLOADER_MAGIC_MARKER == env_read(4)) {
		if (env_init() < 0) {
			asm volatile ("mcr p15, 0, %0, c7, c0, 4\n" : : "r" (0) );
		}
	}
	else {
		/* no env found, bad news! */
		/* Put ARM in low power mode, should never wake up and if it does reboot */
		asm volatile ("mcr p15, 0, %0, c7, c0, 4\n" : : "r" (0) );
	}

	/* try to init the uart to the default, will return if a SYSTEM section 
	*  was found during the env init
	 */
	uart_init(CONSOLE_BAUDRATE, 
			CONSOLE_NBITS, 
			CONSOLE_PARITY, 
			CONSOLE_BITSTOP, 
			0);

	//debug("\n&envstart = ");dputhex((uint32_t)&_envstart);debug("\n");
	//info("Merlinloader boot device ");puthex(bootparams_defs.devID);info("\n");
	
	/* if we found a driver section for a memtest we will run it now because
	*  it may just be a basic memory test and we need to run it before booting.
	*  if it is a full memtest init will never return.  the type of test
	*  is decided during configuration.
	*/
#ifdef CONFIG_MEMTEST
	if (bootparams_defs.run_memtst) {
		bootdev = &boot_devs[BOOT_DEVICE_MEMTEST];
		/* prepares the device, unless it's DDR which we assume is ready */
		if (bootdev->init != NULL)
			ret = bootdev->init();
	}
#endif

	/*info("\nMboot start... bootdevice ID ");*/
	info("\nCarregando mboot... bootdevice ID ");
	/* if multidevice config, read the LORs */
	if (bootparams_defs.devID == BOOT_DEVICE_QUERY) {
		bootparams_defs.devID = get_config();
		//info("Query boot device got: ");puthex(bootparams_defs.devID);info("\n");

	}
	puthex(bootparams_defs.devID);info("\n");

	if ((device_bootparam_offset[bootparams_defs.devID] == 0x0)) {
		/* can't boot if device is not defined !! */
		error("FATAL: No bootparams section\n");
		asm volatile ("mcr p15, 0, %0, c7, c0, 4\n" : : "r" (0) );
	}

	switch (bootparams_defs.devID) {
		case BOOT_DEVICE_XMODEM:
		case BOOT_DEVICE_ENET: /* maybe? */
		case BOOT_DEVICE_MEMTEST:
			break;
		default:
			/*
			   case BOOT_DEVICE_DDR:
			   case BOOT_DEVICE_NAND:
			   case BOOT_DEVICE_NOR:
			   case BOOT_DEVICE_USB:
			 */
			env_seek(device_bootparam_offset[bootparams_defs.devID], ENV_SEEK_SET); 
			env_read(1); /* skip past deviceID */
			bootparams_defs.kern_addr = env_read(4);
			bootparams_defs.kern_type = env_read(1);
			bootparams_defs.kern_copies = env_read(1);
			bootparams_defs.kern_stride = env_read(2);
			bootparams_defs.initrd_addr = env_read(4);
			bootparams_defs.initrd_type = env_read(1);
			bootparams_defs.initrd_copies = env_read(1);
			bootparams_defs.initrd_stride = env_read(2);
			break;
	}
#ifdef CONFIG_JTAG
	if (bootparams_defs.devID == BOOT_DEVICE_JTAG) {
		info("\nEnter the 'halt' command on the jtag\n");
		info("load kernel image into address: ");
		puthex(bootparams_defs.kern_addr);
		info("\nload initrd image into address: ");
		puthex(bootparams_defs.initrd_addr);
		info("\nWhen complete write 0x1 to address ");
		puthex(MERLIN_DMABRIDGE_BASE);
		info("\nand enter 'go' command on the jtag\n");

		*(int*)MERLIN_DMABRIDGE_BASE = 0;
		while (*(int*)MERLIN_DMABRIDGE_BASE == 0)
			udelay(1000000);
	}
#endif
	/*
	   fputs("kern_addr ");fputhex(bootparams_defs.kern_addr);fputs("\n");
	   fputs("kern_type ");fputhexb(bootparams_defs.kern_type);fputs("\n");
	   fputs("kern_copies ");fputhexb(bootparams_defs.kern_copies);fputs("\n");
	   fputs("kern_stride ");fputhexb(bootparams_defs.kern_stride);fputs("\n");
	   fputs("initrd_addr ");fputhex(bootparams_defs.initrd_addr);fputs("\n");
	   fputs("initrd_type ");fputhexb(bootparams_defs.initrd_type);fputs("\n");
	   fputs("initrd_copies ");fputhexb(bootparams_defs.initrd_copies);fputs("\n");
	   fputs("initrd_stride ");fputhexb(bootparams_defs.initrd_stride);fputs("\n");
	 */

	/* 
	*  the devID is the index into the table so the boot_devs table must
	*  be layed out exactly to match the defintions of boot_device_t defined
	*  in cfg2env.c tool 
	 */
	bootdev = &boot_devs[bootparams_defs.devID];

	/* prepares the device, unless it's DDR which we assume is ready */
	if (bootdev->init != NULL)
		ret = bootdev->init();

	if (bootdev->load == NULL) {
		error("FATAL: No device load function\n");
		asm volatile ("mcr p15, 0, %0, c7, c0, 4\n" : : "r" (0) );
	}

	/* 
	*  load data from device to DDR, ret will be size
	*  of last image loaded 
	 */
	if (ret >= 0)
		ret = bootdev->load();

	if (ret > 0)
		boot_linux();

	/* never returns */
	return ret; 
}

