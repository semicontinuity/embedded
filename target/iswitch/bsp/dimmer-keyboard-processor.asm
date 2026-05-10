
; 2 triac control outputs are connected to the port D

; pin 01	PD3/INT1/OC2B/PCINT19	O	Triac control 0
; pin 09	PD5/T1/OC0B/PCINT21		O	Triac control 1



; --------------------------------------------------------------------------------------
process_keyboard:			

			.def	current_step_l			= r10
			.def	current_step_h			= r11
			.def	current_limit_l			= r12
			.def	current_limit_h			= r13			
			.def	current_brightness_l	= r14
			.def	current_brightness_h	= r15
; --------------------------------------------------------------------------------------

			ldi		yl, low(channel_0_data)
			ldi		yh, high(channel_0_data)
			ldd		current_state_register, y + OFS_STATE

			; debug **************
			mov		r1, current_state_register
			rcall	printByteAsHex						
			; debug **************


			mov		r17, current_state_register
			andi	r17, 0x01	; leave only bit 0 - r17 contains logical_button
			; debug **************
			ldi		zl, low(sR17<<1)
			ldi		zh, high(sR17<<1)
			rcall	print			
			mov		r1, r17
			rcall	printByteAsHex			
			rcall	println
			; debug **************



			cpi		current_state_register, 4 	; 4=100b=UP_PRESSED
			brsh	upper_states				; 4,5,6,7 -> go

lower_states:

			cpi		current_state_register, 2 	; 2=010b=UP_RELEASED_RECENTLY
			brsh	released_recently_states	; 2,3 -> go			

pressed_recently_states:
; #####################################################################################

			; debug **************
			ldi		zl, low(sPressedRecently<<1)
			ldi		zh, high(sPressedRecently<<1)
			rcall	print
			; debug **************

			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldd		r16, y + OFS_TIMEOUT_COUNTER

			; debug **************
			push	r16
			ldi		zl, low(sCounter<<1)
			ldi		zh, high(sCounter<<1)
			rcall	print
			pop		r16
			push	r16
			mov		r1, r16
			rcall	printByteAsHex			
			rcall	println
			pop		r16
			; debug **************

			dec		r16
			brne	notReachedZero

			subi	current_state_register, -4	; add 4, i.e. move to PRESSED state
			std		y + OFS_STATE, current_state_register
			rjmp	change_brightness
notReachedZero:
			std		y + OFS_TIMEOUT_COUNTER, r16
			rjmp	change_brightness

; #####################################################################################

released_recently_states:
; i.e. states UP_RELEASED_RECENTLY and DOWN_RELEASED_RECENTLY
; #####################################################################################
			; debug **************
			ldi		zl, low(sReleasedRecently<<1)
			ldi		zh, high(sReleasedRecently<<1)
			rcall	print
			; debug **************
			
			; debug **************
			ldi		zl, low(sR17<<1)
			ldi		zh, high(sR17<<1)
			rcall	print			
			mov		r1, r17
			rcall	printByteAsHex			
			rcall	println
			; debug **************

			cpi		r17, 1				; down or up?
			brne	set_max_brightness	; if up

set_min_brightness:
			ldd		current_brightness_l, y + OFS_LOW_BRIGHTNESS_VALUE_L
			ldd		current_brightness_h, y + OFS_LOW_BRIGHTNESS_VALUE_H
			rjmp	set_brightness_done
set_max_brightness:
			ldd		current_brightness_l, y + OFS_HIGH_BRIGHTNESS_VALUE_L
			ldd		current_brightness_h, y + OFS_HIGH_BRIGHTNESS_VALUE_H
set_brightness_done:


store_brightness:			
			std		y+OFS_BRIGHTNESS_L, current_brightness_l
			std		y+OFS_BRIGHTNESS_H, current_brightness_h

			; debug **************
			ldi		zl, low(sBrightness<<1)
			ldi		zh, high(sBrightness<<1)
			rcall	print			
			mov		r1, current_brightness_h
			rcall	printByteAsHex
			mov		r1, current_brightness_l
			rcall	printByteAsHex			
			rcall	println
			; debug **************

			subi	current_state_register, -4	; advance to 'released' state (add 4)
			std		y + OFS_STATE, current_state_register
			reti

; #####################################################################################

