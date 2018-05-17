/**uart_regs.h
 * This file contains the UART hardware registers definitions
 */
 
//#ifndef __UART_REGS_H
//#define	__UART_REGS_H

//#include "mloader.h"
#include "types.h"

/* Few defines */
#define MERLIN_UART0_BASE	0x88201400
#define MERLIN_UART1_BASE	0x88201800
#define MERLIN_UARTDBG_BASE	0x88201c00

/* Registers definitions */
typedef union
{	uint32_t r;
	struct
	{	uint32_t RBR:		8;
		uint32_t Rsvd1:		24;
	} b;
} uartreg_RBR_t;

typedef union
{	uint32_t r;
	struct
	{	uint32_t THR:		8;
		uint32_t Rsvd1:		24;
	} b;
} uartreg_THR_t;

typedef union
{	uint32_t r;
	struct
	{	uint32_t DLL:		8;
		uint32_t Rsvd1:		24;
	} b;
} uartreg_DLL_t;

typedef union
{	uartreg_RBR_t RBR;
	uartreg_THR_t THR;
	uartreg_DLL_t DLL;
} uartreg_RBR_THR_DLL_t;

typedef union
{	uint32_t r;
	struct
	{	uint32_t DLH:		8;
		uint32_t Rsvd1:		24;
	} b;
} uartreg_DLH_t;

typedef union
{	uint32_t r;
	struct
	{	uint32_t ERBFI:		1;
		uint32_t ETBEI:		1;
		uint32_t ELSI:		1;
		uint32_t EDSSI:		1;
		uint32_t Rsvd1:		3;
		uint32_t PTIME:		1;
		uint32_t Rsvd2:		24;
	} b;
} uartreg_IER_t;

typedef union
{	uartreg_DLH_t DLH;
	uartreg_IER_t IER;
} uartreg_DLH_IER_t;

typedef union
{	uint32_t r;
	struct
	{	uint32_t BUSY:	1;
		uint32_t TFNF:	1;
		uint32_t TFE:	1;
		uint32_t RFNE:	1;
		uint32_t RFF:	1;
		uint32_t Rsvd1:	27;
	} b;
} uartreg_USR_t;

typedef union
{	uint32_t r;
	struct
	{	uint32_t DLS:	2;
		uint32_t STOP:	1;
		uint32_t PEN:	1;
		uint32_t EPS:	1;
		uint32_t Rsvd1:	1;
		uint32_t BC:	1;
		uint32_t DLAB:	1;
		uint32_t Rsvd2:	24;
	} b;
} uartreg_LCR_t;

typedef union
{	uint32_t r;
	struct __attribute__((packed))
	{	uint32_t IID:		4;
		uint32_t Rsvd1:		2;
		uint32_t FIFOSE:	2;
		uint32_t Rsvd2:		24;
	} b;
} uartreg_IIR_t;

typedef union
{	uint32_t r;
	struct __attribute__((packed))
	{	uint32_t FIFOE:		1;
		uint32_t RFIFOR:	1;
		uint32_t XFIFOR:	1;
		uint32_t DMAM:		1;
		uint32_t TET:		2;
		uint32_t RCVR:		2;
		uint32_t Rsvd1:		24;
	} b;
} uartreg_FCR_t;

typedef union
{	uartreg_FCR_t FCR;
	uartreg_IIR_t IIR;
} uartreg_IIR_FCR_t;

typedef union
{	uint32_t r;
	struct
	{	uint32_t DTR:		1;
		uint32_t RTS:		1;
		uint32_t OUT1:		1;
		uint32_t OUT2:		1;
		uint32_t LB:		1;
		uint32_t AFCE:		1;
		uint32_t SIRE:		1;
		uint32_t Rsvd1:		25;
	} b;
} uartreg_MCR_t;

typedef union
{	uint32_t r;
	struct
	{	uint32_t DR:		1;
		uint32_t OE:		1;
		uint32_t PE:		1;
		uint32_t FE:		1;
		uint32_t BI:		1;
		uint32_t THRE:		1;
		uint32_t TEMT:		1;
		uint32_t RFE:		1;
		uint32_t Rsvd1:		24;
	} b;
} uartreg_LSR_t;

typedef volatile struct
{	uartreg_RBR_THR_DLL_t RBR_THR_DLL;
	uartreg_DLH_IER_t DLH_IER;
	uartreg_IIR_FCR_t IIR_FCR;
	uartreg_LCR_t LCR;
	uartreg_MCR_t MCR;
	uartreg_LSR_t LSR;
	uint32_t MSR;
	uint32_t SCR;
	uint32_t LPDLL;
	uint32_t LPDLH;
	uint32_t Rsvd0x28;
	uint32_t Rsvd0x2C;
	uint32_t SRBR_STHR;
	uint32_t Rsvd0x34;
	uint32_t Rsvd0x38;
	uint32_t Rsvd0x3C;
	uint32_t Rsvd0x40;
	uint32_t Rsvd0x44;
	uint32_t Rsvd0x48;
	uint32_t Rsvd0x4C;
	uint32_t Rsvd0x50;
	uint32_t Rsvd0x54;
	uint32_t Rsvd0x58;
	uint32_t Rsvd0x5C;
	uint32_t Rsvd0x60;
	uint32_t Rsvd0x64;
	uint32_t Rsvd0x68;
	uint32_t Rsvd0x6C;
	uint32_t FAR;
	uint32_t TFR;
	uint32_t RFW;
	uartreg_USR_t USR;
	uint32_t TFL;
	uint32_t RFL;
	uint32_t SRR;
	uint32_t SRTS;
	uint32_t SBCR;
	uint32_t SDMAM;
	uint32_t SFE;
	uint32_t SRT;
	uint32_t STET;
	uint32_t HTX;
	uint32_t DMASA;
	uint32_t Rsvd0xAC;
	uint32_t Rsvd0xB0;
	uint32_t Rsvd0xB4;
	uint32_t Rsvd0xB8;
	uint32_t Rsvd0xBC;
	uint32_t Rsvd0xC0;
	uint32_t Rsvd0xC4;
	uint32_t Rsvd0xC8;
	uint32_t Rsvd0xCC;
	uint32_t Rsvd0xD0;
	uint32_t Rsvd0xD4;
	uint32_t Rsvd0xD8;
	uint32_t Rsvd0xDC;
	uint32_t Rsvd0xE0;
	uint32_t Rsvd0xE4;
	uint32_t Rsvd0xE8;
	uint32_t Rsvd0xEC;
	uint32_t Rsvd0xF0;
	uint32_t CPR;
	uint32_t UCV;
	uint32_t CTR;
} dwc_uart_t;

//#endif	/* #ifndef __UART_REGS_H */
