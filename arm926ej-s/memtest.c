/**********************************************************************
*
* Filename:    memtest.c
* 
* Description: General-purpose memory testing functions.
*
* Notes:       This software can be easily ported to systems with
*              different data bus widths by redefining 'datum'.
*
* 
* Copyright (c) 1998 by Michael Barr.  This software is placed into
* the public domain and may be used for any purpose.  However, this
* notice must not be changed or removed and no warranty is either
* expressed or implied by its publication or distribution.
**********************************************************************/

#include "memtest.h"
#include "debug.h"
#include "env.h"
#include "ddr_regs.h"

void CP15_c7(void);

//#undef VERBOSE_MEMTEST

//#if defined(CONFIG_MEMTEST)

/**********************************************************************
*
* Function:    memtest_init()
*
* Description: Run a full strength memory test
*
* Returns:     0 if ok, a negative value otherwise
*
**********************************************************************/
void memtest_init()
{	
	//unsigned long memtest_start=0x30010000;	/* Those test are doing word accesses, using 0x30000000 guarantee the byte order is maintained */
	//unsigned long memtest_size=0;
	unsigned long memtest_start=0x30010000;
	unsigned long memtest_size=0x08000000; /* 128MB  */
	unsigned long memt_start;

	/* add one to skip devID */
	//env_seek(device_driver_offset[BOOT_DEVICE_MEMTEST]+1, ENV_SEEK_SET); 
	//memtest_size = env_read(4);
	//memtest_size -= memtest_start & 0x07FFFFFF;
	memtest_size -= memtest_start & (memtest_size - 1);
	debug_puts("\nMBOOT: running memory test of ");
	putint(memtest_size);
	debug_puts("B please wait....\n");
	debug_puts("\nRunning Data bus connectivity test:\n");
	memt_start=memtest_start;
	memTestDataBus((datum*)memt_start);
	debug_puts("\nRunning Address bus connectivity test:\n");
	memt_start = memtest_start;
	memTestAddressBus((datum*)memt_start, memtest_size);
	debug_puts("\nRunning Device memory test:\n");
	memt_start = memtest_start;
	memTestDevice((datum*)memt_start, memtest_size);

//#ifdef CONFIG_FULL_MEMTEST
	debug_puts("\nRunning signal integrity test:\n");
	memTestSSO((uint32_t *)memtest_start, memtest_size);
	debug_puts("\nRunning reliability test:\n");
	memTestBurst((uint32_t *)memtest_start, memtest_size);
	debug_puts("\nMemory test completed\n");
//	asm volatile ("mcr p15, 0, %0, c7, c0, 4\n" : : "r" (0) );
	CP15_c7();
//#else
	//debug_puts("\nMemory test completed\n");
//#endif

	//return 0;
}


/**********************************************************************
*
* Function:    memTestDataBus()
*
* Description: Test the data bus wiring in a memory region by
*              performing a walking 1's test at a fixed address
*              within that region.  The address (and hence the
*              memory region) is selected by the caller.
*
* Notes:       
*
* Returns:     0 if the test succeeds.  
*              A non-zero result is the first pattern that failed.
*
**********************************************************************/
datum memTestDataBus(volatile datum *address)
{
	datum pattern;

	/*
	* Perform a walking 1's test at the given address.
	 */
	debug_puts("Starting memTestDataBus... ");
	for (pattern = 1; pattern != 0; pattern <<= 1)
	{
		/*
		* Write the test pattern.
		 */
		*address = pattern;

		/*
		* Read it back (immediately is okay for this test).
		 */
		if (*address != pattern) 
		{
			debug_puts("failed!\n");
			return (pattern);
		}
	}

	debug_puts("passed!\n");
	return (0);

}   /* memTestDataBus() */


