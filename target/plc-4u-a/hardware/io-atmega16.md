#### I/O allocation for ATMega16

```
PA0	Valve state HWS					U17	X0
PA1	Valve state HWS					U16	X1
PA2	Valve state CWS					U15	X2
PA3	Valve state CWS					U14	X3
PA4	Leakage sensor SD				U21	SD
PA5	Leakage sensor SC				U20	SC
PA6	Leakage sensor SB				U19	SB
PA7	Leakage sensor SA				U18	SA

PB0     			S1LED	(Red)
PB1     			S1BTN	(Red)
PB2     			S2BTN	(White)
PB3     			S2LED	(White)
PB4     Valve drive 1?					U2	Y0
PB5     Valve drive 2?					U3	Y1
PB6	Valve drive 3?					U4	Y2
PB7	Valve drive 4?					U5	Y3

PC0     SCL / RD485 DIR / SOFT_TX
PC1     SDA / Buzzer / Extra opto-isolated IN / SOFT_RX
PC2     AUX IN 1?					U8	X9
PC3     AUX IN 2?					U9	X8
PC4     Valve control CWS	S3BTN			U10	X7
PC5     Valve control CWS	S4BTN			U11	X6
PC6	Valve control HWS	S6BTN			U12	X5
PC7	Valve control HWS	S5BTN			U13	X4

PD0	RXD
PD1	TXD
PD2				S5LED	(Left Bottom)
PD3     			S3LED	(Left Top)
PD4     			S4LED	(Right Top)
PD5     			S6LED	(Right Bottom)
PD6     AUX OUT 1?					U6	Y4
PD7     AUX OUT 2?					U7	Y5

```
