; --------------------------------------------------------------------------------------			
; param		channel			contains the channel ID (channel is a pair of up+down buttons)
; param		logical_button	contains 0 if 'up' button was toggled, 1 if 'down'
; param		action			contains 0 if button was pressed, 1 if released
;
; layout of channel state/control structure:

; control
; fullBrightnessValue
; zeroBrightnessValue
; highBrightnessValue
; lowBrightnessValue
; brightnessChangeStep
; pressTimeout
; state
; timeout counter
; brightness
;
;
; previous channel state is ignored
; reasoning:
; if the button was pressed, obviously it was not pressed before.
; if the button was released, obviously it was pressed before.
; if two buttons are pressed simultaneously, only the last one is processed.
;
; action codes layout [timeout flag][released flag][down button flag]
;
;
;
; button event handling routine:
; -------------------------------------------------------------------------------------------
; up button was pressed
; 		set channel state to UP_PRESSED_RECENTLY (000)
;		set counter to pressTimeout
;		
; up button was released
;		if channel state is UP_PRESSED_RECENTLY (000)
; 			set channel state to UP_RELEASED_RECENTLY (010)
;		else
;			set channel state to UP_RELEASED (110)
;		set counter to 0
;
; down button was pressed
;		set channel state to DOWN_PRESSED_RECENTLY (001)
;		set counter to pressTimeout
;
; down button was released
;		if channel state is DOWN_PRESSED_RECENTLY (001)
;			set channel state to DOWN_RELEASED_RECENTLY (011)
;		else
;			set channel state to DOWN_RELEASED (111)
;		set counter to 0
; -------------------------------------------------------------------------------------------
;
;
; action handling routine:
; -------------------------------------------------------------------------------------------
; 000	[STATE=UP_PRESSED_RECENTLY]
;		up button was pressed, timeout not exceeded (was released for a short time before)
;		[ACTION=INCREASE_BRIGHTNESS]
;		if brightness has not yet reached fullBrightnessValue
;			increase brightness by brightnessChangeStep
;		decrement timeout counter
;		if it has reached 0
;			set TIMEOUT flag (bit 2), i.e. move to state UP_PRESSED
;
; 001	[STATE=DOWN_PRESSED_RECENTLY]
;		down button was pressed, timeout not exceeded (was released for a short time before)
;		[ACTION=DECREASE_BRIGHTNESS]
;		if brightness has not yet reached zeroBrightnessValue
;			decrease brightness by brightnessChangeStep
;		decrement timeout counter
;		if it has reached 0
;			set TIMEOUT flag (bit 2), i.e. move to state DOWN_PRESSED
;
; 010	[STATE=UP_RELEASED_RECENTLY]
;		up button was released, timeout not exceeded (was pressed for a short time before)
;		[ACTION=MAX_BRIGHTNESS]
;		set brightness to highBrightnessValue
;		move to state UP_RELEASED
;
; 011	[STATE=DOWN_RELEASED_RECENTLY]
;		down button was released, timeout not exceeded (was pressed for a short time before)
;		[ACTION=MIN_BRIGHTNESS]
;		set brightness to lowBrightnessValue
;		move to state DOWN_RELEASED
;
; 100	[STATE=UP_PRESSED]
;		up button was pressed long time ago, timeout exceeded (was released for a long time before)
;		[ACTION=INCREASE_BRIGHTNESS]
;		if brightness has not yet reached fullBrightnessValue
;			increase brightness by brightnessChangeStep
;
; 101	[STATE=DOWN_PRESSED]
;		down button was pressed long time ago, timeout exceeded
;		[ACTION=DECREASE_BRIGHTNESS]
;		if brightness has not yet reached zeroBrightnessValue
;			decrease brightness by brightnessChangeStep
;
; 110	[STATE=UP_RELEASED]
;		up button was released long time ago, timeout exceeded
;		do nothing
;
; 111	[STATE=DOWN_RELEASED]
;		down button was released long time ago, timeout exceeded
;		do nothing
; --------------------------------------------------------------------------------------

TIM2_OVF:	; Timer2 Overflow Handler

			reti	; TEMPORARY - DEBUG


; --------------------------------------------------------------------------------------
; --------------------------------------------------------------------------------------
.def		current_state_register	= r24


