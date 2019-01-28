; =========================================================================================
;
; HARDWARE:
;
; ATMEGA48
; pin 01	PD3/INT1/OC2B/PCINT19	O	Triac control 0
; pin 02	PD4/T0/XCK/PCINT20		I	Button UP0
; pin 09	PD5/T1/OC0B/PCINT21		O	Triac control 1
; pin 10	PD6/AIN0/OC0A/PCINT22	I	Button DOWN0
; pin 11	PD7/AIN1/PCINT23		O	CAN Controller select (-CS)
; pin 23	PC0/ADC0/PCINT8			I	CAN Controller interrupt (-INT)
; pin 30	PD0/RXD/PCINT16			I	Button UP1
; pin 31	PD1/TXD/PCINT17			I	Button DOWN1
; pin 32	PD2/INT0/PCINT18		I	Zero cross interrupt

; =========================================================================================

.equ	DDR_INPUT			= 0
.equ	DDR_OUTPUT			= 1


; output / load
.equ	PORTBIT_OUTPUT_0				= 3		; PD3	pin 01
.equ	PORTBIT_OUTPUT_1				= 5		; PD5	pin 09
.equ	LOAD_ON							= 0
.equ	LOAD_OFF						= 1

; buttons
.equ	KEYBOARD_PCICR_BIT				= pcie2

.equ	BUTTONS_PORT					= PIND
.equ	BUTTONS_PCMSK					= pcmsk2

.equ	PORTBIT_BUTTON_UP0				= 4		; PD4	pin 02	PCINT20
.equ	BUTTON_UP0_PORTBITNUM				= 4		; PD4	pin 02	PCINT20
.equ	BUTTON_UP0_PCINT				= pcint20

.equ	PORTBIT_BUTTON_DOWN0			= 6		; PD6	pin 10	PCINT22
.equ	BUTTON_DOWN0_PORTBITNUM			= 6
.equ	BUTTON_DOWN0_PCINT				= pcint22

.equ	PORTBIT_BUTTON_UP1				= 0		; PD0	pin 30	PCINT16
.equ	BUTTON_UP1_PORTBITNUM			= 0
.equ	BUTTON_UP1_PCINT				= pcint16

.equ	PORTBIT_BUTTON_DOWN1			= 1		; PD1	pin 31	PCINT17 (txd=debug!)
.equ	BUTTON_DOWN1_PORTBITNUM			= 1
.equ	BUTTON_DOWN1_PCINT				= pcint17

; when DEBUGging, PD1 is used as tx to transmit debug data
.ifdef	DEBUG
.equ	KEYBOARD_PORT_MASK				= (1<<BUTTON_UP0_PORTBITNUM)|(1<<BUTTON_DOWN0_PORTBITNUM)|(1<<BUTTON_UP1_PORTBITNUM)
.else
.equ	KEYBOARD_PORT_MASK				= (1<<BUTTON_UP0_PORTBITNUM)|(1<<BUTTON_DOWN0_PORTBITNUM)|(1<<BUTTON_UP1_PORTBITNUM)|(1<<BUTTON_DOWN1_PORTBITNUM)
.endif


; control registers for logical devices
.equ	DEV_REG_CONTROL_ADDRESS_LOW		= 24
.equ	DEV_REG_CONTROL_ADDRESS_HIGH	= 0
.def	channel_0_control				= r24
.def	channel_1_control				= r25

.equ	BITNUM_SWITCH_ENABLED			= 0
.equ	BITNUM_CAN_NOTIFICATION			= 1


; for a simple device!
.def	value							= r14
.def	value1							= r15

; port D  1111 1011 = FB (PD2=0)



; CAN
.equ	CAN_PCINT_BIT					= pcint8
.equ	CAN_PCMSK_REG					= pcmsk1
.equ	CAN_PCICR_BIT					= pcie1