/**********************************************************************
*
* Function:    memTestAddressBus()
*
* Description: Test the address bus wiring in a memory region by
*              performing a walking 1's test on the relevant bits
*              of the address and checking for aliasing. This test
*              will find single-bit address failures such as stuck
*              -high, stuck-low, and shorted pins.  The base address
*              and size of the region are selected by the caller.
*
* Notes:       For best results, the selected base address should
*              have enough LSB 0's to guarantee single address bit
*              changes.  For example, to test a 64-Kbyte region, 
*              select a base address on a 64-Kbyte boundary.  Also, 
*              select the region size as a power-of-two--if at all 
*              possible.
*
* Returns:     NULL if the test succeeds.  
*              A non-zero result is the first address at which an
*              aliasing problem was uncovered.  By examining the
*              contents of memory, it may be possible to gather
*              additional debug_putsrmation about the problem.
*
**********************************************************************/
datum *memTestAddressBus(volatile datum *baseAddress, unsigned long nBytes)
{
	unsigned long addressMask = (nBytes/sizeof(datum) - 1);
	unsigned long offset;
	unsigned long testOffset;

	datum pattern     = (datum) 0xAAAAAAAA;
	datum antipattern = (datum) 0x55555555;

	/*
	* Write the default pattern at each of the power-of-two offsets.
	 */
	debug_puts("Starting memTestAddressBus... ");
	for (offset = 1; (offset & addressMask) != 0; offset <<= 1)
	{
		baseAddress[offset] = pattern;
	}

	/* 
	* Check for address bits stuck high.
	 */
	testOffset = 0;
	baseAddress[testOffset] = antipattern;

	for (offset = 1; (offset & addressMask) != 0; offset <<= 1)
	{
		if (baseAddress[offset] != pattern)
		{
			debug_puts("failed!\n");
			return ((datum *) &baseAddress[offset]);
		}
	}

	baseAddress[testOffset] = pattern;

	/*
	* Check for address bits stuck low or shorted.
	 */
	for (testOffset = 1; (testOffset & addressMask) != 0; testOffset <<= 1)
	{
		baseAddress[testOffset] = antipattern;

		if (baseAddress[0] != pattern)
		{
			debug_puts("failed!\n");
			return ((datum *) &baseAddress[testOffset]);
		}

		for (offset = 1; (offset & addressMask) != 0; offset <<= 1)
		{
			if ((baseAddress[offset] != pattern) && (offset != testOffset))
			{
				return ((datum *) &baseAddress[testOffset]);
			}
		}

		baseAddress[testOffset] = pattern;
	}

	debug_puts("passed!\n");
	return (NULL);

}   /* memTestAddressBus() */


/**********************************************************************
*
* Function:    memTestDevice()
*
* Description: Test the integrity of a physical memory device by
*              performing an increment/decrement test over the
*              entire region.  In the process every storage bit 
*              in the device is tested as a zero and a one.  The
*              base address and the size of the region are
*              selected by the caller.
*
* Notes:       
*
* Returns:     NULL if the test succeeds.
*
*              A non-zero result is the first address at which an
*              incorrect value was read back.  By examining the
*              contents of memory, it may be possible to gather
*              additional debug_putsrmation about the problem.
*
**********************************************************************/
datum *memTestDevice(volatile datum *baseAddress, unsigned long nBytes)	
{
	unsigned long offset;
	unsigned long nWords = nBytes / sizeof(datum);
	datum memdata;

	datum pattern;
	datum antipattern;

	/*
	* Fill memory with a known pattern.
	 */
	debug_puts("Starting memTestDevice phase 1... ");
	for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
	{
		baseAddress[offset] = pattern;
	}

	/*
	* Check each location and invert it for the second pass.
	 */
	for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
	{
		memdata = baseAddress[offset];
//#if 0
		if (memdata != pattern) {
			debug_puts("pattern match failed @ offset ");
			puthex(offset);
			debug_puts("\n  expected ");puthex(pattern);
			debug_puts(" got ");puthex(memdata);debug_puts("\n");
//#else
	//	if (baseAddress[offset] != pattern) {
	//		return ((datum *) &baseAddress[offset]);
//#endif
		}

		antipattern = ~pattern;
		baseAddress[offset] = antipattern;
	}

	/*
	* Check each location for the inverted pattern and zero it.
	 */
	debug_puts("passed.\nStarting phase 2... ");
	for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
	{
		antipattern = ~pattern;
		memdata = baseAddress[offset];
//#if 0
		if (memdata != antipattern) {
			debug_puts("anti-pattern match failed @ offset ");
			puthex(offset);
			debug_puts("\n  expected ");puthex(antipattern);
			debug_puts(" got ");puthex(memdata);debug_puts("\n");
		}
//#else
//		if (baseAddress[offset] != antipattern)
//			return ((datum *) &baseAddress[offset]);
//#endif
	}

	debug_puts("passed!\n");
	return (NULL);

}   /* memTestDevice() */


