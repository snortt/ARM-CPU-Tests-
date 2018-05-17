/*
 *	Funções para escrita
*/

#include "uart.h"
#include "uart_regs.h"
#include "io.h"


int putch(char _c) {
	dwc_uart_t *uartL=(dwc_uart_t *)MERLIN_UARTDBG_BASE;
	while(uartL->USR.b.TFNF==0);
	uartL->RBR_THR_DLL.THR.r=_c;
	return 0;
}

int putstr(char *_c) {
	while (*_c)
		putch(*_c++);
	return 0;
}
