/**gpio_regs.h
 * This file contains the GPIO hardware registers definitions
 */
 
#ifndef __GPIO_REGS_H
#define	__GPIO_REGS_H

//#include "mloader.h"
//#include "types.h"

/* Few defines */
#define MERLIN_GPIOBANK0_BASE	0x88202800
#define MERLIN_GPIOBANK1_BASE	0x88202c00
#define MERLIN_GPIOBANK2_BASE	0x88203000

/* Registers definitions */

typedef volatile struct
{	uint32_t data;
	uint32_t dir;
	uint32_t mode;
	uint32_t Rsvd0x0C;
	uint32_t Rsvd0x10;
	uint32_t Rsvd0x14;
	uint32_t Rsvd0x18;
	uint32_t Rsvd0x1C;
	uint32_t Rsvd0x20;
	uint32_t Rsvd0x24;
	uint32_t Rsvd0x28;
	uint32_t Rsvd0x2C;
	uint32_t IntEnable;
	uint32_t IntMask;
	uint32_t IntTypeLevel;
	uint32_t IntTypePolarity;
	uint32_t IntStatus;
	uint32_t RawIntStatus;
	uint32_t Debounce;
	uint32_t IntClear;
	uint32_t extdata;
	uint32_t Rsvd0x54;
	uint32_t Rsvd0x58;
	uint32_t Rsvd0x5C;
	uint32_t LevelSync;
	uint32_t ID;
	uint32_t Rsvd0x68;
	uint32_t Version;
} dwc_gpio_t;

#endif	/* #ifndef __GPIO_REGS_H */
