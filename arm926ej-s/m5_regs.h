//#ifndef M5_REGS_H
//#define M5_REGS_H

//#define QCC_BID_CHIPCTL 		8	/* Chip Control register block */

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_SerialIOControl_ADDRESS	0xe0
//#define	Reg_M5_CHIP_CTL_x_SerialIOControl_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	SerialIOControl_DBGUARTSel		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	SerialIOControl_I2C1Cfg		        : 0x01 ;	/* LSB 0x01 */
//	uint32_t	SerialIOControl_V23_MOSI_AltSel		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	SerialIOControl_V23_MCLK_AltSel		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	SerialIOControl_V01_MOSI_AltSel		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	SerialIOControl_V01_MCLK_AltSel		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	SerialIOControl_SPI_MOSI_AltSel		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	SerialIOControl_SPI_MCLK_AltSel		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	SerialIOControl_SPI_MSS0_AltSel		: 0x01 ;	/* LSB 0x08 */
//	uint32_t	SerialIOControl_SPI_MSS1_AltSel		: 0x01 ;	/* LSB 0x09 */
//	uint32_t	SerialIOControl_SPIMasterSel		: 0x01 ;	/* LSB 0x0a */
//	uint32_t	reserved_SerialIOControl_0		: 0x15 ;	/* LSB 0x0b */
//
//} Reg_M5_CHIP_CTL_x_SerialIOControl_FIELDS;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_SerialIOControl_FIELDS b;
//} Reg_M5_CHIP_CTL_x_SerialIOControl_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_GPIO1Sel_ADDRESS	0xe4
//#define	Reg_M5_CHIP_CTL_x_GPIO1Sel_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	GPIO1Sel_S0		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	GPIO1Sel_S1		: 0x01 ;	/* LSB 0x01 */
//	uint32_t	GPIO1Sel_S2		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	GPIO1Sel_S3		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	GPIO1Sel_S4		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	GPIO1Sel_S5		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	GPIO1Sel_S6		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	GPIO1Sel_S7		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	GPIO1Sel_S8		: 0x01 ;	/* LSB 0x08 */
//	uint32_t	GPIO1Sel_S9		: 0x01 ;	/* LSB 0x09 */
//	uint32_t	GPIO1Sel_S10		: 0x01 ;	/* LSB 0x0a */
//	uint32_t	GPIO1Sel_S11		: 0x01 ;	/* LSB 0x0b */
//	uint32_t	GPIO1Sel_S12		: 0x01 ;	/* LSB 0x0c */
//	uint32_t	GPIO1Sel_S13		: 0x01 ;	/* LSB 0x0d */
//	uint32_t	GPIO1Sel_S14		: 0x01 ;	/* LSB 0x0e */
//	uint32_t	GPIO1Sel_S15		: 0x01 ;	/* LSB 0x0f */
//	uint32_t	GPIO1Sel_S16		: 0x01 ;	/* LSB 0x10 */
//	uint32_t	GPIO1Sel_S17		: 0x01 ;	/* LSB 0x11 */
//	uint32_t	GPIO1Sel_S18		: 0x01 ;	/* LSB 0x12 */
//	uint32_t	GPIO1Sel_S19		: 0x01 ;	/* LSB 0x13 */
//	uint32_t	GPIO1Sel_S20		: 0x01 ;	/* LSB 0x14 */
//	uint32_t	GPIO1Sel_S21		: 0x01 ;	/* LSB 0x15 */
//	uint32_t	GPIO1Sel_S22		: 0x01 ;	/* LSB 0x16 */
//	uint32_t	GPIO1Sel_S23		: 0x01 ;	/* LSB 0x17 */
//	uint32_t	GPIO1Sel_S24		: 0x01 ;	/* LSB 0x18 */
//	uint32_t	GPIO1Sel_S25		: 0x01 ;	/* LSB 0x19 */
//	uint32_t	GPIO1Sel_S26		: 0x01 ;	/* LSB 0x1a */
//	uint32_t	GPIO1Sel_S27		: 0x01 ;	/* LSB 0x1b */
//	uint32_t	GPIO1Sel_S28		: 0x01 ;	/* LSB 0x1c */
//	uint32_t	GPIO1Sel_S29		: 0x01 ;	/* LSB 0x1d */
//	uint32_t	GPIO1Sel_S30		: 0x01 ;	/* LSB 0x1e */
//	uint32_t	GPIO1Sel_S31		: 0x01 ;	/* LSB 0x1f */
//} Reg_M5_CHIP_CTL_x_GPIO1Sel_FIELDS;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_GPIO1Sel_FIELDS b;
//} Reg_M5_CHIP_CTL_x_GPIO1Sel_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_GPIO2Sel_ADDRESS	0xe8
//#define	Reg_M5_CHIP_CTL_x_GPIO2Sel_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	GPIO2Sel_S0		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	GPIO2Sel_S1		: 0x01 ;	/* LSB 0x01 */
//	uint32_t	GPIO2Sel_S2		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	GPIO2Sel_S3		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	GPIO2Sel_S4		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	GPIO2Sel_S5		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	GPIO2Sel_S6		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	GPIO2Sel_S7		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	GPIO2Sel_S8		: 0x01 ;	/* LSB 0x08 */
//	uint32_t	GPIO2Sel_S9		: 0x01 ;	/* LSB 0x09 */
//	uint32_t	GPIO2Sel_S10		: 0x01 ;	/* LSB 0x0a */
//	uint32_t	GPIO2Sel_S11		: 0x01 ;	/* LSB 0x0b */
//	uint32_t	GPIO2Sel_S12		: 0x01 ;	/* LSB 0x0c */
//	uint32_t	GPIO2Sel_S13		: 0x01 ;	/* LSB 0x0d */
//	uint32_t	GPIO2Sel_S14		: 0x01 ;	/* LSB 0x0e */
//	uint32_t	GPIO2Sel_S15		: 0x01 ;	/* LSB 0x0f */
//	uint32_t	GPIO2Sel_S16		: 0x01 ;	/* LSB 0x10 */
//	uint32_t	GPIO2Sel_S17		: 0x01 ;	/* LSB 0x11 */
//	uint32_t	GPIO2Sel_S18		: 0x01 ;	/* LSB 0x12 */
//	uint32_t	GPIO2Sel_S19		: 0x01 ;	/* LSB 0x13 */
//	uint32_t	GPIO2Sel_S20		: 0x01 ;	/* LSB 0x14 */
//	uint32_t	GPIO2Sel_S21		: 0x01 ;	/* LSB 0x15 */
//	uint32_t	GPIO2Sel_S22		: 0x01 ;	/* LSB 0x16 */
//	uint32_t	GPIO2Sel_S23		: 0x01 ;	/* LSB 0x17 */
//	uint32_t	GPIO2Sel_S24		: 0x01 ;	/* LSB 0x18 */
//	uint32_t	GPIO2Sel_S25		: 0x01 ;	/* LSB 0x19 */
//	uint32_t	GPIO2Sel_S26		: 0x01 ;	/* LSB 0x1a */
//	uint32_t	GPIO2Sel_S27		: 0x01 ;	/* LSB 0x1b */
//	uint32_t	GPIO2Sel_S28		: 0x01 ;	/* LSB 0x1c */
//	uint32_t	GPIO2Sel_S29		: 0x01 ;	/* LSB 0x1d */
//	uint32_t	GPIO2Sel_S30		: 0x01 ;	/* LSB 0x1e */
//	uint32_t	GPIO2Sel_S31		: 0x01 ;	/* LSB 0x1f */
//} Reg_M5_CHIP_CTL_x_GPIO2Sel_FIELDS;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_GPIO2Sel_FIELDS b;
//} Reg_M5_CHIP_CTL_x_GPIO2Sel_t;

