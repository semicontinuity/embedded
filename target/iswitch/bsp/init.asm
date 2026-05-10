user_init:
			
			; X Initialize D7 as output (MCP2515_SS)
			; X Initialize PD0, PD1, PD3, PD4, PD6 as outputs (used to connect debug LEDS)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			.equ	DDRD_BUTTON_UP0		= (DDR_INPUT<<PORTBIT_BUTTON_UP0)
			.equ	DDRD_BUTTON_DOWN0	= (DDR_INPUT<<PORTBIT_BUTTON_DOWN0)
			.equ	DDRD_BUTTON_UP1		= (DDR_INPUT<<PORTBIT_BUTTON_UP1)
			.equ	DDRD_BUTTON_DOWN1	= (DDR_INPUT<<PORTBIT_BUTTON_DOWN1)

			.equ	DDRD_OUTPUT_0	= (DDR_OUTPUT<<PORTBIT_OUTPUT_0)
			.equ	DDRD_OUTPUT_1	= (DDR_OUTPUT<<PORTBIT_OUTPUT_1)

			; NB debug COM port also uses these pins (1<<1 enables TX output)
.ifdef	DEBUG
			ldi		r16, DDRD_BUTTON_UP0|DDRD_BUTTON_DOWN0|DDRD_BUTTON_UP1|DDRD_BUTTON_DOWN1 | DDRD_OUTPUT_0|DDRD_OUTPUT_1 | (1<<1)
.else
			ldi		r16, DDRD_BUTTON_UP0|DDRD_BUTTON_DOWN0|DDRD_BUTTON_UP1|DDRD_BUTTON_DOWN1 | DDRD_OUTPUT_0|DDRD_OUTPUT_1
.endif
			out		DDRD, r16

			
			ldi		r16, 0xFF
			mov		value,r16		; lamp initially off
			mov		value1,r16		; lamp initially off

			; all triac control outputs=1 (initially switched off)
			ldi		r16, (LOAD_OFF<<PORTBIT_OUTPUT_0)|(LOAD_OFF<<PORTBIT_OUTPUT_1)
			out		PORTD, r16
			; pull up buttons
			sbi		PORTD, PORTBIT_BUTTON_UP0	; pull up for button UP0
			sbi		PORTD, PORTBIT_BUTTON_DOWN0	; pull up for button DOWN0			
			sbi		PORTD, PORTBIT_BUTTON_UP1	; pull up for button UP1
			;sbi		PORTD, PORTBIT_BUTTON_DOWN1	; pull up for button DOWN1




			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			rcall	init_timer_1


			; Initialize timer 2
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; Generate the following waveform on OC2B:
			; +---------------------+     +---------------------
			; +                     +-----+
			; 0                    OC2B  OC2A
			;
			; DEBUG: System frequency 1.0 MHz, FAST PWM mode, TOP=OC2A, Prescaler=1024.
			; DIM:	 Prescaler=64. At 1.0 MHz, Period is 0-64*256usec = 0-16.3msec
			
			; TCCR2A:
			;	COM2A1,COM2A0=00	Normal port operation, OC2A disconnected
			;	COM2B1,COM2B0=10	Clear OC2B on compare match, set OC0B at OC0A
			;   WGM21,WGM20=11		Entire WGM=111 (7) => Fast PWM, TOP=OCRA
			; TCCR2B:
			;	FOC2A,FOC2B=00		Not applicable
			;   WGM22=1				Entire WGM=111 (7) => Fast PWM, TOP=OCRA
			;	CS22,CS21,CS20=111	111=CLK/1024 from prescaler
			; OCR2A=255(DEBUG)
			; OCR2B=200(DEBUG)
			; TIMSK2:
			;	OCIE2B=0			Interrupt on Compare Match B disabled
			;	OCIE2A=0			Interrupt on Compare Match A disabled
			;	TOIE2=0				Interrupt on Overflow disabled

			;ldi		r16, 255
			;sts		OCR2A, r16
			;ldi		r16, 200
			;sts		OCR2B, r16
			;ldi		r16, (1<<TOIE2)
			;sts		TIMSK2, r16
			;ldi		r16, (0<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(1<<WGM00)
			;sts		TCCR2A, r16
			;ldi		r16, (0<<FOC0A)|(0<<FOC0B)|(1<<WGM02)|(1<<CS02)|(1<<CS01)|(1<<CS00)
			;sts		TCCR2B, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



			; fill 'previous_buttons_state' with 'no buttons pressed' value
			; TODO: should we fill with actual PIND value?
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ser		previous_buttons_state	; previous_buttons_state <- 0xFF
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; initialize channel control registers with default values
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r16, (1<<BITNUM_SWITCH_ENABLED)|(1<<BITNUM_CAN_NOTIFICATION)
			mov		channel_0_control, r16
			mov		channel_1_control, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			; Enable interrupts from buttons
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			lds		r16, pcicr
			ori		r16, (1<<KEYBOARD_PCICR_BIT)
			sts		pcicr, r16	; enable required pin change interrupts

			ldi		r16, KEYBOARD_PORT_MASK
			sts		BUTTONS_PCMSK, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; TODO: Initialize other units

			;rcall	default_channel_data

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sUserInitComplete<<1)
			ldi		zh, high(sUserInitComplete<<1)
			rcall	print
.endif
; debug **************


infinite:	;sleep
			rjmp	infinite


; debug **************
.ifdef	DEBUG

sUserInitComplete:
.db			"User Init complete",13,10,0

.endif
; debug **************
