//#include "env.h"
//#include "qcc.h"
//#include "qcc_regs.h"
//#include "ddr_regs.h"
//#include "memtest.h"
/* 
*  this file will handle private processing of the env needed for
*  early startup and also provide an API to the drivers so 
*  they can get access also
*
*  - at startup, process the entire env.  Look for CSR and ARM 
*  sections, running the commands/section as they are found in the
*  order they are found.
 */

//extern uint32_t xin_rate;
/* this is the global ptr which is used for all access to the env. drivers
*  should access this via the env_* API calls NOT directly
 */
char *env_ptr = (char*) &_envstart;

uint32_t env_read_data(uint8_t size, uint8_t inc)
{
	uint32_t data;

	switch (size) { 
		case 1: data = *env_ptr & 0xFF;
				break;
		case 2: data = (*(env_ptr+0) << 8 | *(env_ptr+1)) & 0xFFFF;
				break;
		case 4: data =  *(env_ptr+0) << 24 | 
				*(env_ptr+1) << 16 | 
					*(env_ptr+2) <<  8 | 
					*(env_ptr+3);
				break;
		default: 
				/* illegal read size, don't bump the env_ptr, this should never
				*  happen */
				size = 0;
				data = 0;
	}
	if (inc == ENVPTR_INCREMENT)
		env_ptr += size;

	return(data);
}

/* reset the env_ptr some offset in the env */
void env_seek(uint32_t offset, uint8_t whence)
{
	switch (whence) {
		case ENV_SEEK_SET: env_ptr = (char*)(&_envstart) + offset;
			break;
		case ENV_SEEK_CUR: env_ptr += offset;
			break;
	}
}

/* returns the current position of the env_ptr */
#define env_tell() ((uint32_t)env_ptr)
/* returns value when env started */
#define env_start() ((uint32_t)&_envstart)

#define CONDITION_CODE_EQ	0x1
#define CONDITION_CODE_NE	0x2
#define CONDITION_CODE_LT	0x3
#define CONDITION_CODE_LE	0x4
#define CONDITION_CODE_GT	0x5
#define CONDITION_CODE_GE	0x6

int process_reg_cmds(uint16_t section_type, 
		uint32_t section_start, uint32_t section_size)
{

	/* first pass, will do env_read to get data, 
	*  once I redo the endianess of the env, I should just be
	*  able to use ptrs
	 */
	uint8_t cmd, size, blockID, condition_true;
	uint32_t addr, data, mask, read_data;

	do {

		cmd = env_read(1);
		/* get the three defaults here except for delay */
		if (section_type == ENV_CSR_SECTION) {
			if (cmd != 'D') {
				blockID = env_read(1);
				addr = env_read(2);
				size = env_read(1);
			}
		}
		else {
			addr = env_read(4);
		}

		switch (cmd) {
			case 'W': 
				data = env_read(4);
				if (section_type == ENV_CSR_SECTION) {
					qcc_write(blockID, addr, data, size);
				}
				else {
					*(uint32_t*)addr = data;
				}
				break;
			case 'R':
				if (section_type == ENV_CSR_SECTION) {
					read_data = qcc_read(blockID, addr, size);
				}
				else {
					read_data = *(uint32_t*)addr;
				}
				break;
			case 'P':
				/* poll, read until value match */
				data = env_read(4);
				mask = env_read(4);
				do {
					if (section_type == ENV_CSR_SECTION) {
						read_data = qcc_read(blockID, addr, size);
					}
					else {
						read_data = *(uint32_t*)addr;
					}
				} while ((read_data & mask) != (data & mask));
				break;
			case 'C':
				/* check if equal unless a condition is given */
				/* if result of test condition is false, we jmp to the 
				*  end of this section, skipping all remaining commands. we
				*  can do if/else this way by including another CSR section 
				*  after this
				 */
				data = env_read(4);
				mask = env_read(4);
				if (section_type == ENV_CSR_SECTION) {
					read_data = qcc_read(blockID, addr, size);
				}
				else {
					read_data = *(uint32_t*)addr;
				}
				condition_true = 0;
				switch (env_read(1)) {
					case CONDITION_CODE_EQ: 
						if ((read_data & mask) == (data & mask))
							condition_true = 1;
						break;
					case CONDITION_CODE_NE: 
						if ((read_data & mask) != (data & mask))
							condition_true = 1;
						break;
					case CONDITION_CODE_LT: 
						if ((read_data & mask) < (data & mask))
							condition_true = 1;
						break;
					case CONDITION_CODE_LE: 
						if ((read_data & mask) <= (data & mask))
							condition_true = 1;
						break;
					case CONDITION_CODE_GT: 
						if ((read_data & mask) > (data & mask))
							condition_true = 1;
						break;
					case CONDITION_CODE_GE: 
						if ((read_data & mask) >= (data & mask))
							condition_true = 1;
						break;
				}
				if (!condition_true) {
					/* then don't process any more cmd in this section */
					env_seek(section_start - env_start(), ENV_SEEK_SET);
					env_seek(section_size, ENV_SEEK_CUR);
				}
				break;
			case 'M':
				/* read, modify, write */
				data = env_read(4);
				mask = env_read(4);
				if (section_type == ENV_CSR_SECTION) {
					read_data = qcc_read(blockID, addr, size);
				}
				else {
					read_data = *(uint32_t*)addr;
				}
				read_data &= ~(mask);
				read_data |= data;

				if (section_type == ENV_CSR_SECTION) {
					qcc_write(blockID, addr, read_data, size);
				}
				else {
					*(uint32_t*)addr = read_data;
				}
				break;
			case 'D':
				/* Delay, re-used addr for tmp var */
				addr = env_read(4);
				for (mask=0;mask<addr;mask++);

				break;
		}
	} while ((env_tell() - section_start) != section_size);

	return(0);
}

