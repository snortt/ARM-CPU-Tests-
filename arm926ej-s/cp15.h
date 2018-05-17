/* Vamos obter informações relacionadas ao CP15
* Em MG3500.s temos:
; --------------------------------------------
; get ID
				EXPORT  read_CP15_c0_id
read_CP15_c0_id
   				MRC 	p15, 0, R0, c0, c0, 0
				BX		LR

; get cache
				EXPORT  read_CP15_c0_cache
read_CP15_c0_cache
   				MRC 	p15, 0, R0, c0, c0, 1
				BX		LR

; TCM status
				EXPORT read_CP15_c0_tcm
read_CP15_c0_tcm
				MRC		p15, 0, R0, c0, c0, 2
				BX	    LR

; Control Register
				EXPORT read_CP15_c1
read_CP15_c1
				MRC		p15, 0, R0, c1, c0, 0
				BX	    LR

; Read TCM region data register c9
				EXPORT read_CP15_tcm_rd
read_CP15_tcm_rd
				MRC p15, 0, R0, c9, c1, 0
				BX LR

; Readn TCM region instruction register
				EXPORT read_CP15_tcm_ri
read_CP15_tcm_ri
				MRC p15, 0, R0, c9, c1, 1
				BX LR
; --------------------------------------------
* 
*/

/* Registrador c0 : aqui pegaremos ID Code, Cache Type e TCM Status
*	--------------------------------------------------------------------
*	ID Code: MRC p15, 0, <Rd>, c0, c0, {0, 3-7} ;returns ID
* 	Register bits: 	Function Value:
* 	[31:24] 		ASCII code of implementer trademark 0x41
*	[23:20] 		Variant 0x0
*	[19:16] 		Architecture (ARMv5TEJ) 0x6
*	[15:4] 		Part number 0x926
*	[3:0]			Revision 0x05a
*
*	--------------------------------------------------------------------
*	Cache Type: MRC p15, 0, <Rd>, c0, c0, 1; returns cache details
*	Size field:		Cache size:
*	b0011		4KB
*	b0100		8KB
*	b0101		16KB
*	b0110		32KB
*	b0111			64KB
*	b1000		128KB
*
*	Function		Register bits	Value
*	Reserved		[31:29]		b000
*	Ctype			[28:25]		b1110
*	S 			[24] 			b1 = Harvard cache
*	Dsize
*		Reserved	[23:22]		b00
*		Size		[21:18]		b0100 = 8KB
*		Assoc	[17:15]		b010 = 4-way
*		M 		[14]			b0
*		Len		[13:12]		b10 = 8 words per line (32 bytes)
*	Isize
*		Reserved	[11:10]		b00
*		Size		[9:6]			b0101 = 16KB
*		Assoc	[5:3]			b010 = 4-way
*		M		[2]			b0
*		Len		[1:0]			b10 = 8 words per line (32 bytes)
*
*	--------------------------------------------------------------------
*	TCM Status:  MRC p15,0,<Rd>,c0,c0,2 ;returns TCM details
*	DTCM Present	[16]
*	ITCM Present	[0]
*/
unsigned int CP15_c0_id(void);
unsigned int CP15_c0_cache(void);
unsigned int CP15_c0_tcm(void);

/* Registrador c1 : aqui pegaremos informações sobre o status/uso de caches e MMU
* Utilizar eqüências read-modify-write para acessar este registrador 
*	--------------------------------------------------------------------
* Control Register
*	Bit		Name		Function
*	[31:19] 	-		Reserved. When read returns an Unpredictable value. When written, Should Be Zero, or a value read from bits [31:19] on the same processor. 
*	[18] 		-		Reserved, SBO. Read = 1, write = 1.
*	[17] 		-		Reserved, SBZ. Read = 0, write = 0.
*	[16] 		-		Reserved, SBO. Read = 1, write = 1.
*	[15] 		L4 bit	Determines if the T bit is set when load instructions change the PC: 0 = loads to PC set the T bit 1 = loads to PC do not set T bit (ARMv4 behavior).
*	[14]		RR bit	Replacement strategy for ICache and DCache: 0 = Random replacement 1 = Round-robin replacement.
*	[13] 		V bit		Location of exception vectors: 0 = Normal exception vectors, address range = 0x00000000 to 0x0000001C 1 = High exception vectors, address range = 0xFFFF0000 to 0xFFFF001C.
*	[12]		I bit		ICache enable/disable: 0 = ICache disabled 1 = ICache enabled.
*	[11:10]	-		SBZ.
*	[9]		R bit		ROM protection. This bit modifies the ROM protection system. See Domain access control on page 3-24.
*	[8]		S bit		System protection. This bit modifies the MMU protection system. See Domain access control on page 3-24.
*	[7]		B bit		Endianness: 0 = Little-endian operation 1 = Big-endian operation. Set to the value of BIGENDINIT on reset.
*	[6:3]		-		Reserved. SBO.
*	[2] 		C bit		DCache enable/disable: 0 = Cache disabled 1 = Cache enabled.
*	[1]		A bit		Alignment fault enable/disable: 0 = Data address alignment fault checking disabled 1 = Data address alignment fault checking enabled.
*	[0]		M bit		MMU enable/disable: 0 = disabled 1 = enabled.
*/
unsigned int CP15_c1(void);

/* Registrador c9 : aqui pegaremos informações a respeito dos TCM Region Registers
*	--------------------------------------------------------------------
*	MRC p15, 0, R0, c9, c1, 0 ; TCM Region Data 
*	MRC p15, 0, R0, c9, c1, 1 ; TCM Region Instruction
*	Bits:		Function:
*	[31:12]	Base address (physical address).
*	[11:6]		SBZ/UNP.
*	[5:2]		Size. The Size field reflects the value of the IRSIZE/DRSIZE macrocell inputs. (see below).
*	[1]		SBZ/UNP.
*	[0]		Enable bit: 0 = disabled 1 = enabled.
*	--------------------------------------------------------------------
*		Memory size:	Value:
*		0KB/absent		b0000
*		Reserved		b0001, b0010
*		4KB			b0011
*		8KB			b0100
*		16KB			b0101
*		32KB			b0110
*		64KB			b0111
*		128KB		b1000
*		256KB		b1001
*		512KB		b1010
*		1MB			b1011
*		Reserved		b1100, b1101, b1110, b1111
*/
unsigned int CP15_tcm_rd(void);
unsigned int CP15_tcm_ri(void);
