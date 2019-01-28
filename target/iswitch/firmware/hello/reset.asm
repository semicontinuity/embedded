RESET:		; Main program start


			; Set Stack Pointer to top of RAM
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			ldi		r16, high(RAMEND)
			out		sph, r16	
			ldi		r16, low(RAMEND)
			out		spl, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
		
			ldi		r16, (1<<1)
			out		DDRD, r16

			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			rcall	initUart

infinite:	

			; debug **************
			ldi		zl, low(sHelloWorld<<1)
			ldi		zh, high(sHelloWorld<<1)
			rcall	print
			; debug **************

			
			rjmp	infinite


sHelloWorld:
.db			"Hello, world!",13,0
