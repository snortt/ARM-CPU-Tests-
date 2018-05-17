/**xmodem.c
 * This file contains the X Modem loader
 */

//#include "mloader.h"
//#include "env.h"
//#include "uart.h"
//#include "ddr_regs.h"

//#ifdef CONFIG_XMODEM 

/* X Modem protocol commands */
//#define XMODEM_NCG	'C'
//#define XMODEM_SOH	1
//#define XMODEM_STX	2
//#define XMODEM_EOT	4
//#define XMODEM_ACK	6
//#define XMODEM_NAK	21
//#define XMODEM_CAN	24

/* Only select one of those */
//#undef XMODEM_USE_DATATABLE
//#undef XMODEM_USE_BSSTABLE
//#define XMODEM_USE_ALGO

//#if defined(XMODEM_USE_DATATABLE)

//static unsigned short crcTable[] = {
//	   0,     4129,     8258,    12387,    16516,    20645,    24774,    28903,
//   33032,    37161,    41290,    45419,    49548,    53677,    57806,    61935,
//    4657,      528,    12915,     8786,    21173,    17044,    29431,    25302,
//   37689,    33560,    45947,    41818,    54205,    50076,    62463,    58334,
//    9314,    13379,     1056,     5121,    25830,    29895,    17572,    21637,
//   42346,    46411,    34088,    38153,    58862,    62927,    50604,    54669,
//   13907,     9842,     5649,     1584,    30423,    26358,    22165,    18100,
//   46939,    42874,    38681,    34616,    63455,    59390,    55197,    51132,
//   18628,    22757,    26758,    30887,     2112,     6241,    10242,    14371,
//   51660,    55789,    59790,    63919,    35144,    39273,    43274,    47403,
//   23285,    19156,    31415,    27286,     6769,     2640,    14899,    10770,
//   56317,    52188,    64447,    60318,    39801,    35672,    47931,    43802,
//   27814,    31879,    19684,    23749,    11298,    15363,     3168,     7233,
//   60846,    64911,    52716,    56781,    44330,    48395,    36200,    40265,
//   32407,    28342,    24277,    20212,    15891,    11826,     7761,     3696,
//   65439,    61374,    57309,    53244,    48923,    44858,    40793,    36728,
//   37256,    33193,    45514,    41451,    53516,    49453,    61774,    57711,
//    4224,      161,    12482,     8419,    20484,    16421,    28742,    24679,
//   33721,    37784,    41979,    46042,    49981,    54044,    58239,    62302,
//     689,     4752,     8947,    13010,    16949,    21012,    25207,    29270,
//   46570,    42443,    38312,    34185,    62830,    58703,    54572,    50445,
//   13538,     9411,     5280,     1153,    29798,    25671,    21540,    17413,
//   42971,    47098,    34713,    38840,    59231,    63358,    50973,    55100,
//    9939,    14066,     1681,     5808,    26199,    30326,    17941,    22068,
//   55628,    51565,    63758,    59695,    39368,    35305,    47498,    43435,
//   22596,    18533,    30726,    26663,     6336,     2273,    14466,    10403,
//   52093,    56156,    60223,    64286,    35833,    39896,    43963,    48026,
//   19061,    23124,    27191,    31254,     2801,     6864,    10931,    14994,
//   64814,    60687,    56684,    52557,    48554,    44427,    40424,    36297,
//   31782,    27655,    23652,    19525,    15522,    11395,     7392,     3265,
//   61215,    65342,    53085,    57212,    44955,    49082,    36825,    40952,
//   28183,    32310,    20053,    24180,    11923,    16050,     3793,     7920,
//};

//static inline unsigned short crccalc(char const message[], int nBytes)
//{
//    unsigned short remainder = 0;
//    unsigned char  data;
//    int            byte;
//
//    for (byte = 0; byte < nBytes; ++byte) {
//        data = message[byte] ^ (remainder >> 8);
//        remainder = crcTable[data] ^ (remainder << 8);
//    }
//    return remainder;
//} 

