/**qcc_regs.h
 * This file contains the QCC bridge registers description
 */

//#ifndef __QCC_REGS_H
//#define	__QCC_REGS_H

#include "mloader.h"
#include "types.h"

/* Few defines */
//#define MERLIN_QCCBRIDGE_BASE	0x80004c00

/* Registers definition */
//typedef union
//{	uint32_t r;
//	struct
//	{	uint32_t CSRBlockID:	8;
//		uint32_t Rsvd1:		4;
//		uint32_t CSRLen:	3;
//		uint32_t CSRAccess:	1;
//		uint32_t Padding:	16;
//	} b;
//} qccreg_CSRCmd_t;

//typedef union
//{	uint32_t r;
//	struct 
//	{	uint32_t CSRAddr:	16;
//		uint32_t Padding:	16;
//	} b;
//} qccreg_CSRAddr_t;

//typedef union
//{	uint32_t r;
//	struct
//	{	uint32_t CSRWrData:	32;
//	} b;
//} qccreg_CSRWrData_t;

//typedef union
//{	uint32_t r;
//	struct
//	{	uint32_t CSRRdData:	32;
//	} b;
//} qccreg_CSRRdData_t;

//typedef union
//{	uint32_t r;
//	struct
//	{	uint32_t CSRDone:	1;
//		uint32_t CSRErr:	1;
//		uint32_t Rsvd1:		2;
//		uint32_t CSRRespLen:	3;
//		uint32_t Rsvd2:		1;
//		uint32_t CSRRespID:	8;
//		uint32_t Padding:	16;
//	} b;
//} qccreg_CSRStat_t;

//typedef union
//{	uint32_t r;
//	struct
//	{	uint32_t CSRInt:	1;
//		uint32_t Mbox0Int:	1;
//		uint32_t Mbox1Int:	1;
//		uint32_t Mbox4Int:	1;
//		uint32_t Mbox5Int:	1;
//		uint32_t HMCSInt:	1;
//		uint32_t Rsvd1:		26;
//	} b;
//} qccreg_PeriInt_t;

//typedef union
//{	uint32_t r;
//	struct
//	{	uint32_t nor_span_reg:		1;
//		uint32_t nand_flash_reg:	1;
//		uint32_t nand_2k_pg_reg:	1;
//		uint32_t nand_nor_ram_en_reg:	1;
//		uint32_t nand_rd_cf_reg:	1;
//		uint32_t cf_ram_en_reg:		1;
//		uint32_t cf_pc_mode_reg:	1;
//		uint32_t mac_speed_i_reg:	1;
//		uint32_t phy_intf_sel_i_reg:	3;
//		uint32_t tx_tune_reg:		2;
//		uint32_t Rsvd1:			19;
//	} b;
//} qccreg_SysConfig_t;

//typedef volatile struct
//{	qccreg_CSRCmd_t CSRCmd;
//	qccreg_CSRAddr_t CSRAddr;
//	qccreg_CSRWrData_t CSRWrData;
//	qccreg_CSRRdData_t CSRRdData;
//	qccreg_CSRStat_t CSRStat;
//	qccreg_PeriInt_t PeriIntPend;
//	qccreg_PeriInt_t PeriIntEnSet;
//	qccreg_PeriInt_t PeriIntEnClr;
//	uint32_t BFifoStatus;
//	uint32_t BFifoConfig;
//	uint32_t Rsvd0x28;
//	uint32_t Rsvd0x2C;
//	uint32_t Rsvd0x30;
//	uint32_t Rsvd0x34;
//	uint32_t Rsvd0x38;
//	uint32_t Rsvd0x3C;
//	uint32_t BFifoWrPort;
//	uint32_t Rsvd0x44;
//	uint32_t Rsvd0x48;
//	uint32_t Rsvd0x4C;
//	uint32_t Rsvd0x50;
//	uint32_t Rsvd0x54;
//	uint32_t Rsvd0x58;
//	uint32_t Rsvd0x5C;
//	qccreg_SysConfig_t SysConfig;
//	uint32_t SysMux_0;
//	uint32_t SysMux_1;
//	uint32_t SysMux_2;
//	uint32_t SysMux_3;
//	uint32_t DTCM_Ram_Config;
//	uint32_t USB_Ram_Config;
//	uint32_t Rsvd0x6C;
//	uint32_t FIQSel;
//	uint32_t HMCS_status;
//	uint32_t HostMuxCnt;
//} qccbridge_t;

//#endif	/* #ifndef __QCC_REGS_H */
