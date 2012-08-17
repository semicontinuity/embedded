// Connectors on the base board:

//			ext4	01	02	ext5
//			ext6	03	04	ext7
//		RESET	PC6	05	06	PC5	ADC5/SCL
//		rxd	PD0   =	07	08	PC4	ADC4/SDA
//		txd	PD1   =	09	10	PC3	ADC3		SENSOR
//		INT0	PD2   *	11	12 *	PC2	ADC2
//	 INT1 OC2B	PD3   *	13	14 *	PC1     ADC1
//	 xck	T0	PD4   *	15	16 *	PC0	ADC0
//			VCC	17	18	AGND					
//			GND	19	20      AREF    				MCU
//	 xtal1 tosc1	PB6	21	22	PB5	SCK
//	 xtal2 tosc2	PB7	23	24	PB4	MISO
//	 T1	OC0B	PD5   *	25	26	PB3	MOSI/OC2A
//	 AIN0	OC0A	PD6   *	27	28 *	PB2	SS/OC1B         SENSOR1
//	 AIN1		PD7   *	29	30 *	PB1	OC1A            SENSOR1
//	sensor line	ext2	31	32 *	PB0	CLKO/ICP	SENSOR0
//			ext1	33	34	ext1
//			ext0	35	36	ext0


//	ext0	= GND 12v
//	ext1	= VCC 12v


// Connectors on the riser board:


//	36		GND	01	02	GND			35
//	34		VCC_12V	03	04	VCC_12V			33
//	32		SENSOR0	05	06      n.used - sensor line	31
//	30		SENSOR1	07	08	SENSOR0			29
//	28		SENSOR2	09	10	SENSOR1			27
//	26		n.used	11	12	SENSOR2			25
//	24		n.used	13	14	(T10)		xtal2	23
//	22 SCK		(T12)	15	16	(T11)		xtal1	21
//	20 AREF		(T13)	17	18	GND		AGND	19
//	18		GND	19	20	VCC_5V			17
//	16		CTRL2	21	22      CTRL2			15
//	14		CTRL1	23	24	CTRL1			13
//	12		CTRL0	25	26	CTRL0			11
//	10 PC3/ADC3	n.used	27	28      txd			09
//	08 PC4/ADC4/SDA	n.used	29	30      rxd			07
//	06 PC5/ADC5/SCL	n.used	31	32      n.used		RESET	05
//	04		ext1	33	34	ext2			03
//	02		ext3	35	36	ext4			01

// Pins not used on riser boards:

//	06	31 ext2 on base board	(SENSOR LINE)
//	11      26 MOSI/OC2A               In-circuit programming only? - CAN
//	13      24 MISO                    In-circuit programming only? - CAN
//	27      10 PC3/ADC3                (Sensor)
//	29      08 PC4/ADC4/SDA		Future inter-board comm - CAN chip select
//	31      06 PC5/ADC5/SCL            Future inter-board comm - CAN interrupt
//	32	05 RESET on base board	In-circuit programming only?

// Pins not connected to riser boards:
//?

// Interconnections:

//	Riser board A, SENSOR0	PB0
//	Riser board A, SENSOR1	PB1
//	Riser board A, SENSOR2	PB2
//	Riser board B, SENSOR0	PD7
//	Riser board B, SENSOR1	PD6
//	Riser board B, SENSOR2	PD5

// Using NC contacts of motion sensors.
// Sensor is connected between corresponding SENSOR pin and GND:

// SENSORx -------------------+
//                            |
//                             /
//                            /
//                            |
// GND -----------------------+

// Non-active sensor will be read as logical 0, active as logical 1
// Internal pull-up resistor is activated.



// Output is open-collector with external transistor

//                                            (PULLUP RESISTOR)

//                                       -----SENSOR LINE
//                                      /
//                                     | 
// /SENSOR ---------------/\/\/\-------|
//                                      \
//                                       v
//                                       |
//                                      GND
