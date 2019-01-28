; --------------------------------------------------------------------------------------			
.ifdef	DEBUG
; debug **************

sSwitchingOn:
.db			"channel 0 => ON!",13,10,0
sSwitchingOff:
.db			"channel 0 => OFF!",13,10,0
sSwitchingOn1:
.db			"channel 1 => ON!",13,10,0
sSwitchingOff1:
.db			"channel 1 => OFF!",13,10,0

; debug **************
.endif


handle_button_action:

; param		channel			contains the channel ID (channel is a pair of up+down buttons)
; param		logical_button	contains 0 if 'up' button was toggled, 1 if 'down'
; param		action			contains 0 if button was pressed, 1 if released

; 2 triac control outputs are connected to the D

; pin 01	PD3/INT1/OC2B/PCINT19	O	Triac control 0
; pin 09	PD5/T1/OC0B/PCINT21		O	Triac control 1

; --------------------------------------------------------------------------------------

			; first, current_buttons_state becomes previous_buttons_state.
			; it will be used next time
			; TODO: move to 'common' section?
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			mov 	previous_buttons_state, current_buttons_state
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; check if the 'action' was 'pressed' (bit=0) or 'released' (bit=1)
			; ignore 'released' events
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; we check only bit 0 to distinguish 0x00 from 0x01
			; skip 'ret' if the value was '0' => if pressed do the job!
			sbrc	action, 0			
			ret


			sbrc	channel, 0
			rjmp	channel_1
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
channel_0:
			; now we know that a button was pressed
			com		value
			
			sbrs	value, 0
			rjmp	switch_on
switch_off:
			sbi		PORTD, PORTBIT_OUTPUT_0
.ifdef	DEBUG
			; debug **************
			ldi		zl, low(sSwitchingOff<<1)
			ldi		zh, high(sSwitchingOff<<1)
			rcall	print
			; debug **************
.endif
			ret					
switch_on:
			cbi		PORTD, PORTBIT_OUTPUT_0

.ifdef	DEBUG
			; debug **************
			ldi		zl, low(sSwitchingOn<<1)
			ldi		zh, high(sSwitchingOn<<1)
			rcall	print
			; debug **************
.endif
			ret
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
channel_1:
			; now we know that a button was pressed
			com		value1
			
			sbrs	value1, 0
			rjmp	switch_on_1
switch_off_1:
			sbi		PORTD, PORTBIT_OUTPUT_1

.ifdef	DEBUG
			; debug **************
			ldi		zl, low(sSwitchingOff1<<1)
			ldi		zh, high(sSwitchingOff1<<1)
			rcall	print
			; debug **************
.endif
			ret					
switch_on_1:
			cbi		PORTD, PORTBIT_OUTPUT_1

.ifdef	DEBUG
			; debug **************
			ldi		zl, low(sSwitchingOn1<<1)
			ldi		zh, high(sSwitchingOn1<<1)
			rcall	print
			; debug **************
.endif
			ret
