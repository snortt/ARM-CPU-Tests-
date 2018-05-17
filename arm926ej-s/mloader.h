/**mloader.h
 * This file contains some merlinloader parameters.
 */

//#ifndef __MLOADER_H
//#define	__MLOADER_H

//#define	MLOADER_BANNER	"\n\nMerlin Loader (Copyright Mobilygen Corp.)" 

/* console config options */
//#define CONSOLE_BAUDRATE	115200
//#define CONSOLE_PARITY		'n'
//#define CONSOLE_NBITS		8
//#define CONSOLE_BITSTOP		1

/* BootROM parameters */
//#define MAINSTACK_SIZE	1536
//#define EXCSTACK_SIZE	512
//#define	BOOTADDR_DDR		0xC0000000

/* X Modem protocol parameters */
//#define XMODEM_WAIT_CONNECTION		1500000
//#define XMODEM_CONNECTION_TIMEOUT	15000000
//#define XMODEM_2NDEOT_TIMEOUT		1000000

//#ifndef __ASM__

/* Standard includes */
//#include "types.h"
//#include "errno.h"
//#include "debug.h"
//#include "libc.h"

//extern void ddrcopy(uint32_t src, uint32_t dst, uint32_t size);
//extern int ddr_load(void);
//extern int nand_init(void);
//extern int nand_load(void);
//extern int nor_init(void);
//extern int nor_load(void);
//extern int flash_load(void);
//extern int xmodem_init(void);
//extern int xmodem_load(void);
//extern int pll0_init(void);

//#define MERLINLOADER_MAGIC_MARKER	0x4D4C4541  /* MLEA */

//#define IH_MAGIC        0x27051956      /* Image Magic Number           */
//#define IH_NMLEN                32      /* Image Name Length            */

/* 32bit endian swap */
//#define SWAP32(x) \
//    (((x & 0xff000000) >> 24) | \
//     ((x & 0x00ff0000) >> 8 ) | \
//     ((x & 0x0000ff00) << 8 ) | \
//     ((x & 0x000000ff) << 24))
/*  
*  WARNING - the boot_devs table and defines below
*  must exactly match the order defined in the following 
*  enum found *  in the cfg2env tool.
*
typedef enum {
    BOOT_DEVICE_DDR	    = 0x0,
    BOOT_DEVICE_NAND    = 0x1,
    BOOT_DEVICE_NOR     = 0x2,
    BOOT_DEVICE_XMODEM  = 0x3,
    BOOT_DEVICE_USB    	= 0x4,
    BOOT_DEVICE_ENET  	= 0x5,
    BOOT_DEVICE_MEMTEST = 0x6,
    BOOT_DEVICE_JTAG    = 0x7,
    BOOT_DEVICE_QUERY   = 0xA,
} boot_device_t;
*/

//#define BOOT_DEVICE_DDR			0x0
//#define BOOT_DEVICE_NAND    	0x1
//#define BOOT_DEVICE_NOR     	0x2
//#define BOOT_DEVICE_XMODEM  	0x3
//#define BOOT_DEVICE_USB    		0x4
//#define BOOT_DEVICE_ENET  		0x5
//#define BOOT_DEVICE_MEMTEST  	0x6
//#define BOOT_DEVICE_JTAG  	    0x7
/* these means read the LOR and query the boot device */
//#define BOOT_DEVICE_QUERY  	    0xA

//#define NUMBER_BOOT_DEVICES     9

/* these arrays will hold the offset in the env
*  to the different device sections
*/
//uint32_t device_bootparam_offset[NUMBER_BOOT_DEVICES];
//uint32_t device_driver_offset[NUMBER_BOOT_DEVICES];

//#define CMDLINE_MAX_LEN  256
//struct linux_section_defs {
//    uint32_t kern_addr;
//    uint32_t initrd_addr;
//    char cmdline[CMDLINE_MAX_LEN]; /* XXX size ?? */
//};

//struct linux_section_defs linux_defs;

//struct bootparams_section_defs {
//    uint8_t devID;
//    uint32_t kern_addr;
//    uint32_t kern_size;
//    uint8_t  kern_type;
//    uint8_t  kern_copies; /* may have multiple copies in some devices */
//    uint16_t kern_stride; /* how many blocks to skip to find next images */
//    uint32_t initrd_addr;
//    uint32_t initrd_size;
//    uint8_t  initrd_type;
//    uint8_t  initrd_copies; /* may have multiple copies in some devices */
//    uint16_t initrd_stride;/* how many blocks to skip to find next images */
//	uint8_t  run_memtst;
//};

//struct bootparams_section_defs bootparams_defs;

/*
 * all data in network byte order (aka natural aka bigendian)
 */
//typedef struct image_header {
//        uint32_t        ih_magic;       /* Image Header Magic Number    */
//        uint32_t        ih_hcrc;        /* Image Header CRC Checksum    */
//        uint32_t        ih_time;        /* Image Creation Timestamp     */
//        uint32_t        ih_size;        /* Image Data Size              */
//        uint32_t        ih_load;        /* Data  Load  Address          */
//        uint32_t        ih_ep;          /* Entry Point Address          */
//        uint32_t        ih_dcrc;        /* Image Data CRC Checksum      */
//        uint8_t         ih_os;          /* Operating System             */
//        uint8_t         ih_arch;        /* CPU architecture             */
//        uint8_t         ih_type;        /* Image Type                   */
//        uint8_t         ih_comp;        /* Compression Type             */
//        uint8_t         ih_name[IH_NMLEN];      /* Image Name           */
//} image_header_t;

/* taken directly from the bootrom, these are the external LOR settings */
//typedef enum {
//	CONFIG_NONE=-1,
//	CONFIG_LOAD_NAND_CS1_08L01G=0x0,
//	CONFIG_LOAD_NAND_CS1_08L02G=0x1,
//	CONFIG_LOAD_NAND_CS1_16L01G=0x2,
//	CONFIG_LOAD_NAND_CS1_16L02G=0x3,
//	CONFIG_LOAD_NAND_CS1_08S256M=0x4,
//	CONFIG_LOAD_NAND_CS1_08S512M=0x5,
//	//CONFIG_LOAD_USB_PID0=0x6,
//	//CONFIG_LOAD_USB_PID1=0x7,
//	//CONFIG_LOAD_USB_SPIID=0x8,
//	CONFIG_LOAD_SPI=0x9,
//	CONFIG_LOAD_BOOTP=0xA,
//	CONFIG_LOAD_XMODEM=0xB,
//	CONFIG_BOOT_DISABLE=0xC,
//	CONFIG_BOOT_DDR=0xD,
//	//CONFIG_LOAD_NOR_CS0=0xE,
//	//CONFIG_BOOT_NOR_CS0_16MB=0xF,   /* default */
//} bootrom_config_t;

//#endif	/* #ifndef __ASM__ */

//#endif	/* #ifndef __MLOADER_H */
