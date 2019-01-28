core_init:			
			; Select peripherals that must be on
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; PRR (power reduction register) is 0 at startup (all peripherals turned on)
			; TODO: turn off USART0 when debugging is not needed anymore
			;ldi		r16, (1<<PRTW1)|(1<<PRTIM2)|(1<<PRTIM0)|(1<<PRADC)
			;sts		PRR, r16	; switch off TWI(I2C), ADC, Timers 0 and 2
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


			; Set Stack Pointer to top of RAM
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			ldi		r16, high(RAMEND)
			out		sph, r16	
			ldi		r16, low(RAMEND)
			out		spl, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			

; debug **************
.ifdef	DEBUG
			ldi		r16, (DDR_INPUT<<1)
			out		DDRD, r16

			rcall	initUart
.endif
; debug **************

			; Initialize SPI-related pins (TODO: do we need to do this?)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; Set PB3 (MOSI) and PB5 (SCK) as outputs, all others inputs + SS
			ldi		r16, (1<<3)|(1<<5)|(1<<2)
			out		DDRB, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			

			; Initialize SPI unit
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; - SPIE=0: Don't enable interrupts. TODO: use interrupts
			; - SPE =1: Enable SPI.
			; - DORD=0: MSB first.
			; - MSTR=1: Master. TODO: check that SS is not an input
			; - CPOL=0: SCK is low when idle 
			; - CPHA=0: Sample on leading edge, setup on trailing edge
			; - SPR0=0, SPR1=0, combined with SPI2X=0: Set clock rate fck/4
			; ( SPR0=1, SPR1=1, combined with SPI2X=0: Set clock rate fck/128)
			ldi		r16, (0<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(1<<SPR0)
			out		SPCR, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			; Initialize CAN controller
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			rcall	init_mcp251x
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			; Enable interrupts from CAN controller
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			ldi		r16, (1<<CAN_PCICR_BIT)
			sts		pcicr, r16	; enable required pin change interrupts

			ldi		r16, (1<<CAN_PCINT_BIT)	; enable interrupt from CAN controller
			sts		CAN_PCMSK_REG, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sInitComplete<<1)
			ldi		zh, high(sInitComplete<<1)
			rcall	print
.endif
; debug **************
			ldi		r18, 2	; length=2
			ldi		r16, OPCODE_RESET
			mov		r8, r16
			in		r9, MCUSR
			ldi		xl, 8 ; x points to r8
			ldi		xh, 0
			rcall	can_send_packet_new

			; debug **************
			; TODO: remove???
			rcall	delay
			; debug **************

			ldi		r17, MCP251X_REGISTER_CANCTRL
			rcall	mcp251x_read_byte
			ldi		r17, MCP251X_REGISTER_CANSTAT
			rcall	mcp251x_read_byte
			ldi		r17, MCP251X_REGISTER_TXB0CTRL
			rcall	mcp251x_read_byte
			ldi		r17, MCP251X_REGISTER_EFLG
			rcall	mcp251x_read_byte

			sei					; Enable interrupts

			rjmp	user_init


; debug **************
.ifdef	DEBUG

sInitComplete:
.db			"Init complete",13,10,0

.endif
; debug **************
