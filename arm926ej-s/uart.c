/**uart.c
 * This file contains the UART driver
 */

//#include "mloader.h"
//#include "reset.h"
//#include "clock.h"
#include "uart_regs.h"
//#include "ioctrl.h"

/* this will be called by 1) the SYSTEM_SECTION if defined, 2) from main and 3) 
*  if booting from xmodem.  If called from main, we don't want to override 
*  settings if already called from system_section.  However, if no system 
*  section exist, and xmodem is used, there is a changes that xmodem will 
*  not used the default.  
 */
int uart_init(int baudrate, int databits, 
		char parity, int stopbits, char override)
{	
	dwc_uart_t *uart=(dwc_uart_t *)MERLIN_UARTDBG_BASE;
	uartreg_LCR_t LCR;
	uartreg_FCR_t FCR;
	uartreg_MCR_t MCR;
	unsigned long clock_rate;
	//uartreg_RBR_THR_DLL_t RBR_THR_DLL={ DLL: {r: 0} };
	//uartreg_DLH_IER_t DLH_IER={ DLH: { r: 0} };
	unsigned short divisor;
	int i;

	LCR.r = 0;
	FCR.r = 0;
	MCR.r = 0;
	/* Enable and set UARTDBG clock */
	//if(clock_set(CLOCKID_UARTDBG, MERLIN_UARTDBG_CLK_HZ, &clock_rate) < 0) {
	//	BUG();
	//};
/* HACK: The clock used by the FPGA cannot be achieved with default PLL values ... */
#ifdef FPGA_BOARD
	clock_rate=MERLIN_UARTDBG_CLK_HZ;
#endif
	/* calc divisor based on real rate, not requested rate */
	divisor=(clock_rate+(baudrate<<3))/(baudrate<<4);

	/* Set UART IO strength */
	//ioctrl_set_strength(IOCTRL_GRP_UART, 
	//		IOCTRL_SLEWRATE_FASTER, IOCTRL_DRIVESTRENGTH_4ma);
	/* Remove UARTDBG from reset */
	//if(reset_clear(RESET_ID_UARTDBG)<0) {	
		//puts("ERROR: Failed to remove UART reset, continue anyway ... \n");
	//	BUG();
	//};
	/* Program the UART */
	while(uart->USR.b.BUSY);
	/* Set config register */
	LCR.b.DLS=databits-5;
	LCR.b.STOP=stopbits-1;
	LCR.b.PEN=parity=='n'?0:1;
	LCR.b.EPS=parity=='e'?1:0;
	uart->LCR.r=LCR.r;
	/* Reset and enable FIFOs */
	FCR.b.FIFOE=1;
	uart->IIR_FCR.FCR.r=FCR.r;
	/* Set flow control bits to enable Rx/Tx */
	MCR.b.DTR=1;
	MCR.b.RTS=1;
	uart->MCR.r=MCR.r;
	/* Wait for the UART to be ready before we switch DLAB */
	while(uart->USR.b.BUSY);
	/* Set baudrate, to do so we must switch register context with DLAB */
	LCR.b.DLAB=1;
	uart->LCR.r=LCR.r;
	uart->RBR_THR_DLL.DLL.r=divisor & 0xFF;
	uart->DLH_IER.DLH.r=divisor>>8;
	LCR.b.DLAB=0;
	uart->LCR.r=LCR.r;
	/* Datasheet recommend to wait 8 UART cycles, we read USR to achieve that */
	for(i=8; i!=0; i--) {	
		volatile uint32_t reg=uart->USR.r;
	}
	/* UART is now ready */
	return 0;
}

int uart_write(const char *buf, int n)
{	
	dwc_uart_t *uart=(dwc_uart_t *)MERLIN_UARTDBG_BASE;
	int count=n;

	while(count--)
	{	
		while(uart->USR.b.TFNF==0);	/* wait for FIFO to have space */
		uart->RBR_THR_DLL.THR.r=*buf++;
	};
	return n;
}

int uart_read(char *buf, int n)
{	
	dwc_uart_t *uart=(dwc_uart_t *)MERLIN_UARTDBG_BASE;
	int count=n;

	while(count--)
	{	
		uint32_t data;
		while(uart->USR.b.RFNE==0);
		data=uart->RBR_THR_DLL.RBR.r;
		*buf++=data & 0xFF;
	};
	return n;
}

int uart_read_nowait(char *buf, int n)
{	
	dwc_uart_t *uart=(dwc_uart_t *)MERLIN_UARTDBG_BASE;
	int count=n;

	while(count)
	{	
		uint32_t data;
		if(uart->USR.b.RFNE==0) 
			break;
		data=uart->RBR_THR_DLL.RBR.r;
		*buf++=data & 0xFF;
		count--;
	};
	return n-count;
}

void uart_flush()
{	
	dwc_uart_t *uart=(dwc_uart_t *)MERLIN_UARTDBG_BASE;

	while(uart->USR.b.TFE==0);
	return;
}
