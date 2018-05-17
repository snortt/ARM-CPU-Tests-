/**qcc.c
 * This file contains the QCC registers access routines
 */

//#include "mloader.h"
//#include "qcc.h"
//#include "qcc_regs.h"
//
/* Read a register in QCC space */
//uint32_t qcc_read(int blockid, uint32_t addr, char size)
//{	
    //qccbridge_t *qcc=(qccbridge_t *)MERLIN_QCCBRIDGE_BASE;
//    qccreg_CSRCmd_t CSRCmd;
    //qccreg_CSRStat_t CSRStat;
//    uint32_t data;
//
    //CSRCmd.b.CSRBlockID=blockid;
//    CSRCmd.b.CSRLen=size & 3;
    //CSRCmd.b.CSRAccess=0;
//    qcc->CSRAddr.r=addr;
    //qcc->CSRCmd.r=CSRCmd.r;
//	
	//CSRCmd.r = 0;
//
    //do {	
//	CSRStat=qcc->CSRStat;
    //} while(CSRStat.b.CSRDone==0);
    /* see comment in write below */
//    CSRStat=qcc->CSRStat;
//
    //data=qcc->CSRRdData.r;
//    if((CSRStat.b.CSRRespID!=blockid) || (CSRStat.b.CSRRespLen!=CSRCmd.b.CSRLen) || CSRStat.b.CSRErr)
    //{	
//	puts("QCC read at address ");
	//putint(blockid);
//	puts(":");
	//puthex(addr);
//	puts(" failed, CSRStat=");
	//puthex(CSRStat.r);
//	puts("\n");
	//BUG();
//	/*return 0xFFFFFFFF;*/
    //};
//    CSRStat.b.CSRDone=1;
    //qcc->CSRStat.r=CSRStat.r;
//    return data;
//}
//
/* Write to a register in QCC space */
//int qcc_write(int blockid, uint32_t addr, uint32_t data, char size)
//{	
    //qccbridge_t *qcc=(qccbridge_t *)MERLIN_QCCBRIDGE_BASE;
//    qccreg_CSRCmd_t CSRCmd;
    //qccreg_CSRStat_t CSRStat;
//	
	//CSRCmd.r = 0;
//
    //CSRCmd.b.CSRBlockID=blockid;
//    CSRCmd.b.CSRLen=size & 3;
    //CSRCmd.b.CSRAccess=1;
//    qcc->CSRAddr.r=addr;
    //qcc->CSRWrData.r=data;
//    qcc->CSRCmd.r=CSRCmd.r;
//
    //do {	
//	CSRStat=qcc->CSRStat;
    //} while(CSRStat.b.CSRDone==0);
//    /* The hardware(at least on the FPGA, appears to be updating the done bit 
    //*  before the other bits, so we can exist the above loop with the wrong
//    *  data.  do one more read of the register and we should get the correct
    //*  data
//    */
    //CSRStat=qcc->CSRStat;
//
    //if((CSRStat.b.CSRRespID!=blockid) || (CSRStat.b.CSRRespLen!=1) || CSRStat.b.CSRErr)
//    {	
	//puts("QCC write at address ");
//	putint(blockid);
	//puts(":");
//	puthex(addr);
	//puts(" failed, CSRStat=");
//	puthex(CSRStat.r);
	//puts("\n");
//	BUG();
	/*return -EIO;*/
//    };
//
    //CSRStat.b.CSRDone=1;
//    qcc->CSRStat.r=CSRStat.r;
//
    //return 0;
//}
