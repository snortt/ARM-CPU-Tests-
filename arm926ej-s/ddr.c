/**ddr.c
 * This file contains memory access APIs and DDR code
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
#include "qcc.h"
#include "qcc_regs.h"

/* 
*  At this time we will only used this code for relocation of 
*  the images.  We will have a restriction in place that addresses
*  must be above the 1M boundry.  This is because the kernel maps in 
*  the first meg of memory and expect to find the boot args there.  
*  Therefor, we don't have to worry about ever accessing memory below
*  the 16K boundry via the first bridge(doing this would access the ICTM
*  instead of the DDR)
*/
void ddrcopy(uint32_t src, uint32_t dst, uint32_t size)
{

    /* XXX no boundry checking here, we always do 8 words at a
    *  time
    */
    asm volatile ( 
	    "mov r0, %0\n\t"  	// src
	    "mov r1, %1\n\t"  	// dst
	    "mov r2, %2\n\t"    //size, 
	    "add r2, r0, r2\n\t" //end addr
	"1:\n\t"
	    "ldmia   r0!, {r3-r10}\n\t"
	    "stmia   r1!, {r3-r10}\n\t"
	    "cmp     r0, r2\n\t"
	    "ble     1b"
	    : 
	    :"r" (src), "r" (dst), "r" (size)
	    :"r0", "r1", "r2", "r3","r4","r5","r6","r7","r8","r9","r10"
	);
}

#if defined(CONFIG_DDR) || defined(CONFIG_JTAG)
int ddr_load_img(uint32_t img_src, uint32_t img_dst)
{
    uint32_t size;
    image_header_t *hdr = NULL;

    /* if we had space we could do like u-boot which is nice!
    *  ## Booting image at 01050000 ...
	   Image Name:   Linux 2.6.20.mobi.merlin.r853M i
	   Created:      2007-08-10   1:01:59 UTC
	   Image Type:   ARM Linux Kernel Image (uncompressed)
	   Data Size:    1796320 Bytes =  1.7 MB
	   Load Address: 00108000
	   Entry Point:  00108000
		OK
		## Loading Ramdisk Image at 01450000 ...
	   Image Name:   initrd merlin-r853M
	   Created:      2007-08-10   0:41:36 UTC
	   Image Type:   ARM Linux RAMDisk Image (uncompressed)
	   Data Size:    15728640 Bytes = 15 MB
	   Load Address: 00000000
	   Entry Point:  00000000

   */
    /* extract the info from the header, just go via the dma 
    *  bridge to avoid any odd addressing issues
	 */
	hdr = (image_header_t*)(img_src);
	if (SWAP32(hdr->ih_magic) != IH_MAGIC) {
		error("Bad Magic Number\n");
		//error("Bad Magic Number: ");puthex(hdr->ih_magic);error("\n");
		return(-1);
	}
	dputs("Image name: ");dputs(hdr->ih_name);dputs("\n");

	size = SWAP32(hdr->ih_size);
	dputs("Image size: ");dputint(size);dputs("\n");
	
	/* Note: we shouldn't check if the kernel is loaded at the right
	 * address because the zImage may not be and this is fine */

	/* skip over the header of 64 bytes */
	ddrcopy(img_src+sizeof(image_header_t), img_dst, size);

	return(size);
}

int ddr_load(void)
{
	int ret;

	/* only handle uncompressed, img files for now */
	dputs("\nLoading kernel from DDR(");
	dputhex(bootparams_defs.kern_addr);
	dputs(") into DDR(");
	dputhex(linux_defs.kern_addr);
	dputs(")\n");

	ret = ddr_load_img(bootparams_defs.kern_addr, linux_defs.kern_addr);
	if (ret > 0)
		bootparams_defs.kern_size = ret;

	if (ret > 0 && linux_defs.initrd_addr != 0) {
		dputs("\nLoading initrd from DDR(");
		dputhex(bootparams_defs.initrd_addr);
		dputs(") into DDR(");
		dputhex(linux_defs.initrd_addr);
		dputs(")\n");

		ret = ddr_load_img(bootparams_defs.initrd_addr, linux_defs.initrd_addr);
		if (ret > 0)
			bootparams_defs.initrd_size = ret;
	}

	return(ret);
}

#endif

