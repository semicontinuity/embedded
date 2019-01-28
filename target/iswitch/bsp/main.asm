.EQU	DEBUG = 1

.INCLUDE	"m48def.inc"
.INCLUDE	"device.inc"

; TODO: init PRR (power reduction register)
; TODO: enable pull-ups on unused (floating) pins to minimize power consumption
; TODO: init and use watchdog
; TODO: power saving, sleep

; =========================================================================================
;
; HARDWARE:
;
; ATMEGA48
; 01		PD3/INT1/OC2B/PCINT19	O	Triac control 0
; 09		PD5/T1/OC0B/PCINT21		O	Triac control 1
; 11		PD7/AIN1/PCINT23		O	CAN Controller select (-CS)
; 23		PC0/ADC0/PCINT8			I	CAN Controller interrupt (-INT)
; 32		PD2/INT0/PCINT18		I	Zero cross interrupt
; =========================================================================================

.CSEG


; =========================================================================================
; Flash page 0 (ATMega48) - self-reprogrammable
; -----------------------------------------------------------------------------------------
.ORG		0	
.INCLUDE	"interrupt-table.asm"

; placed before RESET: so that any unexpected interrupt will cause reset
.INCLUDE	"empty-int-handlers.asm"
; -----------------------------------------------------------------------------------------
RESET:		; Main program start
; -----------------------------------------------------------------------------------------			
.INCLUDE	"wdt-init.asm"	; must be short enough to fit in the rest of the page!
; =========================================================================================



.ORG		32
; =========================================================================================
; CORE
; Flash pages 1+ (ATMega48) - not self-reprogrammable
; -----------------------------------------------------------------------------------------
.INCLUDE	"../../../shared/src/avrasm/core.asm"
; =========================================================================================




.ORG		1024
; =========================================================================================
; USER SECTION: Flash pages ?+ (ATMega48) - self-reprogrammable
; -----------------------------------------------------------------------------------------
.INCLUDE	"operations.inc"
.INCLUDE	"init.asm"
.INCLUDE	"timer1-driver.asm"
.INCLUDE	"keyboard-driver.asm"
.INCLUDE	"switch-handler.asm"
.INCLUDE	"user-can-message-dispatcher.asm"
.INCLUDE	"operations.asm"
; =========================================================================================





; =========================================================================================



.DSEG

.INCLUDE	"dimmer-control.inc"

.ORG		0x100	; TODO explain why 0x100
channel_0_data:		.byte 0x16
channel_1_data:		.byte 0x16

; =========================================================================================
.ESEG
