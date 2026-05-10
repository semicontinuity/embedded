; UART uses pin 31/PD1/TXD, must be enabled!

initUart:
		; set baud rate: UBRR0=9 (115.2K @ 18.432MHz, no x2)
		; set baud rate: UBRR0=119 (9600 @ 18.432MHz, no x2)
		; set baud rate: UBRR0=12 (4800 @ internal 1MHz, no x2)
		; N.B. 1MHz internal is the default frequency of ATMEGA48 with unchanged fuse bits
		ldi		r16, UBRR0L_VALUE
		sts		UBRR0L, r16
		ldi		r16, 0
		sts		UBRR0H, r16

		; set 2x mode
		ldi		r16, (1<<U2X0)
		sts		UCSR0A, r16

		; enable transmitter
		ldi		r16, (1<<TXEN0)
		sts		UCSR0B, r16

		; set frame format:8 data bits, 1 stop bit
		ldi		r16, (0<<USBS0)|(3<<UCSZ00)
		sts		UCSR0C, r16
		ret

