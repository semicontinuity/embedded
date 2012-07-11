;	--------------------------------------------------------------------------
	RESET:
;	--------------------------------------------------------------------------
;	Main program start
;	--------------------------------------------------------------------------
	.def	tmp		= r16
;	--------------------------------------------------------------------------

			; Set Stack Pointer to top of RAM
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			ldi		tmp, high(RAMEND)
			out		sph, tmp
			ldi		tmp, low(RAMEND)
			out		spl, tmp
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			

			ldi		tmp, 1<<5	; PD5=output
			out		DDRD,tmp	; PORTD-all pins are outputs

			rcall	ext_int0_init
			rcall	pwm_timer0_init
			rcall	pwm_timer1_init_and_start
			
			sei					; Enable interrupts

infinite:	;sleep
			rjmp	infinite
