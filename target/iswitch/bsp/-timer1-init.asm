			; debug **************
			ldi		zl, low(sInitializingTimer1<<1)
			ldi		zh, high(sInitializingTimer1<<1)
			rcall	print
			; debug **************
			
			; Initialize timer 1 to fire Output Compare A every 10msec.
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			; 10000usec(0x2710) = 625usec(0x0271)*16
			; 1.0 MHz, CTC Mode, WGM=0100, CS=001 (no prescaling) CS=011 (divide by 64)			
			; Output compare modes = Normal (00)
			
			; enable Output Compare A interrupt
			ldi		r16, (1<<OCIE1A)
			sts		TIMSK1, r16

			ldi		r16, 0xFF
			sts		OCR1AL, r16
			;ldi		r16, 0x27
			ldi		r16, 0xFF
			sts		OCR1AH, r16
			
			ldi		r16, 0
			sts		TCCR1A, r16

			;ldi		r16, (0<<WGM13)|(1<<WGM12)|(0<<CS12)|(0<<CS11)|(1<<CS10)
			ldi		r16, (0<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(1<<CS10)
			sts		TCCR1B, r16
			; no need to init TCCR1A and TCCR1C, they are set to 0 which is OK
			; (
			ldi		r16, 0			
			sts		TCCR1C, r16

			
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; debug **************
			ldi		zl, low(sTimer1Initialized<<1)
			ldi		zh, high(sTimer1Initialized<<1)
			rcall	print
			; debug **************

			ret