handle_dimmer_action:

			; debug **************
			;mov		r1, action
			;rcall	printByteAsHex						
			; debug **************


			; check if the 'action' was 'pressed' (bit=0) or 'released' (bit=1)			
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; we check only bit 0 to distinguish 0x00 from 0x01
			sbrs	action, 0			; skip if button was released
			rjmp	button_was_pressed	; button was released, pass to the next check

button_was_released:
			; debug **************
			ldi		zl, low(sReleasedRecently<<1)
			ldi		zh, high(sReleasedRecently<<1)
			rcall	print
			; debug **************


			ldd		current_state_register, y + OFS_STATE
			ldi		r16, 2				; r16=UP_RELEASED_RECENTLY (010)
			add		r16, logical_button	; r16=UP_RELEASED_RECENTLY (010) or DOWN_RELEASED_RECENTLY (011)

			; check the channel state against UP_PRESSED_RECENTLY (000)/DOWN_PRESSED_RECENTLY (001)
			cp		current_state_register, logical_button
			breq	to_pressed_recently_state	; if channel state is UP_PRESSED_RECENTLY (000)/DOWN_PRESSED_RECENTLY (001)
to_pressed_state:
			subi	r16, -4	; adjust channel state to UP_RELEASED (110)/DOWN_RELEASED (111), i.e. add 4
to_pressed_recently_state:
			; at this point new state is in r16
			std		y + OFS_STATE, r16

			; set counter to 0
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			clr		r16
			std		y + OFS_TIMEOUT_COUNTER, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret

button_was_pressed:
			; debug **************
			ldi		zl, low(sPressedRecently<<1)
			ldi		zh, high(sPressedRecently<<1)
			rcall	print
			; debug **************


			; set channel state to UP_PRESSED_RECENTLY (000) or DOWN_PRESSED_RECENTLY (001)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			std		y + OFS_STATE, logical_button
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; set counter to pressTimeout
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldd		r16, y + OFS_PRESS_TIMEOUT
			std		y + OFS_TIMEOUT_COUNTER, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret




; --------------------------------------------------------------------------------------
default_channel_data:
; --------------------------------------------------------------------------------------
			ldi		yl, low(channel_0_data)
			ldi		yh, high(channel_0_data)

			ldi		r16, 0x80
			std		y+OFS_FULL_BRIGHTNESS_VALUE_L, r16
			ldi		r16, 0x08
			std		y+OFS_FULL_BRIGHTNESS_VALUE_H, r16

			ldi		r16, 0x00
			std		y+OFS_ZERO_BRIGHTNESS_VALUE_L, r16
			ldi		r16, 0x00
			std		y+OFS_ZERO_BRIGHTNESS_VALUE_H, r16

			ldi		r16, 0x00
			std		y+OFS_HIGH_BRIGHTNESS_VALUE_L, r16
			ldi		r16, 0x07
			std		y+OFS_HIGH_BRIGHTNESS_VALUE_H, r16

			ldi		r16, 0x80
			std		y+OFS_LOW_BRIGHTNESS_VALUE_L, r16
			ldi		r16, 0x00
			std		y+OFS_LOW_BRIGHTNESS_VALUE_H, r16

			ldi		r16, 0x80
			std		y+OFS_BRIGHTNESS_INCREASE_STEP_L, r16
			ldi		r16, 0x00
			std		y+OFS_BRIGHTNESS_INCREASE_STEP_H, r16

			ldi		r16, 0x80
			std		y+OFS_BRIGHTNESS_DECREASE_STEP_L, r16
			ldi		r16, 0xFF
			std		y+OFS_BRIGHTNESS_DECREASE_STEP_H, r16


			ldi		r16, 0x03
			std		y+OFS_CONTROL, r16

			ldi		r16, 0x08
			std		y+OFS_PRESS_TIMEOUT, r16

			ldi		r16, 0x00
			std		y+OFS_TIMEOUT_COUNTER, r16

			ldi		r16, 0x07	; DOWN_RELEASED
			std		y+OFS_STATE, r16

			ldi		r16, 0x00
			std		y+OFS_BRIGHTNESS_L, r16
			ldi		r16, 0x00
			std		y+OFS_BRIGHTNESS_H, r16

;.equ		OFS_CURRENT_STEP_L				= 0x12
;.equ		OFS_CURRENT_STEP_H				= 0x13

;.equ		OFS_TARGET_BRIGHTNESS_L			= 0x14
;.equ		OFS_TARGET_BRIGHTNESS_H			= 0x15			

			ret



