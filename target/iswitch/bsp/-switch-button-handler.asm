; -----------------------------------------------------------------------------------------
; Handler for button interrupts (PCINT2)

; 4 buttons are connected to the port D
; Any change on these pins results in the interrupt PCINT2

; pin 02	PD4/T0/XCK/PCINT20		I	Button UP1
; pin 10	PD6/AIN0/OC0A/PCINT22	I	Button DOWN1
; pin 30	PD0/RXD/PCINT16			I	Button UP0
; pin 31	PD1/TXD/PCINT17			I	Button DOWN0

; 2 triac control outputs are connected to the D

; pin 01	PD3/INT1/OC2B/PCINT19	O	Triac control 0
; pin 09	PD5/T1/OC0B/PCINT21		O	Triac control 1

; -----------------------------------------------------------------------------------------


			.def	current_buttons_state		= r23
			.def	previous_buttons_state		= r22
			.def	change_flags				= r22
			
			.equ	EVENT_DESC_ADDRESS_LOW		= 9
			.equ	EVENT_DESC_ADDRESS_HIGH		= 0
			.equ	EVENT_DESC_LENGTH			= 3		; 3 registers r9-r11, 3 bytes
			.def	channel						= r9
			.def	logical_button				= r10
			.def	action						= r11

			.def	current_control_register	= r2
			.def	temp						= r17


PINCHINT2:	; PCINT2 interrupt handler
			
			in		current_buttons_state, PIND				; read current buttons state from the port
			
						
			; debug **************
			ldi		zl, low(sButtonToggled<<1)
			ldi		zh, high(sButtonToggled<<1)
			rcall	print
			; debug **************

			; debug **************
			mov		r1, previous_buttons_state
			rcall	printByteAsHex			
			rcall	println
			; debug **************
			

			; debug **************
			mov		r1, current_buttons_state
			rcall	printByteAsHex			
			rcall	println
			; debug **************
			eor		change_flags, current_buttons_state		; what has changed?
			; debug **************
			mov		r1, change_flags
			rcall	printByteAsHex			
			rcall	println
			; debug **************
			
			; the event detection code will identify the event with these 3 variables:

			; 'channel' contains the number of 'logical device' (pair of up+down buttons)
			; 'logical_button' contains 0 if 'up' button was toggled, 1 if 'down'
			; 'action' contains 0 if button was pressed, 1 if released

			; initial values are:
			clr		channel				; start with 'logical device' #0
			clr		logical_button				; start with 'up' button toggled
			clr		action						; start with 'pressed'


bh_check_button_up0:
			; check whether the UP0 button was toggled
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			sbrs	change_flags, PORTBIT_BUTTON_UP0			; skip if bit 0 is 1 (if UP0 was toggled => skip)
			rjmp	bh_check_button_down0						; go and check next button state
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; Channel 0 UP button was toggled!
			; populate event variables appropriately
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; up0 was toggled  => channel<-0, logical_button <- 0.
			; channel is already 0, logical_button is already 0 - nothing to do
			;
			; decide whether the button was pressed or released and populate 'action' appropriately			
			sbrs	current_buttons_state, PORTBIT_BUTTON_UP0	; bit 0=0? (pressed) => action=0 (pressed)
			inc		action										; bit 0=1? (released) => action=1 (released)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; event identified, now go and handle it
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			rjmp	handle_button_action								
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


bh_check_button_down0:
			; check whether the DOWN0 button was toggled
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			sbrs	change_flags, PORTBIT_BUTTON_DOWN0			; skip if bit 1 is 1 (if DOWN0 was toggled => skip)
			rjmp	bh_check_button_up1
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; Channel 0 DOWN button was toggled!
			; populate event variables appropriately
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; down0 was toggled => channel<-0, logical_button<-1.
			; channel is already 0, logical_button is 0 => logical_button++
			inc		logical_button				; logical_button <- 1			
			;
			; decide whether the button was pressed or released and populate 'action' appropriately						sbrs	current_buttons_state, PORTBIT_BUTTON_UP0	; bit is 0? (pressed) => action=0 (pressed)
			sbrs	current_buttons_state, PORTBIT_BUTTON_DOWN0
			inc		action										; bit is 1? (released) => action=1 (released)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; event identified, now go and handle it
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			rjmp	handle_button_action
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


