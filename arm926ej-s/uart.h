/**uart.h
 * This file contains the API of the UART driver
 */
 
//#ifndef __UART_H
//#define	__UART_H

/* Contain configuration */
//#include "mloader.h"

extern int uart_init(int baudrate, int databits, char parity, int stopbits, char override);
extern int uart_write(const char *buf, int n);
extern int uart_read(char *buf, int n);
extern int uart_read_nowait(char *buf, int n);
extern void uart_flush(void);

//#endif	/* #ifndef __UART_H */