//#elif defined(XMODEM_USE_BSSTABLE)
//
//unsigned short accum_table[256];
//
//int crccalc_init(void)
//{	int n;
//	for(n=0; n<256; n++)
//	{	unsigned short accum=0;
//		int c;
//		for(c=0; c<8; c++) 
//		{	if(((n<<(c+8)) ^ accum) & 0x8000)
//				accum=(accum<<1) ^ 0x1021;
//			else 
//				accum<<=1;
//		};
//		accum_table[n]=accum;
//	};
//	return 0;
//}
//
//unsigned short crccalc(char const message[], int nBytes)
//{	unsigned short crc=0;
//	int i;
//	for(i=0; i<nBytes; i++) 
//		crc=(crc<<8) ^ accum_table[message[i] ^ (crc>>8)];
//	return crc;
//}
//
//#elif defined(XMODEM_USE_ALGO)
//
//unsigned short crccalc(char const message[], int nBytes)
//{	unsigned short crc=0;
//	int i;
//	for(i=0; i<nBytes; i++) 
//	{	unsigned short accum=0;
//		char c;
//		unsigned short index=((crc>>8)^message[i])<<8;
//
//		for(c=0; c<8; c++) {	
//			if(((index<<c) ^ accum) & 0x8000)
//				accum=(accum<<1) ^ 0x1021;
//			else 
//				accum<<=1;
//		};
//		crc=(crc<<8) ^ accum;
//	}
//	return crc;
//}
//
//#endif

/* This API does not support the original xMODEM protocol but the
* XMODEM CRC protocol as well as XMODEM1K protocol.
 */
//int xmodem_load_img(char *buf, uint32_t *img_size)
//{	
//	int timeout, ntx;
//	unsigned long packetid;
//	char tmp[2];
//	image_header_t *hdr;
//
//	/* Send the ready to receive character and wait for a connection
//	 * If nothing do it again forever 
//	 */
//	*img_size = 0;
//	timeout=XMODEM_WAIT_CONNECTION;
//	while(1)
//	{	
//		if (timeout==XMODEM_WAIT_CONNECTION) {	
//			tmp[0]=XMODEM_NCG;
//			uart_write(tmp, 1);
//			timeout=0;
//		};
//		if (uart_read_nowait(tmp, 1) != 0)
//			break;
//
//		timeout++;
//	};
//	packetid=1;
//	ntx=0;
//	while(1) {
//
//		int pktsize;
//		unsigned short crc;
//
//		if(tmp[0]==XMODEM_SOH)
//			/* XMODEM 128B packet */
//			pktsize=128;
//		else if(tmp[0]==XMODEM_STX)
//			/* XMODEM 1kB packet */
//			pktsize=1024;
//		else if(tmp[0]==XMODEM_EOT) {	
//			/* End of transmission, we send an ACK and wait for another EOT */
//			tmp[0]=XMODEM_ACK;
//			uart_write(tmp, 1);
//			timeout=XMODEM_2NDEOT_TIMEOUT;
//			while(timeout--) {	
//				if(uart_read_nowait(tmp, 1)!=0) {	
//					if(tmp[0]==XMODEM_EOT) {	
//						tmp[0]=XMODEM_ACK;
//					} 
//					else {	
//						tmp[0]=XMODEM_NAK;
//						ntx=-EIO;
//					};
//					uart_write(tmp, 1);
//					break;
//				};
//			};
//			/* We timed out, the downloader probably 
//			*  does not follow that part of the protocol */
//			goto out;
//		} 
//		else {	
//			/* error, we cancel transfer 
//			*  (always send 2 CAN, because one may be ignored) */
//			tmp[0]=XMODEM_CAN;
//			tmp[1]=XMODEM_CAN;
//			uart_write(tmp, 2);
//			return -EIO;
//		};
//		/* Check packet number */
//		uart_read(tmp, 2);
//		if (tmp[0]+tmp[1] != 255) {	
//			/* error, we cancel transfer 
//			*  (always send 2 CAN, because one may be ignored) */
//			tmp[0]=XMODEM_CAN;
//			tmp[1]=XMODEM_CAN;
//			uart_write(tmp, 2);
//			return -EIO;
//		} 
//		else if(tmp[0] != (packetid & 0xFF)) {	
//			/* if the packetid is incorrect but the sum of packetid is correct
//			* the uploader may be trying to send again an old packet
//			* => we try to restart at that packet ID with some restrictions 
//			* note that the very first packet num is one but after that it
//			* will wrap to zero
//			 */
//			if((packetid & 0xFF) < tmp[0])
//				packetid-=256-(tmp[0]-(packetid & 0xFF));
//			else 
//				packetid-=(packetid & 0xFF)-tmp[0];
//			/* assume all packets are the same size here */
//			ntx=(packetid-1)*pktsize;
//
//			/* if we enter this else if statement on the very first packet we
//			*  have to reset the size so that we ddrcopy the data again,
//			*  otherwise, we will lose the kernel data when the packet is 
//			*  re-written
//			 */
//			if (packetid == 1)
//				*img_size = 0;
//		};
//		/* read the data ! */
//		uart_read(&buf[ntx], pktsize);
//		/* Check CRC */
//		uart_read(tmp, 2);
//		crc=crccalc(&buf[ntx], pktsize);
//		/* Updated variables and get to the next header */
//		if (crc == ((tmp[0]<<8)|tmp[1])) {
//
//			if (packetid == 1 && *img_size == 0) {
//				/* we are about to ack the first packet, 
//				*  so check if magic num is correct, if yes,
//				*  relocate the real kernel data(overwrite 
//				*  img header) and set index(ntx) to start after
//				*  newly relocated kernel data.  All this will
//				*  save us the effort of copying and then relocating 
//				*  the images!
//			    */
//				hdr = (image_header_t*)buf;
//				if (SWAP32(hdr->ih_magic) != IH_MAGIC) {
//					tmp[0]=XMODEM_CAN;
//					tmp[1]=XMODEM_CAN;
//					uart_write(tmp, 2);
//					error("Bad Magic Number\n");
//					return -EINVAL;
//				}
//				*img_size = SWAP32(hdr->ih_size);
//				ddrcopy((uint32_t)(buf+sizeof(image_header_t)), 
//						(uint32_t)buf, 
//						pktsize-sizeof(image_header_t));
//
//				ntx += (pktsize - sizeof(image_header_t));
//			}
//			else {
//				ntx+=pktsize;
//			}
//			tmp[0]=XMODEM_ACK;
//			packetid++;
//		} 
//		else {
//			tmp[0]=XMODEM_NAK;
//		}
//		uart_write(tmp, 1);
//
//		timeout=XMODEM_CONNECTION_TIMEOUT;
//		while(timeout--) {
//			if(uart_read_nowait(tmp, 1)!=0) {
//				break;
//			}
//		}
//		if(timeout==0) {	
//			/* Connection timed-out, we cancel transfer 
//			*  (always send 2 CAN, because one may be ignored) */
//			tmp[0]=XMODEM_CAN;
//			tmp[1]=XMODEM_CAN;
//			uart_write(tmp, 2);
//			return -ETIMEDOUT;
//		};
//	};
//
//out:
//	return ntx;
//}

