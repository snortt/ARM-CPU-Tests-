/**reset.c
 * This file contains the Reser controller routines
 */
 
//#include "mloader.h"
//#include "reset.h"
//#include "qcc.h"
//#include "qcc_regs.h"

//int reset_init(void)
//{	
	//int ret=0;
	//qccbridge_t *qcc=(qccbridge_t *)MERLIN_QCCBRIDGE_BASE;
	
	/* Disable watchdog reset capability */
	//if(qcc_write(QCC_BID_CHIPCTL, QREG_ADDR(CHIP_CTL_x_WdogResetControl), 0, QREG_NUMB(CHIP_CTL_x_WdogResetControl))<0)
	//{	ret=-EIO;
//		puts("Failed to disable Watchdog reset, continue anyway ...\n");
//		BUG();
//	};
	/* If needed, devices that should be put in reset can be listed here */
	//qcc_write(QCC_BID_CHIPCTL, QREG_ADDR(CHIP_CTL_x_SOCResetVecSet), DEVICES_TO_RESET, QREG_NUMB(CHIP_CTL_x_SOCResetVecSet));
	/* Wait a bit */
	//udelay(1);
	/* Switch FIQ mux to default */
	//qcc->FIQSel=0;
	/* Disable interrupts coming from QCC/SISC bridge */
	//qcc->PeriIntEnClr.r=0xFFFFFFFF;
	/* Remove from reset devices that must be used */
	//qcc_write(QCC_BID_CHIPCTL, QREG_ADDR(CHIP_CTL_x_SOCResetVecClr), DEVICES_TO_UNRESET, QREG_NUMB(CHIP_CTL_x_SOCResetVecClr));
	//return ret;
//}

//int reset_set(reset_id_t id)
//{	
	//return qcc_write(QCC_BID_CHIPCTL, QREG_ADDR(CHIP_CTL_x_SOCResetVecSet), 1<<id, QREG_NUMB(CHIP_CTL_x_SOCResetVecSet));
//}

//int reset_clear(reset_id_t id)
//{	
	//return qcc_write(QCC_BID_CHIPCTL, QREG_ADDR(CHIP_CTL_x_SOCResetVecClr), 1<<id, QREG_NUMB(CHIP_CTL_x_SOCResetVecClr));
//}
