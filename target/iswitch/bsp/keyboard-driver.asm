; --------------------------------------------------------------------------------------
; debug **************
sUnrecognizedButton:
.db			"Unrecognized button!",13,10,0
sButtonToggled:
.db			"Button toggled",13,10,0
; debug **************

; invoked from TIM1_OVF when a signal noise (dribble) is suspended
read_keyboard:

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

; --------------------------------------------------------------------------------------			

			in		current_buttons_state, BUTTONS_PORT		; read current buttons state from the port
			
.ifdef	DEBUG		; **********************************************************
			ldi		zl, low(sButtonToggled<<1)
			ldi		zh, high(sButtonToggled<<1)
			rcall	print

			mov		r1, previous_buttons_state
			rcall	printByteAsHex			

			mov		r1, current_buttons_state
			rcall	printByteAsHex						
.endif				; **********************************************************
			
			eor		change_flags, current_buttons_state		; what has changed?


.ifdef	DEBUG		; **********************************************************
			mov		r1, change_flags
			rcall	printByteAsHex			
			rcall	println			
.endif				; **********************************************************

			andi	change_flags, KEYBOARD_PORT_MASK
			brne	real_check
			ret

real_check:


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
			sbrs	change_flags, PORTBIT_BUTTON_UP0			; skip if bit 4 is 1 (if UP0 was toggled => skip)
			rjmp	bh_check_button_down0						; go and check next button state
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; Channel 0 UP button was toggled!
			; populate event variables appropriately
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; up0 was toggled  => channel<-0, logical_button <- 0.
			; channel is already 0, logical_button is already 0 - nothing to do
			;
			; decide whether the button was pressed or released and populate 'action' appropriately			
			; bit =0? (pressed) => action=0 (pressed)
			; bit =1? (released) => action=1 (released)
			sbrc	current_buttons_state, PORTBIT_BUTTON_UP0	; skip next if bit=0 (pressed)
			inc		action										; execute this if bit=1 (released)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; event identified, now go and handle it
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			rjmp	handle_button_action								
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


bh_check_button_down0:
			; check whether the DOWN0 button was toggled
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			sbrs	change_flags, PORTBIT_BUTTON_DOWN0			; skip if bit 6 is 1 (if DOWN0 was toggled => skip)
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
			sbrc	current_buttons_state, PORTBIT_BUTTON_DOWN0
			inc		action										
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
			sbrc	current_buttons_state, PORTBIT_BUTTON_UP1
			inc		action
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
			sbrc	current_buttons_state, PORTBIT_BUTTON_DOWN1
			inc		action
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			; event identified, now go and handle it
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			rjmp	handle_button_action
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


bh_glitch:	; we end up here if we could not identify any known event; should not happen!
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.ifdef	DEBUG
			; debug **************
			;ldi		zl, low(sUnrecognizedButton<<1)
			;ldi		zh, high(sUnrecognizedButton<<1)
			;rcall	print
			; debug **************
.endif
			
			; just in case, fill previous_buttons_state with "nothing was pressed"
			; previous_buttons_state <- 0xFF			
			eor		previous_buttons_state,	previous_buttons_state
			dec		previous_buttons_state
			ret	; nothing more to do
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


; =============================================================================
PINCHINT2:

; Handler for button interrupts (PCINT2)

; 4 buttons are connected to the port D
; Any change on these pins results in the interrupt PINCHINT2 (PCINT16-23 correspond to PINCHINT2)

; pin 02	PD4/T0/XCK/PCINT20		I	Button UP0
; pin 10	PD6/AIN0/OC0A/PCINT22	I	Button DOWN0
; pin 30	PD0/RXD/PCINT16			I	Button UP1
; pin 31	PD1/TXD/PCINT17			I	Button DOWN1

; Keyboard states:
; -----------------------------------------------------------------------------
.equ	STATE_JUST_TOGGLED			= 3
; reaction: disable iterrupts, after 1 tick switch to state STATE_TOGGLED_1_TICK_AGO
.equ	STATE_TOGGLED_1_TICK_AGO	= 2
; 2 = 1 timer tick occurred. tick=>shift to state 1
.equ	STATE_TOGGLED_2_TICKS_AGO	= 1
; 1 = 2 timer tick occurred. enable keyboard interrupts, read kb, shift to state 0
.equ	STATE_TOGGLED_LONG_AGO		= 0
; 0 = > 2 timer tick occurred. do not do anything.
; -----------------------------------------------------------------------------
.def	keyboard_state				= r19

; =============================================================================
			


			; disable interrupts from keyboard
			; (will be re-enabled when dribble interval expires)
			ldi		r16, 0
			sts		BUTTONS_PCMSK, r16
			
.ifdef	DEBUG
			ldi		r16, '#'
			mov		r0, r16
			rcall	printChar
.endif


			; this state will make TIMER1 OVF handler to do some real job
			ldi		keyboard_state, STATE_JUST_TOGGLED
			
			reti