upper_states:

			cpi		current_state_register, 6 	; 6=110b=UP_RELEASED
			brsh	released_states

; #####################################################################################
pressed_states:
			; the control gets here when a button (either UP or DOWN) is pressed
			; for a sufficiently long time

			; debug **************
			ldi		zl, low(sPressed<<1)
			ldi		zh, high(sPressed<<1)
			rcall	print
			; debug **************

change_brightness:

			; TODO target brightness must be initialized earlier (during read_keyboard?)
			;ldd		current_limit_l, y + OFS_TARGET_BRIGHTNESS_L
			;ldd		current_limit_h, y + OFS_TARGET_BRIGHTNESS_H
			
			; debug **************
			ldi		zl, low(sR17<<1)
			ldi		zh, high(sR17<<1)
			rcall	print			
			mov		r1, r17
			rcall	printByteAsHex			
			rcall	println
			; debug **************

			; TODO compute in advance?
			cpi		r17, 1			; down or up? up=0 down=1
			brne	increasing		; up -> go
decreasing:
			ldd		current_step_l, y + OFS_BRIGHTNESS_DECREASE_STEP_L
			ldd		current_step_h, y + OFS_BRIGHTNESS_DECREASE_STEP_H
			ldd		current_limit_l, y + OFS_ZERO_BRIGHTNESS_VALUE_L
			ldd		current_limit_h, y + OFS_ZERO_BRIGHTNESS_VALUE_H
			rjmp	load_params_done
increasing:
			ldd		current_step_l, y + OFS_BRIGHTNESS_INCREASE_STEP_L
			ldd		current_step_h, y + OFS_BRIGHTNESS_INCREASE_STEP_H
			ldd		current_limit_l, y + OFS_FULL_BRIGHTNESS_VALUE_L
			ldd		current_limit_h, y + OFS_FULL_BRIGHTNESS_VALUE_H
load_params_done:


			; debug **************
			ldi		zl, low(sCurrentLimit<<1)
			ldi		zh, high(sCurrentLimit<<1)
			rcall	print			
			mov		r1, current_limit_h
			rcall	printByteAsHex
			mov		r1, current_limit_l
			rcall	printByteAsHex

			rcall	println
			; debug **************

			; check against limiting value (fullBrightnessValue/zeroBrightnessValue)
			; (check against target brightness value)
			ldd		current_brightness_l, y+OFS_BRIGHTNESS_L
			ldd		current_brightness_h, y+OFS_BRIGHTNESS_H
			; debug **************
			ldi		zl, low(sBrightness<<1)
			ldi		zh, high(sBrightness<<1)
			rcall	print			
			mov		r1, current_brightness_h
			rcall	printByteAsHex
			mov		r1, current_brightness_l
			rcall	printByteAsHex
			rcall	println
			; debug **************

			cp		current_brightness_h, current_limit_h
			brne	do_change_brightness
			cp		current_brightness_l, current_limit_l
			breq	done	; limit reached, do nothing, remain in this state

do_change_brightness:
			add		current_brightness_l, current_step_l
			adc		current_brightness_h, current_step_h
			std		y+OFS_BRIGHTNESS_L, current_brightness_l
			std		y+OFS_BRIGHTNESS_H, current_brightness_h

			; debug **************
			ldi		zl, low(sBrightness<<1)
			ldi		zh, high(sBrightness<<1)
			rcall	print			
			mov		r1, current_brightness_h
			rcall	printByteAsHex
			mov		r1, current_brightness_l
			rcall	printByteAsHex
			rcall	println
			; debug **************
			reti

; #####################################################################################
released_states:	; do nothing
			; debug **************
			ldi		zl, low(sReleased<<1)
			ldi		zh, high(sReleased<<1)
			rcall	print
			; debug **************

done:
			reti




; debug **************
sBrightness:
.db			"Brightness=",0
sCounter:
.db			"Counter=",0
sPressed:
.db			"PRESSED",13,10,0
sReleased:
.db			"RELEASED",13,10,0
sPressedRecently:
.db			"PRESSED REC",13,10,0
sReleasedRecently:
.db			"RELEASED REC",13,10,0

sChangingBrightness:
.db			"Changing brightness..",13,10,0
sCurrentLimit:
.db			"Current limit=",0
sR17:
.db			"R17=",0
; debug **************



