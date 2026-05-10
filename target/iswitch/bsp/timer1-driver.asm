; --------------------------------------------------------------------------------------			
; debug **************
.ifdef	DEBUG

sInitializingTimer1:
.db			"Initializing timer 1",13,10,0

sTimer1Initialized:
.db			"Timer 1 initialized",13,10,0

.endif
; debug **************

init_timer_1:
; --------------------------------------------------------------------------------------
			
			; Initialize timer 1 to reset watchdog ~ every 4 seconds (?)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; debug **************
.ifdef	DEBUG
			ldi		zl, low(sInitializingTimer1<<1)
			ldi		zh, high(sInitializingTimer1<<1)
			rcall	print
.endif
; debug **************

			; enable overflow interrupt
;			ldi		r16, (1<<TOIE1)
;			sts		TIMSK1, r16
			ldi		r16, (1<<OCIE1A)
			sts		TIMSK1, r16

			ldi		r16, 0xFF
			sts		OCR1AL, r16
			;ldi		r16, 0x27
			ldi		r16, 0xFF
			sts		OCR1AH, r16


			ldi		r16, (0<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(1<<CS10)
			sts		TCCR1B, r16



			; 1.0 MHz, NORMAL mode, Prescaler=64.
			; Overflow interrupt will occur every 65536*64*1microsec
			; WGM = 0 (NORMAL), CS=011 (divide by 64)
;			ldi		r16, (0<<CS12)|(1<<CS11)|(1<<CS10)
;			sts		TCCR1B, r16

			; no need to init TCCR1A and TCCR1C, they are set to 0 which is OK
			ldi		r16, 0
			sts		TCCR1A, r16
			sts		TCCR1C, r16
			ret


; --------------------------------------------------------------------------------------
;TIM1_OVF:
TIM1_COMPA:	; Timer1 Compare A Handler
; --------------------------------------------------------------------------------------

wdr			; TODO: IS THAT a right place for wdr???

			; Keyboard driver state machine to support key dribbling
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; if the key was toggled long enough ago,
			; so that all dribbling is suppressed at this moment
			; we do only continuous keyboard processing...
			cpi		keyboard_state, STATE_TOGGLED_LONG_AGO
			breq	dribble_suppression_step_done

			dec		keyboard_state	; progress to next stage in dribbling supression
			brne	dribble_suppression_step_done
			
			; state was STATE_TOGGLED_2_TICKS_AGO
			; it's time to ... 
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; ... enable keyboard interrupts...
			ldi		r16, KEYBOARD_PORT_MASK	; KEYBOARD_PORT_MASK is the same
			sts		BUTTONS_PCMSK, r16

			; and ...
			rcall	read_keyboard

			; and shift to STATE_TOGGLED_LONG_AGO (done already...)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

dribble_suppression_step_done:

			reti	; SWITCH: do not do anything else (do not fall thru to process_keyboard)