/*******************************************************************************
*
*******************************************************************************/
//#define RegF_M5_CHIP_CTL_x_reserved_SerialIODriveStrength0_0_WIDTH   0x11
//#define RegF_M5_CHIP_CTL_x_reserved_SerialIODriveStrength0_0_LSB       0x0f
//
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS2_WIDTH     0x03
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS2_LSB       0x0c
//
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR2_WIDTH     0x02
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR2_LSB       0x0a
//
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS1_WIDTH     0x03
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS1_LSB       0x07
//
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR1_WIDTH     0x02
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR1_LSB       0x05
//
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS0_WIDTH     0x03
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_DS0_LSB       0x02
//
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR0_WIDTH     0x02
//#define RegF_M5_CHIP_CTL_x_SerialIODriveStrength0_SR0_LSB       0x00
//
//#define	Reg_M5_CHIP_CTL_x_SerialIODriveStrength0_ADDRESS	0xf0
//#define	Reg_M5_CHIP_CTL_x_SerialIODriveStrength0_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	SerialIODriveStrength0_SR0		: 0x02 ;	/* LSB 0x00 */
//	uint32_t	SerialIODriveStrength0_DS0		: 0x03 ;	/* LSB 0x02 */
//	uint32_t	SerialIODriveStrength0_SR1		: 0x02 ;	/* LSB 0x05 */
//	uint32_t	SerialIODriveStrength0_DS1		: 0x03 ;	/* LSB 0x07 */
//	uint32_t	SerialIODriveStrength0_SR2		: 0x02 ;	/* LSB 0x0a */
//	uint32_t	SerialIODriveStrength0_DS2		: 0x03 ;	/* LSB 0x0c */
//	uint32_t	reserved_SerialIODriveStrength0_0	: 0x11 ;	/* LSB 0x0f */
//} Reg_M5_CHIP_CTL_x_SerialIODriveStrength0_FIELDS;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_SerialIODriveStrength0_FIELDS	b;
//} Reg_M5_CHIP_CTL_x_SerialIODriveStrength0_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_SerialIODriveStrength1_ADDRESS	0xf4
//#define	Reg_M5_CHIP_CTL_x_SerialIODriveStrength1_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	SerialIODriveStrength1_SR3		: 0x02 ;	/* LSB 0x00 */
//	uint32_t	SerialIODriveStrength1_DS3		: 0x03 ;	/* LSB 0x02 */
//	uint32_t	SerialIODriveStrength1_SR4		: 0x02 ;	/* LSB 0x05 */
//	uint32_t	SerialIODriveStrength1_DS4		: 0x03 ;	/* LSB 0x07 */
//	uint32_t	SerialIODriveStrength1_SR5		: 0x02 ;	/* LSB 0x0a */
//	uint32_t	SerialIODriveStrength1_DS5		: 0x03 ;	/* LSB 0x0c */
//	uint32_t	reserved_SerialIODriveStrength1_0	: 0x11 ;	/* LSB 0x0f */
//} Reg_M5_CHIP_CTL_x_SerialIODriveStrength1_FIELDS;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_SerialIODriveStrength1_FIELDS b;
//} Reg_M5_CHIP_CTL_x_SerialIODriveStrength1_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_SerialIODriveStrength2_ADDRESS	0xf8
//#define	Reg_M5_CHIP_CTL_x_SerialIODriveStrength2_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	SerialIODriveStrength2_SR6		: 0x02 ;	/* LSB 0x00 */
//	uint32_t	SerialIODriveStrength2_DS6		: 0x03 ;	/* LSB 0x02 */
//	uint32_t	SerialIODriveStrength2_SR7		: 0x02 ;	/* LSB 0x05 */
//	uint32_t	SerialIODriveStrength2_DS7		: 0x03 ;	/* LSB 0x07 */
//	uint32_t	SerialIODriveStrength2_SR8		: 0x02 ;	/* LSB 0x0a */
//	uint32_t	SerialIODriveStrength2_DS8		: 0x03 ;	/* LSB 0x0c */
//	uint32_t	reserved_SerialIODriveStrength2_0	: 0x11 ;	/* LSB 0x0f */
//} Reg_M5_CHIP_CTL_x_SerialIODriveStrength2_FIELDS ;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_SerialIODriveStrength2_FIELDS b;
//} Reg_M5_CHIP_CTL_x_SerialIODriveStrength2_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_SerialIODriveStrength3_ADDRESS	0xfc
//#define	Reg_M5_CHIP_CTL_x_SerialIODriveStrength3_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	SerialIODriveStrength3_SR9		: 0x02 ;	/* LSB 0x00 */
//	uint32_t	SerialIODriveStrength3_DS9		: 0x03 ;	/* LSB 0x02 */
//	uint32_t	SerialIODriveStrength3_SR10		: 0x02 ;	/* LSB 0x05 */
//	uint32_t	SerialIODriveStrength3_DS10		: 0x03 ;	/* LSB 0x07 */
//	uint32_t	SerialIODriveStrength3_SR11		: 0x02 ;	/* LSB 0x0a */
//	uint32_t	SerialIODriveStrength3_DS11		: 0x03 ;	/* LSB 0x0c */
//	uint32_t	reserved_SerialIODriveStrength3_0	: 0x11 ;	/* LSB 0x0f */
//} Reg_M5_CHIP_CTL_x_SerialIODriveStrength3_FIELDS;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_SerialIODriveStrength3_FIELDS b;
//} Reg_M5_CHIP_CTL_x_SerialIODriveStrength3_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_GPIO0PullUpEnable_ADDRESS	0x100
//#define	Reg_M5_CHIP_CTL_x_GPIO0PullUpEnable_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	GPIO0PullUpEnable_S0PUEn		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	GPIO0PullUpEnable_S1PUEn		: 0x01 ;	/* LSB 0x01 */
//	uint32_t	GPIO0PullUpEnable_S2PUEn		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	GPIO0PullUpEnable_S3PUEn		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	GPIO0PullUpEnable_S4PUEn		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	GPIO0PullUpEnable_S5PUEn		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	GPIO0PullUpEnable_S6PUEn		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	GPIO0PullUpEnable_S7PUEn		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	reserved_GPIO0PullUpEnable_0		: 0x18 ;	/* LSB 0x08 */
//} Reg_M5_CHIP_CTL_x_GPIO0PullUpEnable_FIELDS ;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_GPIO0PullUpEnable_FIELDS b;
//} Reg_M5_CHIP_CTL_x_GPIO0PullUpEnable_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_GPIO1PullUpEnable_ADDRESS	0x104
//#define	Reg_M5_CHIP_CTL_x_GPIO1PullUpEnable_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	GPIO1PullUpEnable_S0PUEn		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	GPIO1PullUpEnable_S1PUEn		: 0x01 ;	/* LSB 0x01 */
//	uint32_t	GPIO1PullUpEnable_S2PUEn		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	GPIO1PullUpEnable_S3PUEn		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	GPIO1PullUpEnable_S4PUEn		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	GPIO1PullUpEnable_S5PUEn		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	GPIO1PullUpEnable_S6PUEn		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	GPIO1PullUpEnable_S7PUEn		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	GPIO1PullUpEnable_S8PUEn		: 0x01 ;	/* LSB 0x08 */
//	uint32_t	GPIO1PullUpEnable_S9PUEn		: 0x01 ;	/* LSB 0x09 */
//	uint32_t	GPIO1PullUpEnable_S10PUEn		: 0x01 ;	/* LSB 0x0a */
//	uint32_t	GPIO1PullUpEnable_S11PUEn		: 0x01 ;	/* LSB 0x0b */
//	uint32_t	GPIO1PullUpEnable_S12PUEn		: 0x01 ;	/* LSB 0x0c */
//	uint32_t	GPIO1PullUpEnable_S13PUEn		: 0x01 ;	/* LSB 0x0d */
//	uint32_t	GPIO1PullUpEnable_S14PUEn		: 0x01 ;	/* LSB 0x0e */
//	uint32_t	GPIO1PullUpEnable_S15PUEn		: 0x01 ;	/* LSB 0x0f */
//	uint32_t	GPIO1PullUpEnable_S16PUEn		: 0x01 ;	/* LSB 0x10 */
//	uint32_t	GPIO1PullUpEnable_S17PUEn		: 0x01 ;	/* LSB 0x11 */
//	uint32_t	GPIO1PullUpEnable_S18PUEn		: 0x01 ;	/* LSB 0x12 */
//	uint32_t	GPIO1PullUpEnable_S19PUEn		: 0x01 ;	/* LSB 0x13 */
//	uint32_t	GPIO1PullUpEnable_S20PUEn		: 0x01 ;	/* LSB 0x14 */
//	uint32_t	GPIO1PullUpEnable_S21PUEn		: 0x01 ;	/* LSB 0x15 */
//	uint32_t	GPIO1PullUpEnable_S22PUEn		: 0x01 ;	/* LSB 0x16 */
//	uint32_t	GPIO1PullUpEnable_S23PUEn		: 0x01 ;	/* LSB 0x17 */
//	uint32_t	GPIO1PullUpEnable_S24PUEn		: 0x01 ;	/* LSB 0x18 */
//	uint32_t	GPIO1PullUpEnable_S25PUEn		: 0x01 ;	/* LSB 0x19 */
//	uint32_t	GPIO1PullUpEnable_S26PUEn		: 0x01 ;	/* LSB 0x1a */
//	uint32_t	GPIO1PullUpEnable_S27PUEn		: 0x01 ;	/* LSB 0x1b */
//	uint32_t	GPIO1PullUpEnable_S28PUEn		: 0x01 ;	/* LSB 0x1c */
//	uint32_t	GPIO1PullUpEnable_S29PUEn		: 0x01 ;	/* LSB 0x1d */
//	uint32_t	GPIO1PullUpEnable_S30PUEn		: 0x01 ;	/* LSB 0x1e */
//	uint32_t	GPIO1PullUpEnable_S31PUEn		: 0x01 ;	/* LSB 0x1f */
//} Reg_M5_CHIP_CTL_x_GPIO1PullUpEnable_FIELDS;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_GPIO1PullUpEnable_FIELDS b;
//} Reg_M5_CHIP_CTL_x_GPIO1PullUpEnable_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_GPIO2PullUpEnable_ADDRESS	0x108
//#define	Reg_M5_CHIP_CTL_x_GPIO2PullUpEnable_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	GPIO2PullUpEnable_S0PUEn		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	GPIO2PullUpEnable_S1PUEn		: 0x01 ;	/* LSB 0x01 */
//	uint32_t	GPIO2PullUpEnable_S2PUEn		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	GPIO2PullUpEnable_S3PUEn		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	GPIO2PullUpEnable_S4PUEn		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	GPIO2PullUpEnable_S5PUEn		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	GPIO2PullUpEnable_S6PUEn		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	GPIO2PullUpEnable_S7PUEn		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	GPIO2PullUpEnable_S8PUEn		: 0x01 ;	/* LSB 0x08 */
//	uint32_t	GPIO2PullUpEnable_S9PUEn		: 0x01 ;	/* LSB 0x09 */
//	uint32_t	GPIO2PullUpEnable_S10PUEn		: 0x01 ;	/* LSB 0x0a */
//	uint32_t	GPIO2PullUpEnable_S11PUEn		: 0x01 ;	/* LSB 0x0b */
//	uint32_t	GPIO2PullUpEnable_S12PUEn		: 0x01 ;	/* LSB 0x0c */
//	uint32_t	GPIO2PullUpEnable_S13PUEn		: 0x01 ;	/* LSB 0x0d */
//	uint32_t	GPIO2PullUpEnable_S14PUEn		: 0x01 ;	/* LSB 0x0e */
//	uint32_t	GPIO2PullUpEnable_S15PUEn		: 0x01 ;	/* LSB 0x0f */
//	uint32_t	GPIO2PullUpEnable_S16PUEn		: 0x01 ;	/* LSB 0x10 */
//	uint32_t	GPIO2PullUpEnable_S17PUEn		: 0x01 ;	/* LSB 0x11 */
//	uint32_t	GPIO2PullUpEnable_S18PUEn		: 0x01 ;	/* LSB 0x12 */
//	uint32_t	GPIO2PullUpEnable_S19PUEn		: 0x01 ;	/* LSB 0x13 */
//	uint32_t	GPIO2PullUpEnable_S20PUEn		: 0x01 ;	/* LSB 0x14 */
//	uint32_t	GPIO2PullUpEnable_S21PUEn		: 0x01 ;	/* LSB 0x15 */
//	uint32_t	GPIO2PullUpEnable_S22PUEn		: 0x01 ;	/* LSB 0x16 */
//	uint32_t	GPIO2PullUpEnable_S23PUEn		: 0x01 ;	/* LSB 0x17 */
//	uint32_t	GPIO2PullUpEnable_S24PUEn		: 0x01 ;	/* LSB 0x18 */
//	uint32_t	GPIO2PullUpEnable_S25PUEn		: 0x01 ;	/* LSB 0x19 */
//	uint32_t	GPIO2PullUpEnable_S26PUEn		: 0x01 ;	/* LSB 0x1a */
//	uint32_t	GPIO2PullUpEnable_S27PUEn		: 0x01 ;	/* LSB 0x1b */
//	uint32_t	GPIO2PullUpEnable_S28PUEn		: 0x01 ;	/* LSB 0x1c */
//	uint32_t	GPIO2PullUpEnable_S29PUEn		: 0x01 ;	/* LSB 0x1d */
//	uint32_t	GPIO2PullUpEnable_S30PUEn		: 0x01 ;	/* LSB 0x1e */
//	uint32_t	GPIO2PullUpEnable_S31PUEn		: 0x01 ;	/* LSB 0x1f */
//} Reg_M5_CHIP_CTL_x_GPIO2PullUpEnable_FIELDS ;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_GPIO2PullUpEnable_FIELDS b;
//} Reg_M5_CHIP_CTL_x_GPIO2PullUpEnable_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_GPIO0PullDownEnable_ADDRESS	0x110
//#define	Reg_M5_CHIP_CTL_x_GPIO0PullDownEnable_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	GPIO0PullDownEnable_S0PDEn		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	GPIO0PullDownEnable_S1PDEn		: 0x01 ;	/* LSB 0x01 */
//	uint32_t	GPIO0PullDownEnable_S2PDEn		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	GPIO0PullDownEnable_S3PDEn		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	GPIO0PullDownEnable_S4PDEn		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	GPIO0PullDownEnable_S5PDEn		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	GPIO0PullDownEnable_S6PDEn		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	GPIO0PullDownEnable_S7PDEn		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	reserved_GPIO0PullDownEnable_0		: 0x18 ;	/* LSB 0x08 */
//} Reg_M5_CHIP_CTL_x_GPIO0PullDownEnable_FIELDS ;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_GPIO0PullDownEnable_FIELDS b;
//} Reg_M5_CHIP_CTL_x_GPIO0PullDownEnable_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_GPIO1PullDownEnable_ADDRESS	0x114
//#define	Reg_M5_CHIP_CTL_x_GPIO1PullDownEnable_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	GPIO1PullDownEnable_S0PDEn		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	GPIO1PullDownEnable_S1PDEn		: 0x01 ;	/* LSB 0x01 */
//	uint32_t	GPIO1PullDownEnable_S2PDEn		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	GPIO1PullDownEnable_S3PDEn		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	GPIO1PullDownEnable_S4PDEn		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	GPIO1PullDownEnable_S5PDEn		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	GPIO1PullDownEnable_S6PDEn		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	GPIO1PullDownEnable_S7PDEn		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	GPIO1PullDownEnable_S8PDEn		: 0x01 ;	/* LSB 0x08 */
//	uint32_t	GPIO1PullDownEnable_S9PDEn		: 0x01 ;	/* LSB 0x09 */
//	uint32_t	GPIO1PullDownEnable_S10PDEn		: 0x01 ;	/* LSB 0x0a */
//	uint32_t	GPIO1PullDownEnable_S11PDEn		: 0x01 ;	/* LSB 0x0b */
//	uint32_t	GPIO1PullDownEnable_S12PDEn		: 0x01 ;	/* LSB 0x0c */
//	uint32_t	GPIO1PullDownEnable_S13PDEn		: 0x01 ;	/* LSB 0x0d */
//	uint32_t	GPIO1PullDownEnable_S14PDEn		: 0x01 ;	/* LSB 0x0e */
//	uint32_t	GPIO1PullDownEnable_S15PDEn		: 0x01 ;	/* LSB 0x0f */
//	uint32_t	GPIO1PullDownEnable_S16PDEn		: 0x01 ;	/* LSB 0x10 */
//	uint32_t	GPIO1PullDownEnable_S17PDEn		: 0x01 ;	/* LSB 0x11 */
//	uint32_t	GPIO1PullDownEnable_S18PDEn		: 0x01 ;	/* LSB 0x12 */
//	uint32_t	GPIO1PullDownEnable_S19PDEn		: 0x01 ;	/* LSB 0x13 */
//	uint32_t	GPIO1PullDownEnable_S20PDEn		: 0x01 ;	/* LSB 0x14 */
//	uint32_t	GPIO1PullDownEnable_S21PDEn		: 0x01 ;	/* LSB 0x15 */
//	uint32_t	GPIO1PullDownEnable_S22PDEn		: 0x01 ;	/* LSB 0x16 */
//	uint32_t	GPIO1PullDownEnable_S23PDEn		: 0x01 ;	/* LSB 0x17 */
//	uint32_t	GPIO1PullDownEnable_S24PDEn		: 0x01 ;	/* LSB 0x18 */
//	uint32_t	GPIO1PullDownEnable_S25PDEn		: 0x01 ;	/* LSB 0x19 */
//	uint32_t	GPIO1PullDownEnable_S26PDEn		: 0x01 ;	/* LSB 0x1a */
//	uint32_t	GPIO1PullDownEnable_S27PDEn		: 0x01 ;	/* LSB 0x1b */
//	uint32_t	GPIO1PullDownEnable_S28PDEn		: 0x01 ;	/* LSB 0x1c */
//	uint32_t	GPIO1PullDownEnable_S29PDEn		: 0x01 ;	/* LSB 0x1d */
//	uint32_t	GPIO1PullDownEnable_S30PDEn		: 0x01 ;	/* LSB 0x1e */
//	uint32_t	GPIO1PullDownEnable_S31PDEn		: 0x01 ;	/* LSB 0x1f */
//} Reg_M5_CHIP_CTL_x_GPIO1PullDownEnable_FIELDS;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_GPIO1PullDownEnable_FIELDS b;
//} Reg_M5_CHIP_CTL_x_GPIO1PullDownEnable_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_GPIO2PullDownEnable_ADDRESS	0x118
//#define	Reg_M5_CHIP_CTL_x_GPIO2PullDownEnable_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	GPIO2PullDownEnable_S0PDEn		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	GPIO2PullDownEnable_S1PDEn		: 0x01 ;	/* LSB 0x01 */
//	uint32_t	GPIO2PullDownEnable_S2PDEn		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	GPIO2PullDownEnable_S3PDEn		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	GPIO2PullDownEnable_S4PDEn		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	GPIO2PullDownEnable_S5PDEn		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	GPIO2PullDownEnable_S6PDEn		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	GPIO2PullDownEnable_S7PDEn		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	GPIO2PullDownEnable_S8PDEn		: 0x01 ;	/* LSB 0x08 */
//	uint32_t	GPIO2PullDownEnable_S9PDEn		: 0x01 ;	/* LSB 0x09 */
//	uint32_t	GPIO2PullDownEnable_S10PDEn		: 0x01 ;	/* LSB 0x0a */
//	uint32_t	GPIO2PullDownEnable_S11PDEn		: 0x01 ;	/* LSB 0x0b */
//	uint32_t	GPIO2PullDownEnable_S12PDEn		: 0x01 ;	/* LSB 0x0c */
//	uint32_t	GPIO2PullDownEnable_S13PDEn		: 0x01 ;	/* LSB 0x0d */
//	uint32_t	GPIO2PullDownEnable_S14PDEn		: 0x01 ;	/* LSB 0x0e */
//	uint32_t	GPIO2PullDownEnable_S15PDEn		: 0x01 ;	/* LSB 0x0f */
//	uint32_t	GPIO2PullDownEnable_S16PDEn		: 0x01 ;	/* LSB 0x10 */
//	uint32_t	GPIO2PullDownEnable_S17PDEn		: 0x01 ;	/* LSB 0x11 */
//	uint32_t	GPIO2PullDownEnable_S18PDEn		: 0x01 ;	/* LSB 0x12 */
//	uint32_t	GPIO2PullDownEnable_S19PDEn		: 0x01 ;	/* LSB 0x13 */
//	uint32_t	GPIO2PullDownEnable_S20PDEn		: 0x01 ;	/* LSB 0x14 */
//	uint32_t	GPIO2PullDownEnable_S21PDEn		: 0x01 ;	/* LSB 0x15 */
//	uint32_t	GPIO2PullDownEnable_S22PDEn		: 0x01 ;	/* LSB 0x16 */
//	uint32_t	GPIO2PullDownEnable_S23PDEn		: 0x01 ;	/* LSB 0x17 */
//	uint32_t	GPIO2PullDownEnable_S24PDEn		: 0x01 ;	/* LSB 0x18 */
//	uint32_t	GPIO2PullDownEnable_S25PDEn		: 0x01 ;	/* LSB 0x19 */
//	uint32_t	GPIO2PullDownEnable_S26PDEn		: 0x01 ;	/* LSB 0x1a */
//	uint32_t	GPIO2PullDownEnable_S27PDEn		: 0x01 ;	/* LSB 0x1b */
//	uint32_t	GPIO2PullDownEnable_S28PDEn		: 0x01 ;	/* LSB 0x1c */
//	uint32_t	GPIO2PullDownEnable_S29PDEn		: 0x01 ;	/* LSB 0x1d */
//	uint32_t	GPIO2PullDownEnable_S30PDEn		: 0x01 ;	/* LSB 0x1e */
//	uint32_t	GPIO2PullDownEnable_S31PDEn		: 0x01 ;	/* LSB 0x1f */
//} Reg_M5_CHIP_CTL_x_GPIO2PullDownEnable_FIELDS ;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_GPIO2PullDownEnable_FIELDS b;
//} Reg_M5_CHIP_CTL_x_GPIO2PullDownEnable_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_WdogResetControl_ADDRESS	0xc0
//#define	Reg_M5_CHIP_CTL_x_WdogResetControl_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	WdogResetControl_En		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	reserved_WdogResetControl_0	: 0x1f ;	/* LSB 0x01 */
//} Reg_M5_CHIP_CTL_x_WdogResetControl_FIELDS ;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_WdogResetControl_FIELDS b;
//} Reg_M5_CHIP_CTL_x_WdogResetControl_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_SOCResetVecSet_ADDRESS	0xb0
//#define	Reg_M5_CHIP_CTL_x_SOCResetVecSet_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	SOCResetVecSet_Dev0		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	SOCResetVecSet_Dev1		: 0x01 ;	/* LSB 0x01 */
//	uint32_t	SOCResetVecSet_Dev2		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	SOCResetVecSet_Dev3		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	SOCResetVecSet_Dev4		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	SOCResetVecSet_Dev5		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	SOCResetVecSet_Dev6		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	SOCResetVecSet_Dev7		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	SOCResetVecSet_Dev8		: 0x01 ;	/* LSB 0x08 */
//	uint32_t	SOCResetVecSet_Dev9		: 0x01 ;	/* LSB 0x09 */
//	uint32_t	SOCResetVecSet_Dev10		: 0x01 ;	/* LSB 0x0a */
//	uint32_t	SOCResetVecSet_Dev11		: 0x01 ;	/* LSB 0x0b */
//	uint32_t	SOCResetVecSet_Dev12		: 0x01 ;	/* LSB 0x0c */
//	uint32_t	SOCResetVecSet_Dev13		: 0x01 ;	/* LSB 0x0d */
//	uint32_t	SOCResetVecSet_Dev14		: 0x01 ;	/* LSB 0x0e */
//	uint32_t	SOCResetVecSet_Dev15		: 0x01 ;	/* LSB 0x0f */
//	uint32_t	SOCResetVecSet_Dev16		: 0x01 ;	/* LSB 0x10 */
//	uint32_t	SOCResetVecSet_Dev17		: 0x01 ;	/* LSB 0x11 */
//	uint32_t	SOCResetVecSet_Dev18		: 0x01 ;	/* LSB 0x12 */
//	uint32_t	SOCResetVecSet_Dev19		: 0x01 ;	/* LSB 0x13 */
//	uint32_t	SOCResetVecSet_Dev20		: 0x01 ;	/* LSB 0x14 */
//	uint32_t	SOCResetVecSet_Dev21		: 0x01 ;	/* LSB 0x15 */
//	uint32_t	SOCResetVecSet_Dev22		: 0x01 ;	/* LSB 0x16 */
//	uint32_t	SOCResetVecSet_Dev23		: 0x01 ;	/* LSB 0x17 */
//	uint32_t	SOCResetVecSet_Dev24		: 0x01 ;	/* LSB 0x18 */
//	uint32_t	SOCResetVecSet_Dev25		: 0x01 ;	/* LSB 0x19 */
//	uint32_t	SOCResetVecSet_Dev26		: 0x01 ;	/* LSB 0x1a */
//	uint32_t	SOCResetVecSet_Dev27		: 0x01 ;	/* LSB 0x1b */
//	uint32_t	SOCResetVecSet_Dev28		: 0x01 ;	/* LSB 0x1c */
//	uint32_t	SOCResetVecSet_Dev29		: 0x01 ;	/* LSB 0x1d */
//	uint32_t	SOCResetVecSet_Dev30		: 0x01 ;	/* LSB 0x1e */
//	uint32_t	reserved_SOCResetVecSet_0	: 0x01 ;	/* LSB 0x1f */
//} Reg_M5_CHIP_CTL_x_SOCResetVecSet_FIELDS ;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_SOCResetVecSet_FIELDS b;
//} Reg_M5_CHIP_CTL_x_SOCResetVecSet_t;