//int xmodem_load()
//{
//
//	int ret=0;
//	char tmp;
//	uint32_t img_dst, *img_size;
//	uint8_t i;
//
//	/* Workaround for the bootROM: with HyperTerminal the EOT will not 
//	 * be acknowledged properly by the BootROM, we do it here 
//	 */
//	tmp=XMODEM_ACK;
//	uart_write(&tmp, 1);
//	debug("xmodem_load\n");
//	/* 0 for the kernel, 1 for initrd(if it exist) */
//	for (i=0;i<2;i++) {
//
//		if (i == 0) {
//			//img_dst = linux_defs.kern_addr;
//			//img_size = &bootparams_defs.kern_size;
//			/*info("\nReady to receive kernel image\n");*/
//			info("\nPronto para receber imagem do kernel\n");
//		}
//		else {
//			img_dst = linux_defs.initrd_addr;
//			img_size = &bootparams_defs.initrd_size;
//			if(img_dst != 0)
//				/*info("\nReady to receive initrd image\n");*/
//				info("\nPronto para receber imagem initrd\n");
//			else continue;
//		}
//
//		/* keep trying until success */
//		do {
//			ret = xmodem_load_img((char *)img_dst, img_size);
//
//			if (ret < 0) 
//			{	/*error("Xmodem load error ");*/
//			{	error("Erro de carga Xmodem ");
//				putint(ret);
//				/*error(", try again\n");*/
//				error(", tente novamente\n");
//			};
//		} while(ret < 0);
//	}
//
//	return(ret);
//}

//int xmodem_init()
//{
//	int baudrate, databits, stopbits;
//	char parity;
//
//	/* add one to skip devID */
//	env_seek(device_driver_offset[BOOT_DEVICE_XMODEM]+1, ENV_SEEK_SET); 
//
//	baudrate = env_read(4);
//	databits = env_read(1);
//	parity   = env_read(1);
//	stopbits = env_read(1);
//
//	uart_init(baudrate, databits, parity, stopbits, 1);  /* override */
//
//#ifdef XMODEM_USE_BSSTABLE
//	/* Initialize the CRC table */
//	crccalc_init();
//#endif
//	
//	return(0);
//}
//
//#endif // XMODEM_CONFIG
