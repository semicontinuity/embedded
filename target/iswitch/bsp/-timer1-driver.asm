; !!!!!!!!!!!!!!!!!!!!!
			; Initialize timer 1 to reset watchdog ~ every 4.19 seconds
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; enable overflow interrupt
			ldi		r16, (1<<TOIE1)
			sts		TIMSK1, r16

			; 1.0 MHz, NORMAL mode, Prescaler=64.
			; Overflow interrupt will occur every 65536*64*1microsec
			; WGM = 0 (NORMAL), CS=011 (divide by 64)
			ldi		r16, (0<<CS12)|(1<<CS11)|(1<<CS10)
			sts		TCCR1B, r16
			; no need to init TCCR1A and TCCR1C, they are set to 0 which is OK
			ldi		r16, 0
			sts		TCCR1A, r16
			sts		TCCR1C, r16

			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; debug **************
			ldi		zl, low(sTimer1Initialized<<1)
			ldi		zh, high(sTimer1Initialized<<1)
			rcall	print
			; debug **************




TIM1_OVF:	; Timer1 Overflow Handler

			wdr		;reset watchdog

			; debug **************
			ldi		zl, low(sTimer1Overflowed<<1)
			ldi		zh, high(sTimer1Overflowed<<1)
			rcall	print
			; debug **************

			reti


sTimer1Overflowed:
.db			"Timer 1 overflowed",13,10,0