/*******************************************************************************
*
*******************************************************************************/
//#define	Reg_M5_CHIP_CTL_x_SOCResetVecClr_ADDRESS	0xb4
//#define	Reg_M5_CHIP_CTL_x_SOCResetVecClr_NUM_BYTES	0x4

//typedef	struct	{
//	uint32_t	SOCResetVecClr_Dev0		: 0x01 ;	/* LSB 0x00 */
//	uint32_t	SOCResetVecClr_Dev1		: 0x01 ;	/* LSB 0x01 */
//	uint32_t	SOCResetVecClr_Dev2		: 0x01 ;	/* LSB 0x02 */
//	uint32_t	SOCResetVecClr_Dev3		: 0x01 ;	/* LSB 0x03 */
//	uint32_t	SOCResetVecClr_Dev4		: 0x01 ;	/* LSB 0x04 */
//	uint32_t	SOCResetVecClr_Dev5		: 0x01 ;	/* LSB 0x05 */
//	uint32_t	SOCResetVecClr_Dev6		: 0x01 ;	/* LSB 0x06 */
//	uint32_t	SOCResetVecClr_Dev7		: 0x01 ;	/* LSB 0x07 */
//	uint32_t	SOCResetVecClr_Dev8		: 0x01 ;	/* LSB 0x08 */
//	uint32_t	SOCResetVecClr_Dev9		: 0x01 ;	/* LSB 0x09 */
//	uint32_t	SOCResetVecClr_Dev10		: 0x01 ;	/* LSB 0x0a */
//	uint32_t	SOCResetVecClr_Dev11		: 0x01 ;	/* LSB 0x0b */
//	uint32_t	SOCResetVecClr_Dev12		: 0x01 ;	/* LSB 0x0c */
//	uint32_t	SOCResetVecClr_Dev13		: 0x01 ;	/* LSB 0x0d */
//	uint32_t	SOCResetVecClr_Dev14		: 0x01 ;	/* LSB 0x0e */
//	uint32_t	SOCResetVecClr_Dev15		: 0x01 ;	/* LSB 0x0f */
//	uint32_t	SOCResetVecClr_Dev16		: 0x01 ;	/* LSB 0x10 */
//	uint32_t	SOCResetVecClr_Dev17		: 0x01 ;	/* LSB 0x11 */
//	uint32_t	SOCResetVecClr_Dev18		: 0x01 ;	/* LSB 0x12 */
//	uint32_t	SOCResetVecClr_Dev19		: 0x01 ;	/* LSB 0x13 */
//	uint32_t	SOCResetVecClr_Dev20		: 0x01 ;	/* LSB 0x14 */
//	uint32_t	SOCResetVecClr_Dev21		: 0x01 ;	/* LSB 0x15 */
//	uint32_t	SOCResetVecClr_Dev22		: 0x01 ;	/* LSB 0x16 */
//	uint32_t	SOCResetVecClr_Dev23		: 0x01 ;	/* LSB 0x17 */
//	uint32_t	SOCResetVecClr_Dev24		: 0x01 ;	/* LSB 0x18 */
//	uint32_t	SOCResetVecClr_Dev25		: 0x01 ;	/* LSB 0x19 */
//	uint32_t	SOCResetVecClr_Dev26		: 0x01 ;	/* LSB 0x1a */
//	uint32_t	SOCResetVecClr_Dev27		: 0x01 ;	/* LSB 0x1b */
//	uint32_t	SOCResetVecClr_Dev28		: 0x01 ;	/* LSB 0x1c */
//	uint32_t	SOCResetVecClr_Dev29		: 0x01 ;	/* LSB 0x1d */
//	uint32_t	SOCResetVecClr_Dev30		: 0x01 ;	/* LSB 0x1e */
//	uint32_t	reserved_SOCResetVecClr_0	: 0x01 ;	/* LSB 0x1f */
//} Reg_M5_CHIP_CTL_x_SOCResetVecClr_FIELDS ;