bh_check_button_up1:
			inc		channel								; channel <- 1

			; check whether the UP1 button was toggled
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			sbrs	change_flags, PORTBIT_BUTTON_UP1			; skip if bit 4 is 1 (if UP1 was toggled => skip)
			rjmp	bh_check_button_down1
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; Channel 1 UP button was toggled!
			; populate event variables appropriately
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; up1 was toggled => channel <- 1, logical_button<-0.
			; channel is already 1, logical_button is already 0
			;
			; decide whether the button was pressed or released and populate 'action' appropriately
			sbrs	current_buttons_state, PORTBIT_BUTTON_UP1	; bit is 0? (pressed) => action=0 (pressed)
			inc		action										; bit is 1? (released) => action=1 (released)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			; event identified, now go and handle it
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			rjmp	handle_button_action
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


bh_check_button_down1:
			; check whether the DOWN1 button was toggled
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			sbrs	change_flags, PORTBIT_BUTTON_DOWN1		; skip if bit 6 is 1 (if DOWN1 was toggled => skip)
			rjmp	bh_glitch

			; Channel 1 DOWN button was toggled!
			; populate event variables appropriately
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; down1 was toggled => channel <- 1, logical_button<-1.
			; channel is already 1, logical_button is 0 => logical_button++
			inc		logical_button
			;
			; decide whether the button was pressed or released and populate 'action' appropriately			
			sbrs	current_buttons_state, PORTBIT_BUTTON_DOWN1	; bit is 0? (pressed) => action=0 (pressed)
			inc		action										; bit is 1? (released) => action=1 (released)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			; event identified, now go and handle it
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			rjmp	handle_button_action
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


bh_glitch:	; we end up here if we could not identify any known event; should not happen!
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; debug **************
			ldi		zl, low(sUnrecognizedButton<<1)
			ldi		zh, high(sUnrecognizedButton<<1)
			rcall	print
			; debug **************
			
			; just in case, fill previous_buttons_state with "nothing was pressed"
			; previous_buttons_state <- 0xFF

			
			eor		previous_buttons_state,	previous_buttons_state
			dec		previous_buttons_state
			reti	; nothing more to do
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

; --------------------------------------------------------------------------------------			
; param		channel			contains the channel ID (channel is a pair of up+down buttons)
; param		logical_button	contains 0 if 'up' button was toggled, 1 if 'down'
; param		action			contains 0 if button was pressed, 1 if released
; --------------------------------------------------------------------------------------
handle_button_action:
			; handling the detected event
			
			; debug **************
			ldi		zl, low(sHandlingButtonAction<<1)
			ldi		zh, high(sHandlingButtonAction<<1)
			rcall	print
			; debug **************


			; first, current_buttons_state becomes previous_buttons_state.
			; it will be used next time
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			mov 	previous_buttons_state, current_buttons_state
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; fetch the control register corresponding to the active channel:
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; make X point to DEV_REG_CONTROL_0 if channel is 0
			; make X point to DEV_REG_CONTROL_1 if channel is 1
			ldi		xl, DEV_REG_CONTROL_ADDRESS_LOW
			ldi		xh, DEV_REG_CONTROL_ADDRESS_HIGH
			sbrc	channel, 0	; we check only bit 0 to distinguish 0x00 from 0x01
			inc		xl					; now X points to DEV_REG_CONTROL_1
			ld		current_control_register, X
			; now the register 'current_control_register' is loaded
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


			; check if the 'action' was 'pressed' (bit=0) or 'released' (bit=1)
			; ignore 'released' events
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			sbrs	action, 0			; we check only bit 0 to distinguish 0x00 from 0x01
			rjmp	check_can_bit		; button was released, pass to the next check
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; Should we handle the action?
			; Check the BITNUM_SWITCH_ENABLED flag in the appropriate logical device control register
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; bit is 1 => toggle the output, 0 => do nothing
			sbrc	current_control_register, BITNUM_SWITCH_ENABLED				
			rcall	handle_action			
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


check_can_bit:
			; check the BITNUM_CAN_NOTIFICATION flag in the appropriate logical divice control register
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; bit is 1 => send the CAN packet, 0 => don't send
			sbrs	current_control_register, BITNUM_CAN_NOTIFICATION
			reti	; nothing more to do, just return
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; send the 3-byte packet containing {channel, logical_button, action}
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; make X point to channel (start of data buffer, channel)
			; (NB: X already points to DEV_REG_CONTROL_x. r29 is most likely 0)
			ldi		xl, EVENT_DESC_ADDRESS_LOW
			ldi		xh, EVENT_DESC_ADDRESS_HIGH
			ldi		r18, EVENT_DESC_LENGTH			; length=3 bytes
			rcall	can_send_packet_new			
			reti
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			


; debug **************
sUnrecognizedButton:
.db			"Unrecognized button!",13,10,0
sButtonToggled:
.db			"Button toggled",13,10,0
sHandlingButtonAction:
.db			"Handling BTN action",13,10,0
; debug **************