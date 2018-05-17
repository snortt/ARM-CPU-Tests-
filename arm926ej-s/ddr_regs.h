/**ddr_regs.h
 * This file contains the memory subsystem hardware registers definitions
 */
 
#ifndef __DDR_REGS_H
#define	__DDR_REGS_H

//#include "mloader.h"
#include "types.h"

/* Few defines */
#define MERLIN_MMUBRIDGE_BASE	0x00000000
#define MERLIN_DMABRIDGE_BASE	0xC0000000

/* Registers definitions */
#define MEMBRIDGE_ID_MASK	0xC0000000
#define MEMBRIDGE_REG_BASE	0x0C000000
#define MEMBRIDGE_ADDR_MASK	0x01FFFFFF

typedef union
{	uint32_t r;
	struct
	{	uint32_t Lpartition:	8;
		uint32_t Rsvd1:		24;
	} b;
} memreg_LPartition_t;

typedef union
{	uint32_t r;
	struct
	{	uint32_t MarbPrior:	2;
		uint32_t Isplit:	1;
		uint32_t Rsvd1:		1;
		uint32_t Ifetch:	1;
		uint32_t INCRX_burstsz:	5;
		uint32_t INCRX_en:	1;
		uint32_t Rsvd2:		21;
	} b;
} memreg_MMUConfig_t;

typedef union
{	uint32_t r;
	struct
	{	uint32_t ConfigDone:	1;
		uint32_t Rsvd1:		31;
	} b;
} memreg_MMUConfigDone_t;

typedef volatile struct
{	uint32_t PartitionID0;
	uint32_t PartitionID1;
	uint32_t PartitionID2;
	uint32_t PartitionID3;
	memreg_LPartition_t LPartition;
	memreg_MMUConfig_t MMUConfig;
	uint32_t MasterWrAck;
	memreg_MMUConfigDone_t MMUConfigDone;
} mem_bridge_t;

/* PMC configuration registers are in QCC space. */
#define PMCREG_ADDR(regname)   Reg_QA_PMCDDR_base_##regname##_ADDRESS
#define PMCREG_TYPE(regname)   Reg_QA_PMCDDR_base_##regname##_t
#define PMCREG_NUMB(regname)   Reg_QA_PMCDDR_base_##regname##_NUM_BYTES
#define PMCREG_INDX(regname)   Reg_QA_PMCDDR_base_##regname##_I

/* DDR boot args */
#define GET_DDRBOOT_PARTITION(bootaddr)	((bootaddr)>>24)
#define GET_DDRBOOT_JUMPADDR(bootaddr)	(((bootaddr) & 0xFFFFFF)<<8)

#endif	/* #ifndef __DDR_REGS_H */