//typedef	union	{
//	uint32_t r;
//	Reg_M5_CHIP_CTL_x_SOCResetVecClr_FIELDS b;
//} Reg_M5_CHIP_CTL_x_SOCResetVecClr_t;

/*******************************************************************************
*
*******************************************************************************/
//#define Reg_M5_CHIP_CTL_x_HostMuxControl_ADDRESS    0x140
//#define Reg_M5_CHIP_CTL_x_HostMuxControl_NUM_BYTES  0x4

//typedef struct  {
//    uint32_t    HostMuxControl_HostCS0      : 0x04 ;    /* LSB 0x00 */
//    uint32_t    HostMuxControl_HostCS1      : 0x04 ;    /* LSB 0x04 */
//    uint32_t    HostMuxControl_HostCS2      : 0x04 ;    /* LSB 0x08 */
//    uint32_t    HostMuxControl_HostCS3      : 0x04 ;    /* LSB 0x0c */
//    uint32_t    HostMuxControl_HostCS4      : 0x04 ;    /* LSB 0x10 */
//    uint32_t    HostMuxControl_HostCS5      : 0x04 ;    /* LSB 0x14 */
//    uint32_t    HostMuxControl_CycleDelay   : 0x05 ;    /* LSB 0x18 */
//    uint32_t    reserved_HostMuxControl_0   : 0x03 ;    /* LSB 0x1d */
//} Reg_M5_CHIP_CTL_x_HostMuxControl_FIELDS;