//#ifdef CONFIG_FULL_MEMTEST
/**********************************************************************
*
* Function:    memTestSSO()
*
* Description: Test worst case switching scenario. This test tries
*              to catch eventual board coupling or noise issues by
*              looking at the effect on one DQ of switching all the
*              other DQs. For each DQ the test will scan the whole
*              nBytes with the following tests:
*              -DQX toggle opposite to all others.
*              -DQX stays at 0 while all other DQs toggle.
*              -DQX stays at 1 while all other DQs toggle.
*
* Notes:       This test is specific to MG3500 architecture. It requires
*              at least burstSize*busWidth>>3 bytes of space at baseAddress
*              to be effective.
*
* Returns:     Number of bad DQ found.
*
*              This test will display an debug_puts message and return
*              the number of debug_putss it found.
*
**********************************************************************/
int memTestSSO(volatile uint32_t *baseAddress, unsigned long nBytes)
{	
//	int nwrongdq=0;
//	int dq;
//
//	for(dq=0; dq<32; dq++)
//	{	uint32_t pattern[8],patternrd[8];	/* On MG3500 data are 64bits inside the memory controller */
//		volatile uint32_t *p;
//		int pattern_count;
//		int ndqdebug_putss=0;
//		
//		debug_puts("Test SSO effect on DQ");
//		putint(dq);
//		debug_puts(" ... ");
//		for(pattern_count=0; pattern_count<6; pattern_count++)
//		{	int npatdebug_putss=0;
//			/* For optimization purpose the following code has been
//			 * condensed. This code is here for reference 
//			 */
//#if 0
//			switch(pattern_count)
//			{	case 0:	/* DQX toggle opposite to all others */
//				{	int i;
//					for(i=0; i<8; i+=2)
//					{	pattern[i]=0x00FF00FF ^ (dq<16 ? 0 : (0x101<<(dq-16)));
//						pattern[i+1]=0x00FF00FF ^ (dq>=16 ? 0 : (0x101<<dq));
//					};
//					break;
//				}
//				case 1:	/* we do the same but on a different beat */
//				{	int i;
//					for(i=0; i<8; i+=2)
//					{	pattern[i]=0xFF00FF00 ^ (dq<16 ? 0 : (0x101<<(dq-16)));
//						pattern[i+1]=0xFF00FF00 ^ (dq>=16 ? 0 : (0x101<<dq));
//					};
//					break;
//				}
//				case 2:	/* DQX stays at 0 while all other DQs toggle. */
//				{	int i;
//					for(i=0; i<8; i+=2)
//					{	pattern[i]=0x00FF00FF & (~(dq<16 ? 0 : (0x101<<(dq-16))));
//						pattern[i+1]=0x00FF00FF & (~(dq>=16 ? 0 : (0x101<<dq)));
//					};
//					break;
//				}
//				case 3:	/* we do the same but on a different beat */
//				{	int i;
//					for(i=0; i<8; i+=2)
//					{	pattern[i]=0xFF00FF00 & (~(dq<16 ? 0 : (0x101<<(dq-16))));
//						pattern[i+1]=0xFF00FF00 & (~(dq>=16 ? 0 : (0x101<<dq)));
//					};
//					break;
//				}
//				case 4:	/* DQX stays at 1 while all other DQs toggle. */
//				{	int i;
//					for(i=0; i<8; i+=2)
//					{	pattern[i]=0x00FF00FF | (dq<16 ? 0 : (0x101<<(dq-16)));
//						pattern[i+1]=0x00FF00FF | (dq>=16 ? 0 : (0x101<<dq));
//					};
//					break;
//				}
//				case 5:	/* we do the same but on a different beat */
//				{	int i;
//					for(i=0; i<8; i+=2)
//					{	pattern[i]=0xFF00FF00 | (dq<16 ? 0 : (0x101<<(dq-16)));
//						pattern[i+1]=0xFF00FF00 | (dq>=16 ? 0 : (0x101<<dq));
//					};
//					break;
//				}
//			};
//#else
//			int i;
//			for(i=0; i<8; i++)
//			{	uint32_t val;
//				if(i & 1) val=(dq>=16 ? 0 : (0x101<<dq));
//				else val=(dq<16 ? 0 : (0x101<<(dq-16)));
//				if(pattern_count & 1) pattern[i]=0xFF00FF00;
//				else pattern[i]=0x00FF00FF;
//				if((pattern_count>>1)==0)
//					pattern[i]^=val;
//				else if((pattern_count>>1)==1)
//					pattern[i]&=~val;
//				else if((pattern_count>>1)==2)
//					pattern[i]|=val;
//			};
//#endif
//			for(p=(uint32_t *)baseAddress; (uint32_t)p<(uint32_t)baseAddress+nBytes; p+=8)
//				asm volatile (" \
//					ldr r0, [%0, #0]\n \
//					ldr r1, [%0, #4]\n \
//					ldr r2, [%0, #8]\n \
//					ldr r3, [%0, #12]\n \
//					ldr r4, [%0, #16]\n \
//					ldr r5, [%0, #20]\n \
//					ldr r6, [%0, #24]\n \
//					ldr r7, [%0, #28]\n \
//					stmia %1, { r0, r1, r2, r3, r4, r5, r6, r7 }\n \
//					" : : "r" (&pattern), "r" (p) 
//					: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"
//				);
//			for(p=(uint32_t *)baseAddress; (uint32_t)p<(uint32_t)baseAddress+nBytes; p+=8)
//			{	int i;
//				asm volatile (" \
//					ldmia %1, { r0, r1, r2, r3, r4, r5, r6, r7 }\n \
//					str r0, [%0, #0]\n \
//					str r1, [%0, #4]\n \
//					str r2, [%0, #8]\n \
//					str r3, [%0, #12]\n \
//					str r4, [%0, #16]\n \
//					str r5, [%0, #20]\n \
//					str r6, [%0, #24]\n \
//					str r7, [%0, #28]\n \
//					" : : "r" (&patternrd), "r" (p) 
//					: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"
//				);
//				for(i=0; i<8; i++)
//					if(pattern[i] != patternrd[i])
//					{	if(npatdebug_putss==0) debug_puts("\n");
//						npatdebug_putss++;
//#ifdef VERBOSE_MEMTEST
//						debug_puts("\t@");
//						puthex((uint32_t)p+i*4);
//						debug_puts(" wrote ");
//						puthex(pattern[i]);
//						debug_puts(" read ");
//						puthex(patternrd[i]);
//						debug_puts("\n");
//#endif
//					};
//			}
//			if(npatdebug_putss)
//			{	debug_puts("\tFailed on pattern ");
//				putint(pattern_count);
//				debug_puts(", ");
//				putint(npatdebug_putss);
//				debug_puts(" times.\n");
//				ndqdebug_putss+=npatdebug_putss;
//			};
//		};
//		if(ndqdebug_putss==0)
//			debug_puts("ok.\n");
//		else
//			nwrongdq++;
//						
//	};
//	return nwrongdq;
	return 0;
}	/* memTestSSO() */

