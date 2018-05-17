/**debug.h
 * This file contains the debug routines and defines.
 */

//#ifndef __DEBUG_H
//#define	__DEBUG_H

/* Contain configuration */
//#include "mloader.h"
#include "types.h"
#include "uart.h"


extern int debug_init(void);
extern void debug_puts(const char *str);
//extern int debug_puts(const char *str);
extern void debug_puthex_size(uint32_t val, uint8_t size);
extern void debug_putint(int val);

/* 
*  just different names to indicate importance of message
*/
//#define	error(str)	debug_puts(str)
//#define	info(str)	debug_puts(str)
//#define	warn(str)	debug_puts(str)
//
#define PUTHEX_SIZE_BYTE  4
#define PUTHEX_SIZE_SHORT 12
#define PUTHEX_SIZE_WORD  28
//
//#ifdef DEBUG
//#define	dputs(str)	debug_puts(str)
//#define	debug(str)	debug_puts(str)
#define dputhexb(val)	debug_puthex_size((val & 0xFF), PUTHEX_SIZE_BYTE)
#define dputhexs(val)	debug_puthex_size((val & 0xFFFF), PUTHEX_SIZE_SHORT)
#define dputhex(val)	debug_puthex_size(val, PUTHEX_SIZE_WORD)
#define dputint(val)	debug_putint(val)
//#else
//#define	dputs(str)	do {} while(0)
//#define	debug(str)	do {} while(0)
//#define dputhexb(val)	do {} while(0)
//#define dputhexs(val)	do {} while(0)
//#define dputhex(val)	do {} while(0)
//#define dputint(val)	do {} while(0)
//#endif

/* HACK just want a way to debug_puts in a single file */
/*
#define	fputs(str)	debug_puts(str)
#define fputhexb(val)	debug_puthex_size((val & 0xFF), PUTHEX_SIZE_BYTE)
#define fputhexs(val)	debug_puthex_size((val & 0xFFFF), PUTHEX_SIZE_SHORT)
#define fputhex(val)	debug_puthex_size(val, PUTHEX_SIZE_WORD)
#define fputint(val)	debug_putint(val)
*/

#define	puts(str)	debug_puts(str)
#define puthex(val)	debug_puthex_size(val, PUTHEX_SIZE_WORD)
#define putint(val)	debug_putint(val)

#define BUG()		{ puts(__FILE__ "@"); putint(__LINE__); puts(" : BUG!!!\n"); while(1); }

//#endif	/* #ifndef __DEBUG_H */