//typedef union   {
//    uint32_t r;
//    Reg_M5_CHIP_CTL_x_HostMuxControl_FIELDS b;
//} Reg_M5_CHIP_CTL_x_HostMuxControl_t;

/*******************************************************************************
*
*******************************************************************************/
//#define Reg_M5_CHIP_CTL_x_PLL0Control_ADDRESS   0x10
//#define Reg_M5_CHIP_CTL_x_PLL0Control_NUM_BYTES 0x4

//typedef struct  {
//    uint32_t    PLL0Control_PD          : 0x01 ;    /* LSB 0x00 */
//    uint32_t    PLL0Control_RESET       : 0x01 ;    /* LSB 0x01 */
//    uint32_t    PLL0Control_LOCK        : 0x01 ;    /* LSB 0x02 */
//    uint32_t    PLL0Control_LFTRI       : 0x01 ;    /* LSB 0x03 */
//    uint32_t    PLL0Control_INTPROG     : 0x07 ;    /* LSB 0x04 */
//    uint32_t    PLL0Control_BYPASS      : 0x01 ;    /* LSB 0x0b */
//    uint32_t    PLL0Control_SOUT        : 0x02 ;    /* LSB 0x0c */
//    uint32_t    PLL0Control_SDIV        : 0x02 ;    /* LSB 0x0e */
//    uint32_t    PLL0Control_ABW         : 0x01 ;    /* LSB 0x10 */
//    uint32_t    PLL0Control_BWMAX       : 0x03 ;    /* LSB 0x11 */
//    uint32_t    PLL0Control_BW          : 0x03 ;    /* LSB 0x14 */
//    uint32_t    PLL0Control_VCOSEL      : 0x01 ;    /* LSB 0x17 */
//    uint32_t    PLL0Control_ClkEn       : 0x01 ;    /* LSB 0x18 */
//    uint32_t    PLL0Control_PLLBP       : 0x01 ;    /* LSB 0x19 */
//    uint32_t    PLL0Control_CLKSEL      : 0x01 ;    /* LSB 0x1a */
//    uint32_t    reserved_PLL0Control_0  : 0x05 ;    /* LSB 0x1b */
//} Reg_M5_CHIP_CTL_x_PLL0Control_FIELDS;

