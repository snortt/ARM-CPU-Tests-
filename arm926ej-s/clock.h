/**clock.h
 * This file contains the Clock controller routines definitions
 */

//#ifndef __CLOCK_H
//#define	__CLOCK_H

//#include "mloader.h"

/* Clocks already on when the chip boots */
//#ifdef FPGA_BOARD
//#	define MERLIN_PLL0_XIN_HZ	12000000
//#	define MERLIN_PLL0_OUT_HZ	1295000000
//#	define MERLIN_PLL0_FOQ1_HZ	324000000
//#	define MERLIN_PLL0_FOUT_HZ	144000000
//#	define MERLIN_ARM_CLK_HZ	48000000
//#	define MERLIN_AHB_CLK_HZ	24000000
//#	define MERLIN_APB_CLK_HZ	6000000
//#	define MERLIN_SSI_CLK_HZ	24000000
//#	define MERLIN_UARTDBG_CLK_HZ	27000000
//#else	/* #ifdef FPGA_BOARD */
//#	define MERLIN_PLL0_XIN_HZ	12000000
//#	define MERLIN_PLL0_OUT_HZ	1295000000
//#	define MERLIN_PLL0_FOQ1_HZ	324000000
//#	define MERLIN_PLL0_FOUT_HZ	144000000
//#	define MERLIN_ARM_CLK_HZ	144000000
//#	define MERLIN_AHB_CLK_HZ	72000000
//#	define MERLIN_APB_CLK_HZ	18000000
//#	define MERLIN_SSI_CLK_HZ	72000000
//#	define MERLIN_UARTDBG_CLK_HZ	64800000
//#endif	/* #ifdef FPGA_BOARD */

//#define MERLIN_AHB_T_NS			(1000000000/MERLIN_AHB_CLK_HZ)

//typedef enum {
//	CLOCKID_UARTDBG=1,
//	CLOCKID_SSI=2,
//	CLOCKID_USB=3,
//	CLOCKID_ETH=4,
//} clock_id_t;

//extern int clock_set(clock_id_t clkid, 
//		uint32_t requeste_rate, unsigned long *got_rate);
//
//#endif	/* #ifndef __CLOCK_H */
