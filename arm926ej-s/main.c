/* Testes para o ARM */

/* #include <stdio.h> */
/*#include "uart.h" (debug.h inclui uart.h)*/
#include "debug.h"
#include "cp15.h"
#include "memtest.h"

/* Utilizado pelo io.h*/
/*char screen[81];*/

int main(void) {
	/*
	unsigned int c0_idL=0;
	unsigned int c0_cacheL=0;
	unsigned int c0_tcmL=0;
	unsigned int c1L=0;
	unsigned int c9_tcm_rd_regL=0;
	unsigned int c9_tcm_ri_regL=0;
	*/
	unsigned int c0_idL = CP15_c0_id();
	unsigned int c0_cacheL = CP15_c0_cache();
	unsigned int c0_tcmL = CP15_c0_tcm();
	unsigned int c1L = CP15_c1();
	unsigned int c9_tcm_rd_regL = CP15_tcm_rd();
	unsigned int c9_tcm_ri_regL = CP15_tcm_ri();
		
	/*
	sprintf(screen,"ID = %x\n",c0_idL);
	putstr(screen);
	sprintf(screen,"Cache = %x\n",c0_cacheL);
	putstr(screen);
	sprintf(screen,"TCM = %x\n",c0_tcmL);
	putstr(screen);
	sprintf(screen,"CReg = %x\n",c1L);
	putstr(screen);
	sprintf(screen,"TCM_RD = %x\n",c9_tcm_rd_regL);
	putstr(screen);
	sprintf(screen,"TCM_RI = %x\n",c9_tcm_ri_regL);
	putstr(screen);
	*/
	/* Informações sobre o processador e alguns registradores */
	debug_puts("\nc0_id="); debug_puthex_size(c0_idL,32);
	debug_puts("\nc0_cache="); debug_puthex_size(c0_cacheL,32);
	debug_puts("\nc0_tcm="); debug_puthex_size(c0_tcmL,32);
	debug_puts("\nc1="); debug_puthex_size(c1L,32);
	debug_puts("\nc9_tcm_rd="); debug_puthex_size(c9_tcm_rd_regL,32);
	debug_puts("\nc9_tcm_ri="); debug_puthex_size(c9_tcm_ri_regL,32);
		
	/*  Teste da memória */
	memtest_init();
	
	while(1) {};
}
