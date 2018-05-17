/**debug.c
 * This file contains debug routines that will not be included in the final BootROM
 */

/*Usa funções para a UART */
#include "debug.h"

void debug_puts(const char *str)
{	char *p;
    	/* Get string length */
	for(p=(char *)str;*p!=0;p++)
		/* Add carriage return if necessary */
		if(*p=='\n')
		{	char c='\r';
			uart_write(str,p-str);
			uart_write(&c,1);
			str=p;
		};
	/* Send the last piece */
	uart_write(str,p-str);
	uart_flush();
}

static char hexchars[]="0123456789ABCDEF";

void debug_puthex_size(uint32_t val, uint8_t size)
{	
    int shift;
    uart_write("0x",2);
    for(shift=(size-4);shift>=0; shift-=4)
	    uart_write(&(hexchars[(val>>shift) & 0xF]),1);
}

void debug_putint(int val)
{	uint32_t divider=1000000000;
	char c;
	if(val<0) 
	{	c='-';
		uart_write(&c,1);
		val=-val;
	};
	while(val/divider==0) 
	{	divider/=10;
		if(divider==1)
			break;
	}
	while(divider>=1)
	{	char digit=val/divider;
		c=digit+'0';
		uart_write(&c,1);
		val-=digit*divider;
		divider/=10;
	};
}