int env_init(void)
{

	uint16_t section_type;
	uint32_t section_size;
	uint32_t env_size;
	uint32_t rword;

	env_size = env_read(4);
	bootparams_defs.run_memtst = 0;

	/* sooo, we can't print anything until we have processed the env.  the
	*  reason is because for the uart to work, the pll has to be initialized
	*  and that has to happen here first.  In addtion, we may need to use a
	*  different uart setup than the default so we have to read the env for 
	*  that also(after it's been implemented)
	*
	*  the exception is while we are doing bringup/testing on the fpga.  debug
	*  is enabled for the bootrom and it takes care of initializing everything
	*  so we can print immediatly but that won't be true for the chip!
	 */
	//memset(device_bootparam_offset, 0x0, NUMBER_BOOT_DEVICES);
	while((uint32_t)env_ptr - (uint32_t) &_envstart < env_size) {

		section_type = env_read(2);
		dputs("stype: ");dputhex(section_type);dputs("\n");
		if (section_type >= ENV_VERSION_SECTION && section_type < ENV_END) {
			section_size = env_read(4);
		}
	if (section_size == 0)
			continue;

		switch(section_type) { 
			case ENV_VERSION_SECTION:
				rword = env_read(4);
				info("Env version: ");puthex(rword);info("\n");
				break;
			case ENV_CSR_SECTION:
		case ENV_CLOCK_SECTION:
				/* a clock section is just a csr section that is specially flagged
				*  so just set section type arg to always be CSR for the case 
				*/
				/* process QCC cmds */
			if (section_size != 0) 
					process_reg_cmds(ENV_CSR_SECTION, env_tell(), section_size);
				break;
			case ENV_ARM_SECTION:
				/* process arm cmds */
				if (section_size != 0) 
					process_reg_cmds(section_type, env_tell(), section_size);
				break;
			//case ENV_LINUX_SECTION:
			//	linux_defs.kern_addr = env_read(4);
			//	linux_defs.initrd_addr = env_read(4);
			//	strcpy(linux_defs.cmdline, env_ptr);
			//	/* -8 for the two prev reads and we have the length of the cmdline */
			//	env_seek(section_size-8, ENV_SEEK_CUR);
			//	break;
			//case ENV_BOOTPARAMS_SECTION:
			//	//bootparams_defs.devID = env_read_nc(1);
			//	/* save offset to this devices bootparams, skip header */
			//	/* read devID without inc. the env_ptr so we can easily skip
			//	*  to the end of the section
			//	 */
			//	//device_bootparam_offset[env_read_nc(1)] = (uint32_t)(env_ptr - env_start());
			//	env_seek(section_size, ENV_SEEK_CUR);
			//	break;
			//case ENV_DRIVER_SECTION:
			//	//puts("found driver for dev ");puthex(env_read_nc(1));puts("\n");
			//	device_driver_offset[env_read_nc(1)] = (uint32_t)(env_ptr - env_start());
			//	if (env_read_nc(1) == BOOT_DEVICE_MEMTEST)
			//		bootparams_defs.run_memtst = 1;
			//	env_seek(section_size, ENV_SEEK_CUR);
			//	break;
			case ENV_SYSTEM_SECTION:
				fputs("process system section, size ");fputhex(section_size);fputs("\n");
				switch (env_read(1)) {
					case 'U': 
						uart_init(env_read(4), //CONSOLE_BAUDRATE, 
								env_read(1), //CONSOLE_NBITS, 
								env_read(1), //CONSOLE_PARITY, 
								env_read(1), //CONSOLE_BITSTOP;
								0);  /* override */
						break; 
					case 'X': 
						xin_rate = env_read(4);
						break;
				}
				break;
			//case ENV_BOOTDEVICE_SECTION:
			//	bootparams_defs.devID = env_read(1);
			//	//fputs("found bootdevice ");fputhexb(bootparams_defs.devID);fputs("\n");
			//	break;
			case ENV_DEBUG_SECTION:
				puts("process debug section, size "); puthex(section_size);puts("\n");
				env_seek(section_size, ENV_SEEK_CUR);
				break;
			case ENV_END:
				puts("env_end ");puthex((uint32_t)env_ptr); puts("\n");
				break;
			default:
				puts("Unrecognized section\n");
				return(-1);
		}
	}
	/* so if we reach this point it means
	*  - we've processed all the csr sections
	*  - we've processed all the arm sections
	*  - we've saved the linux section data
	*  - we've saved the bootparams
	*  - we know which device and we have to address to 
	*    the env's devices section.
	*  - save clock section address
	*  - probably have proccesed debug section
	*  - return to main, just to device creation.
	*/
	return(0);
}
