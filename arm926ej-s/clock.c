/**clock.c
 * This file contains the Clock controller routines
 */
//#include "mloader.h"
//#include "clock.h"
//#include "qcc.h"

//uint32_t FOQ1_rate = 0;
//uint32_t xin_rate = 0;

//int clock_set(clock_id_t clkid, uint32_t fout_requested, unsigned long *got_rate)
//{	
//	/* anything that is clock dependent, will have to call this function.
//	*  the expectation is that the chip will boot at the default rate and
//	*  then pll0 and scaler0 clock rate changes will be done in the reg 
//	*  files which are processed before anything else, so it is safe to do
//	*  calculations and write registers(like the uart) that will be valid
//	*  when linux boots also 
//	*/
//	QREG_TYPE(CHIP_CTL_x_PLL0Control) PLL0Control;
//	PLL0Control.r=qcc_read(QCC_BID_CHIPCTL, 
//			QREG_ADDR(CHIP_CTL_x_PLL0Control), 
//			QREG_NUMB(CHIP_CTL_x_PLL0Control));
//	PLL0Control.r = 0;
//	/* in almost all cases, we will use a 12 or 27 MHz xin clock,
// 	 *  so default to one of these values UNLESS for some odd reason
//	 *  xin is one of these two, then xin_rate will be derived from 
//	 *  the environment */
//	if (xin_rate == 0) {
//		if (PLL0Control.b.PLL0Control_CLKSEL == 0)
//			xin_rate = 12000000;
//		else
//			xin_rate = 27000000;
//	}
//	//foq1 = ((xin*sdiv*intprog)/sout)/4
//	FOQ1_rate = (xin_rate * 
//			(8 >> PLL0Control.b.PLL0Control_SDIV) * 
//				PLL0Control.b.PLL0Control_INTPROG) /
//				(8 >> PLL0Control.b.PLL0Control_SOUT);
//	FOQ1_rate /= 4;
//
//	switch(clkid)
//	{	
//		case CLOCKID_UARTDBG:
//			{	
//				QREG_TYPE(CHIP_CTL_x_DBGUARTClkControl) DBGUARTClkControl;
//				uint32_t cycles;
//				DBGUARTClkControl.r = 0;
//
//				if(fout_requested==0) {	
//					BUG();
//					/*return -EINVAL;*/
//				};
//
//				DBGUARTClkControl.r=qcc_read(QCC_BID_CHIPCTL, 
//						QREG_ADDR(CHIP_CTL_x_DBGUARTClkControl), 
//						QREG_NUMB(CHIP_CTL_x_DBGUARTClkControl));
//
//				/* disable clock */
//				DBGUARTClkControl.b.DBGUARTClkControl_ClkEn=0;
//				qcc_write(QCC_BID_CHIPCTL, 
//						QREG_ADDR(CHIP_CTL_x_DBGUARTClkControl), 
//						DBGUARTClkControl.r, 
//						QREG_NUMB(CHIP_CTL_x_DBGUARTClkControl));
//
//				/* calculate and update divider values */
//				cycles = (FOQ1_rate+(fout_requested>>1))/fout_requested;
//				DBGUARTClkControl.b.DBGUARTClkControl_High = (cycles>>1)-1;
//				DBGUARTClkControl.b.DBGUARTClkControl_Low  = 
//					cycles-DBGUARTClkControl.b.DBGUARTClkControl_High-2;
//
//				/* we want to be under instead of over */
//				if (FOQ1_rate/((DBGUARTClkControl.b.DBGUARTClkControl_High+1)+
//							(DBGUARTClkControl.b.DBGUARTClkControl_Low+1)) > fout_requested)
//					DBGUARTClkControl.b.DBGUARTClkControl_High++;
//
//				qcc_write(QCC_BID_CHIPCTL, 
//						QREG_ADDR(CHIP_CTL_x_DBGUARTClkControl), 
//						DBGUARTClkControl.r, 
//						QREG_NUMB(CHIP_CTL_x_DBGUARTClkControl));
//
//				/* re-enable clock */
//				DBGUARTClkControl.b.DBGUARTClkControl_ClkEn=1;
//				qcc_write(QCC_BID_CHIPCTL, 
//						QREG_ADDR(CHIP_CTL_x_DBGUARTClkControl), 
//						DBGUARTClkControl.r, 
//						QREG_NUMB(CHIP_CTL_x_DBGUARTClkControl));
//
//				*got_rate = (FOQ1_rate/
//					((DBGUARTClkControl.b.DBGUARTClkControl_High+1)+
//					 (DBGUARTClkControl.b.DBGUARTClkControl_Low+1)));
//				break;
//			}
//#if 0
//		case CLOCKID_SSI:
//			{	
//				QREG_TYPE(CHIP_CTL_x_SSI0ClkControl) SSI0ClkControl={ r: 0 };
//				unsigned int cycles;
//
//				if(hz==0)
//				{	
//					BUG();
//					return -EINVAL;
//				};
//				cycles=(MERLIN_PLL0_FOQ1_HZ+(hz>>1))/hz;
//				if(cycles<2) 
//				{
//					BUG();
//					return -EINVAL;
//				};
//				SSI0ClkControl.r=qcc_read(QCC_BID_CHIPCTL, 
//						QREG_ADDR(CHIP_CTL_x_SSI0ClkControl), 
//						QREG_NUMB(CHIP_CTL_x_SSI0ClkControl));
//
//				SSI0ClkControl.b.SSI0ClkControl_ClkEn=0;
//
//				qcc_write(QCC_BID_CHIPCTL, 
//						QREG_ADDR(CHIP_CTL_x_SSI0ClkControl), 
//						SSI0ClkControl.r, 
//						QREG_NUMB(CHIP_CTL_x_SSI0ClkControl));
//
//				SSI0ClkControl.b.SSI0ClkControl_High = (cycles>>1)-1;
//
//				SSI0ClkControl.b.SSI0ClkControl_Low = 
//					cycles-SSI0ClkControl.b.SSI0ClkControl_High-2;
//
//				qcc_write(QCC_BID_CHIPCTL, 
//						QREG_ADDR(CHIP_CTL_x_SSI0ClkControl), 
//						SSI0ClkControl.r, 
//						QREG_NUMB(CHIP_CTL_x_SSI0ClkControl));
//
//				SSI0ClkControl.b.SSI0ClkControl_ClkEn=1;
//
//				qcc_write(QCC_BID_CHIPCTL, 
//						QREG_ADDR(CHIP_CTL_x_SSI0ClkControl), 
//						SSI0ClkControl.r, 
//						QREG_NUMB(CHIP_CTL_x_SSI0ClkControl));
//				break;
//			}
//#endif
//		case CLOCKID_USB:
//		case CLOCKID_ETH:
//			break;
//		default:
//			return -EINVAL;
//	};
//	return 0;
//}
