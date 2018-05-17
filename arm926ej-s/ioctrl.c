/**ioctrl.c
 * This file contains IO PAD control APIs
 */

//#include "mloader.h"
//#include "ioctrl.h"
//#include "qcc.h"

/* Set all drive strength to acceptable minimums 
 * This API workaround a chip bug
 */
//int ioctrl_init(void)
//{	uint32_t reg=0;
//	reg|=IOCTRL_SLEWRATE_DEFAULT<<RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR0_LSB;
//	reg|=IOCTRL_DRIVESTRENGTH_DEFAULT<<RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS0_LSB;
//	reg|=IOCTRL_SLEWRATE_DEFAULT<<RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR1_LSB;
//	reg|=IOCTRL_DRIVESTRENGTH_DEFAULT<<RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS1_LSB;
//	reg|=IOCTRL_SLEWRATE_DEFAULT<<RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR2_LSB;
//	reg|=IOCTRL_DRIVESTRENGTH_DEFAULT<<RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS2_LSB;
//	qcc_write(QCC_BID_CHIPCTL, QREG_ADDR(CHIP_CTL_x_SerialIODriveStrength0), reg, QREG_NUMB(CHIP_CTL_x_SerialIODriveStrength0));
//	qcc_write(QCC_BID_CHIPCTL, QREG_ADDR(CHIP_CTL_x_SerialIODriveStrength1), reg, QREG_NUMB(CHIP_CTL_x_SerialIODriveStrength1));
//	qcc_write(QCC_BID_CHIPCTL, QREG_ADDR(CHIP_CTL_x_SerialIODriveStrength2), reg, QREG_NUMB(CHIP_CTL_x_SerialIODriveStrength2));
//	return 0;
//}

//int ioctrl_set_strength(ioctrl_groups_t padgrp, ioctrl_slewrate_t slewrate, ioctrl_drivestrength_t drivestrength)
//{	uint16_t addr;
//	int index;
//	uint32_t reg;
	
//	addr=((padgrp/3)<<2)+QREG_ADDR(CHIP_CTL_x_SerialIODriveStrength0);
//	index=padgrp%3;
//	reg=qcc_read(QCC_BID_CHIPCTL, addr, QREG_NUMB(CHIP_CTL_x_SerialIODriveStrength0));
//	reg&=	~( \
//			(\
//				( ((1<<RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR0_WIDTH)-1)<<RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR0_LSB ) \
//				|| ( ((1<<RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS0_WIDTH)-1)<<RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS0_LSB ) \
//			) << (index * (RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR1_LSB-RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR0_LSB)) \
//		);
//	reg|=slewrate<<(RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR0_LSB+(index * (RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR1_LSB-RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR0_LSB)));
//	reg|=drivestrength<<(RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS0_LSB+(index * (RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS1_LSB-RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS0_LSB)));
//	qcc_write(QCC_BID_CHIPCTL, addr, reg, QREG_NUMB(CHIP_CTL_x_SerialIODriveStrength0));
//	return 0;
//}
