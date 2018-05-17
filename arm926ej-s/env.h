/*
* env.h  
* 	- define parameters and API for access the environment
*/

#ifndef __ENV_H
#define	__ENV_H

/* Standard includes */
#include "types.h"
#include "errno.h"
#include "debug.h"
#include "libc.h"

extern void **_envstart;

/* API calls into the env */
int env_init(void);
uint32_t env_read_data(uint8_t, uint8_t);

#define ENVPTR_INCREMENT  0x1
#define ENVPTR_NOCHANGE   0x2

#define env_read(x)	env_read_data(x, ENVPTR_INCREMENT)
#define env_read_nc(x)  env_read_data(x, ENVPTR_NOCHANGE)

#define ENV_SEEK_SET 0x1
#define ENV_SEEK_CUR 0x2
void env_seek(uint32_t offset, uint8_t whence);

/* 
*  layout env is like this, starting at envstart
*  1st word:  magic_marker 'MLEA'
*  2nd word:  env size
*  sections defined in enum below.  format of sections
*  is as follow
*  1st byte: section id
*  2nd short: section size
*  remaining size:  section specific data/format
*/

typedef enum {
    /* Version number of the environment */
    ENV_VERSION_SECTION = 0x1,

    /* List of QCC read, writes and poll */
    ENV_CSR_SECTION	= 0x2,

    /* list of ARM register read, writes and poll */
    ENV_ARM_SECTION	= 0x3,

    /* contains the following
    *    - final address of kernel in memory
    *    - final address of initrd in memory
    *    - kernel cmdline
    */
    ENV_LINUX_SECTION	= 0x4,

    /* contains the following
    *    - ID of device where kernel is
    *    - address of kernel on device
    *    - size of kernel
    *    - type of kernel(un/compressesed..)
    *    - address of initrd on device
    *    - size of initrd
    *    - type of initrd(un/compressesed..)
    *    - how many copies of kernel exist on the device
    */
    ENV_BOOTPARAMS_SECTION = 0x5,

    /* contains information necessary for the initialization 
    *  and operation of the boot device(identified in the previous
    *  section.  Format of section is unique to the given driver 
    */
    ENV_DRIVER_SECTION	= 0x6,

    /* will contain expected clock rates */
    ENV_CLOCK_SECTION	= 0x7,

    /* misc system stuff */
    ENV_SYSTEM_SECTION	= 0x8,

    /* misc system stuff */
    ENV_BOOTDEVICE_SECTION = 0x9,

    /* used to enable debug message, test, etc */
    ENV_DEBUG_SECTION	= 0xA,

    /* need to indicate when finished */
    ENV_END = 0xB
} mloader_env_section_t;

#endif	/* #ifndef __ENV_H */
