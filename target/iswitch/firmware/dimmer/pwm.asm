; -----------------------------------------------------------------------------------------
  ext_int0_init:
; -----------------------------------------------------------------------------------------
; Initialize INT0 input to generate an interrupt
; -----------------------------------------------------------------------------------------
			; on the falling edge
			ldi		r16, (0<<ISC11)|(0<<ISC10)|(1<<ISC01)|(0<<ISC00)
			sts		EICRA, r16
			
			; enable interrupt
			ldi		r16, (0<<INT1)|(1<<INT0)
			out		EIMSK, r16

			ret

; -----------------------------------------------------------------------------------------
  pwm_timer1_init_and_start:
; -----------------------------------------------------------------------------------------
; Initialize timer 1 to trigger Overflow interrupts every ~10mscec=39*256+16usec
; -----------------------------------------------------------------------------------------
			
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; OCR1AH = 39
			; OCR1AL = 16
			; OCR1BH = N/A
			; OCR1BL = N/A
			; TCNT1H = N/A
			; TCNT1L = N/A
			; ICR1H  = N/A
			; ICR1L  = N/A
			; TIMSK1
			; {
			;   ICIE1	= 0 (Input Capture Interrupt disabled)
			;   OCIE1B	= 0 (interrupt on Compare Match B disabled)
			;   OCIE1A	= 1 (interrupt on Compare Match A enabled)
			;   TOIE1	= 0 (interrupt on Overflow disabled)
			; }
			; TIFR1 = N/A
			; TCCR1A = 0
			; {
			;   COM1A = 00 (Normal port operation, OC1A disconnected)
			;   COM1B = 00 (Normal port operation, OC1B disconnected)
			;   WGM = 0100 (CTC, TOP=OCR1A)
			; }
			; TCCR1B = 00001001 = 0x09
			; {
			;   ICNC1 = 0 (no Input Capture Noise Canceller - N/A)
			;   ICES1 = 0 (Input Capture Edge Select - N/A)
			;   WGM = 0100 (CTC, TOP=OCR1A)
			;   CS = 001 = clkIO/1
			; }
			; TCCR1C = 00 (No Force Output Compare for Channel A and B)

			ldi		r16, 39
			sts		OCR1AH, r16
			ldi		r16, 16
			sts		OCR1AL, r16

			ldi		r16, 0
			sts		OCR1BL, r16
			sts		OCR1BH, r16
			
			ldi		r16, (0<<OCIE1B)|(1<<OCIE1A)|(0<<TOIE1)
			sts		TIMSK1, r16

			ldi		r16, (0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10)
			sts		TCCR1A, r16
			
			ldi		r16, (0<<ICNC1)|(0<<ICES1)|(0<<WGM13)|(1<<WGM12)|(0<<CS12)|(0<<CS11)|(1<<CS10)
			sts		TCCR1B, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			ret

; -----------------------------------------------------------------------------------------
  pwm_timer0_init:
; -----------------------------------------------------------------------------------------
; Initialize timer 0 to produce PWM signal
;
; Most of timer 0 registers are initialized except TCCR0B - timer is not started
; -----------------------------------------------------------------------------------------
			
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; Expected waveform at OCxB is:
			;
			; 0             x-1=OCxB  TOP=x=OCxA
			; ----------------------++-------------------
			;                       ||
			;                       ++
			;
			; OCRxA = TOP = x = (0-156)
			; OCRxB = x - 1
			; TCNTx do not initialize
			; TIMSKx
			; {
			;   OCIExB=0 (interrupt on Compare Match B disabled)
			;   OCIExA=0 (interrupt on Compare Match A disabled)
			;   TOIEx=1 (interrupt on Overflow enabled) ??
			; }
			; TIFR0 do not initialize
			; TCCRxA
			; {
			;   COMxA = 00 (Normal port operation, OCxA disconnected)
			;   COMxB = 10 (Clear OCxB on Compare Match, set OCxB at TOP)
			;   WGM = 111 (Fast PWM, TOP=OCRxA) ???
			; }
			; TCCRxB
			; {
			;   FOCxA = 0 (do not force output compare)
			;   FOCxB = 0 (do not force output compare)
			;   WGM = 111 (Fast PWM, TOP=OCRxA) ???
			;   CS = clkIO/64 = 011 for timer 0
			; }

			ldi		r16, 100
			out		OCR0A, r16

			ldi		r16, 99
			out		OCR0B, r16
			
			ldi		r16, (0<<OCIE0B)|(1<<OCIE0A)|(0<<TOIE0)
			sts		TIMSK0, r16

			ldi		r16, (0<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(1<<WGM00)
			out		TCCR0A, r16
			
			;ldi		r16, (0<<FOC0A)|(0<<FOC0B)|(1<<WGM02)|(0<<CS02)|(1<<CS01)|(1<<CS00)
			;out		TCCR0B, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			ret



; -----------------------------------------------------------------------------------------
  EXT_INT0:
; -----------------------------------------------------------------------------------------
; Mains sync 50 Hz
; Triggered just after angle 0 - EXT_INT0 triggers interrupt on falling edge
; -----------------------------------------------------------------------------------------
			
			; syncronize timer 1 to 0
			ldi		r16, 0
			sts		TCNT1H, r16	; beware of the order - write high byte first
			sts		TCNT1L, r16
			reti


; -----------------------------------------------------------------------------------------
  TIM1_COMPA:
; -----------------------------------------------------------------------------------------
; Timer 1 Compare A Handler;
; Mains sync 100 Hz - Invoked in 10ms after timer 1 is started by the Sync interrupt.
; -----------------------------------------------------------------------------------------

			; start timer 0
			ldi		r16, (0<<FOC0A)|(0<<FOC0B)|(1<<WGM02)|(0<<CS02)|(1<<CS01)|(1<<CS00)
			out		TCCR0B, r16
			reti



; -----------------------------------------------------------------------------------------
  TIM0_COMPA:
; -----------------------------------------------------------------------------------------
; End of firing pulse, timer 0
; -----------------------------------------------------------------------------------------
			; stop timer 0
			ldi		r16, (0<<FOC0A)|(0<<FOC0B)|(1<<WGM02)|(0<<CS02)|(0<<CS01)|(0<<CS00)
			out		TCCR0B, r16
			reti