//typedef union   {
//    uint32_t r;
//    Reg_M5_CHIP_CTL_x_PLL0Control_FIELDS b;
//} Reg_M5_CHIP_CTL_x_PLL0Control_t;

/*******************************************************************************
*
*******************************************************************************/
//#define Reg_M5_CHIP_CTL_x_DBGUARTClkControl_ADDRESS 0x70
//#define Reg_M5_CHIP_CTL_x_DBGUARTClkControl_NUM_BYTES   0x4
//
//typedef struct  {
//    uint32_t    DBGUARTClkControl_Low       : 0x06 ;    /* LSB 0x00 */
//    uint32_t    DBGUARTClkControl_High      : 0x06 ;    /* LSB 0x06 */
//    uint32_t    DBGUARTClkControl_ClkEn     : 0x01 ;    /* LSB 0x0c */
//    uint32_t    reserved_DBGUARTClkControl_0        : 0x13 ;    /* LSB 0x0d */
//} Reg_M5_CHIP_CTL_x_DBGUARTClkControl_FIELDS;

//typedef union   {
//    uint32_t r;
//    Reg_M5_CHIP_CTL_x_DBGUARTClkControl_FIELDS b;
//} Reg_M5_CHIP_CTL_x_DBGUARTClkControl_t;

/*******************************************************************************
*
*******************************************************************************/
//#define Reg_M5_CHIP_CTL_x_SSI0ClkControl_ADDRESS    0x98
//#define Reg_M5_CHIP_CTL_x_SSI0ClkControl_NUM_BYTES  0x4
//
//typedef struct  {
//    uint32_t    SSI0ClkControl_Low      : 0x09 ;    /* LSB 0x00 */
//    uint32_t    SSI0ClkControl_High     : 0x09 ;    /* LSB 0x09 */
//    uint32_t    SSI0ClkControl_ClkEn    : 0x01 ;    /* LSB 0x12 */
//    uint32_t    reserved_SSI0ClkControl_0       : 0x0d ;    /* LSB 0x13 */
//} Reg_M5_CHIP_CTL_x_SSI0ClkControl_FIELDS ;

//typedef union   {
//    uint32_t  r;
//    Reg_M5_CHIP_CTL_x_SSI0ClkControl_FIELDS b;
//} Reg_M5_CHIP_CTL_x_SSI0ClkControl_t;

//#endif 
/*******************************************************************************
* vi: set shiftwidth=4 tabstop=8 softtabstop=4 expandtab nosmarttab:
*******************************************************************************/
