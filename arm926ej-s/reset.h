/**reset.h
 * This file contains the Reser controller routines definitions
 */

//#ifndef __RESET_H
//#define	__RESET_H

//#include "mloader.h"

//typedef enum {
//	RESET_ID_AES=0,
//	RESET_ID_AHB_ARM=1,
//	RESET_ID_AHB_ARM_MMU=2,
//	RESET_ID_AHB_DMA=3,
//	RESET_ID_AHB_DMA_MMU=4,
//	RESET_ID_AHB_PERIPH=5,
//	RESET_ID_APB_BRIDGE=6,
//	RESET_ID_ARM=7,
//	RESET_ID_CF=8,
//	RESET_ID_DMAC=9,
//	RESET_ID_EH2H_DMA=10,
//	RESET_ID_EH2H_PERIPH=11,
//	RESET_ID_GMAC=12,
//	RESET_ID_ICTL=13,
//	RESET_ID_MHIF=14,
//	RESET_ID_NANDNOR=15,
//	RESET_ID_OTGPHY=16,
//	RESET_ID_PRESET=17,
//	RESET_ID_QCCSISC=18,
//	RESET_ID_QDSM=19,
//	RESET_ID_SDMMC=20,
//	RESET_ID_SHA=21,
//	RESET_ID_USBH=22,
//	RESET_ID_USBP=23,
//	RESET_ID_WDT=24,
//	RESET_ID_UARTDBG=25,
//	RESET_ID_UART01=26,
//	RESET_ID_PWM=27,
//	RESET_ID_SSI=28,
//	RESET_ID_GPIO=29,
//	RESET_ID_I2C=30,
//} reset_id_t;

/* Devices not in this list are:
 *	RESET_ID_ARM: obvious
 *	RESET_ID_QCCSISC: need to work to control the resets
 *	RESET_ID_AHB_ARM: needed to talk to QCCSISC bridge
 *	RESET_ID_EH2H_PERIPH: needed to talk to QCCSISC bridge
 *	RESET_ID_AHB_PERIPH: needed to talk to QCCSISC bridge
 */
//#define DEVICES_TO_RESET	((1<<RESET_ID_AES) \
//				| (1<<RESET_ID_AHB_ARM_MMU) \
//				| (1<<RESET_ID_AHB_DMA) \
//				| (1<<RESET_ID_AHB_DMA_MMU) \
//				| (1<<RESET_ID_APB_BRIDGE) \
//				| (1<<RESET_ID_CF) \
//				| (1<<RESET_ID_DMAC) \
//				| (1<<RESET_ID_EH2H_DMA) \
//				| (1<<RESET_ID_GMAC) \
//				| (1<<RESET_ID_ICTL) \
//				| (1<<RESET_ID_MHIF) \
//				| (1<<RESET_ID_NANDNOR) \
//				| (1<<RESET_ID_OTGPHY) \
//				| (1<<RESET_ID_PRESET) \
//				| (1<<RESET_ID_QDSM) \
//				| (1<<RESET_ID_SDMMC) \
//				| (1<<RESET_ID_SHA) \
//				| (1<<RESET_ID_USBH) \
//				| (1<<RESET_ID_USBP) \
//				| (1<<RESET_ID_WDT) \
//				| (1<<RESET_ID_UARTDBG) \
//				| (1<<RESET_ID_UART01) \
//				| (1<<RESET_ID_PWM) \
//				| (1<<RESET_ID_SSI) \
//				| (1<<RESET_ID_GPIO) \
//				| (1<<RESET_ID_I2C))

//#define DEVICES_TO_UNRESET	((1<<RESET_ID_AHB_DMA) \
//				| (1<<RESET_ID_AHB_ARM_MMU) \
//				| (1<<RESET_ID_AHB_DMA_MMU) \
//				| (1<<RESET_ID_AHB_PERIPH) \
//				| (1<<RESET_ID_APB_BRIDGE) \
//				| (1<<RESET_ID_EH2H_DMA) \
//				| (1<<RESET_ID_GPIO) \
//				| (1<<RESET_ID_PRESET))

//#define RESET_MINPERIOD_CYCLES	100	
//
//extern int reset_init(void);
//extern int reset_set(reset_id_t id);
//extern int reset_clear(reset_id_t id);

//#endif	/* #ifndef __RESET_H */