/**********************************************************************
*
* Function:    memTestBurst()
*
* Description: Basic memory test: it does word write and read of several
*              patterns
*
* Notes:       
*
* Returns:     Number of debug_putss found. The test stops after MEMTESTBURST_MAXERR
*
*              This test will display an debug_puts message
*
**********************************************************************/
//#define MEMTESTBURST_MAXERR	100
int memTestBurst(volatile uint32_t *baseAddress, unsigned long nBytes)
{	
//	int burst;
//	int ntotdebug_putss=0;
//	for(burst=1; burst<=8; burst<<=1)
//	{	uint32_t pattern[8], patternrd[8];
//		int pattern_count;
//		for(pattern_count=0; pattern_count<5; pattern_count++)
//		{	int ndebug_putss=0;
//			volatile uint32_t *p;
//			int i;
//			debug_puts("Test Memory with bursts of ");
//			putint(burst);
//			debug_puts(" words using pattern ");
//			putint(pattern_count);
//			debug_puts(" ... ");
//			for(p=(uint32_t *)baseAddress; (uint32_t)p<(uint32_t)baseAddress+nBytes; p+=burst)
//			{	for(i=0; i<burst; i++)
//					switch(pattern_count)
//					{	case 0:	/* 0 everywhere */
//							pattern[i]=0;
//							break;
//						case 1:	/* 1 everywhere */
//							pattern[i]=0xFFFFFFFF;
//							break;
//						case 2:	/* Flip all bits */
//							pattern[i]=0xAA55AA55;
//							break;
//						case 3:	/* return address */
//							pattern[i]=(uint32_t)p+(i<<2);
//							break;
//						case 4:	/* return address in bytes */
//						{	char *t=(char *)&pattern[i];
//							int c;
//							for(c=0; c<4; c++)
//								t[c]=(uint32_t)p+(i<<2)+c;
//							break;
//						}
//					};
//				switch(burst)
//				{	case 1:
//						*p=pattern[0];
//						patternrd[0]=*p;
//						break;
//					case 2:
//						asm volatile (" \
//							ldr r0, [%0, #0]\n \
//							ldr r1, [%0, #4]\n \
//							stmia %1, { r0, r1}\n \
//							" : : "r" (&pattern), "r" (p) 
//							: "r0", "r1"
//						);
//						asm volatile (" \
//							ldmia %1, { r0, r1}\n \
//							str r0, [%0, #0]\n \
//							str r1, [%0, #4]\n \
//							" : : "r" (&patternrd), "r" (p) 
//							: "r0", "r1"
//						);
//						break;
//					case 4:
//						asm volatile (" \
//							ldr r0, [%0, #0]\n \
//							ldr r1, [%0, #4]\n \
//							ldr r2, [%0, #8]\n \
//							ldr r3, [%0, #12]\n \
//							stmia %1, { r0, r1, r2, r3}\n \
//							" : : "r" (&pattern), "r" (p) 
//							: "r0", "r1", "r2", "r3"
//						);
//						asm volatile (" \
//							ldmia %1, { r0, r1, r2, r3}\n \
//							str r0, [%0, #0]\n \
//							str r1, [%0, #4]\n \
//							str r2, [%0, #8]\n \
//							str r3, [%0, #12]\n \
//							" : : "r" (&patternrd), "r" (p) 
//							: "r0", "r1", "r2", "r3"
//						);
//						break;
//					case 8:
//						asm volatile (" \
//							ldr r0, [%0, #0]\n \
//							ldr r1, [%0, #4]\n \
//							ldr r2, [%0, #8]\n \
//							ldr r3, [%0, #12]\n \
//							ldr r4, [%0, #16]\n \
//							ldr r5, [%0, #20]\n \
//							ldr r6, [%0, #24]\n \
//							ldr r7, [%0, #28]\n \
//							stmia %1, { r0, r1, r2, r3, r4, r5, r6, r7 }\n \
//							" : : "r" (&pattern), "r" (p) 
//							: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"
//						);
//						asm volatile (" \
//							ldmia %1, { r0, r1, r2, r3, r4, r5, r6, r7 }\n \
//							str r0, [%0, #0]\n \
//							str r1, [%0, #4]\n \
//							str r2, [%0, #8]\n \
//							str r3, [%0, #12]\n \
//							str r4, [%0, #16]\n \
//							str r5, [%0, #20]\n \
//							str r6, [%0, #24]\n \
//							str r7, [%0, #28]\n \
//							" : : "r" (&patternrd), "r" (p) 
//							: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"
//						);
//						break;
//				};
//				for(i=0; i<burst; i++)
//					if(pattern[i] != patternrd[i])
//					{	if(ndebug_putss==0)
//							debug_puts("failed\n");
//						debug_puts("\t@");
//						puthex((uint32_t)p+i*4);
//						debug_puts(" wrote ");
//						puthex(pattern[i]);
//						debug_puts(" read ");
//						puthex(patternrd[i]);
//						debug_puts("\n");
//						ntotdebug_putss++;
//						ndebug_putss++;
//						//if(ndebug_putss>MEMTESTBURST_MAXERR)
//							//return ntotdebug_putss;
//					};
//			};
//			if(ndebug_putss==0)
//				debug_puts("ok\n");
//		};
//	};
//	return ntotdebug_putss;
	return 0;
} 
//#endif
//#endif
