; -----------------------------------------------------------------------------------------
; Handler for CAN controller interrupts (PCINT1)
; CAN Controller's -INT output is connected to the pin 23 (PC0/ADC0/PCINT8)
; Any change on this pin results in the interrupt PCINT1

; debug **************
.ifdef	DEBUG

sCANInterrupt:
.db			"CAN Interrupt", 13, 10,0

sReadingMessage:
.db			"Reading message", 13, 10, 0

sMessageRead:
.db			"Message read", 13, 10, 0

sHandlingInvoke:
.db			"Handling INVOKE", 13, 10, 0

sCANInterruptHandled:
.db			"CAN Interrupt handled", 13, 10, 0

.endif
; debug **************

			.def	opcode						= r8

PINCHINT1:
; -----------------------------------------------------------------------------------------

			sbic	PINC, 0		; skip iret = start handling interrupt if PC0 was 1->0
			reti				; return immediately if PC0 transitioned 0->1 (INT cleared)
								; in fact, we assume that PC0 was 0->1
								; it could be that any other pin of port C could change.

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sCANInterrupt<<1)
			ldi		zh, high(sCANInterrupt<<1)
			rcall	print

			ldi		zl, low(sReadingMessage<<1)
			ldi		zh, high(sReadingMessage<<1)
			rcall	print
.endif
; debug **************


			; Read the message from CAN controller
			; (from receive buffer 0)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_RXB0D0
			ldi		r18, 8	; all 8 bytes of the payload
			ldi		xl, 8	; X -> r8
			ldi		xh, 0
			rcall	mcp251x_read_bytes

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sMessageRead<<1)
			ldi		zh, high(sMessageRead<<1)
			rcall	print


			mov		r1, r8
			rcall	printByteAsHex
			mov		r1, r9
			rcall	printByteAsHex
			mov		r1, r10
			rcall	printByteAsHex
			mov		r1, r11
			rcall	printByteAsHex
			mov		r1, r12
			rcall	printByteAsHex
			mov		r1, r13
			rcall	printByteAsHex
			mov		r1, r14
			rcall	printByteAsHex
			mov		r1, r15
			rcall	printByteAsHex
			rcall	println
.endif
; debug **************
			

			; Acknowledge interrupt reported by CAN controller after we have read the message
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_CANINTF
			ldi		r18, 0x00	; TODO - currently we clear ALL interrupt flags!
			rcall	mcp251x_write_byte
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


			; +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			rcall	dispatch_can_message
			; +++++++++++++++++++++++++++++++++++++++++++++++++++++++++


			; Clear PCINT8 interrupt flag
			; TODO: investigate:
			; theoretically, another interrupt is triggered
			; on the rising egde on PC0(PCINT8), right after
			; clearing of interrupts in CAN controller.
			; That's why we clear the interrupt that must
			; have been signalled.
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r16, (1<<pcif1)	
			sts		pcifr, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sCANInterruptHandled<<1)
			ldi		zh, high(sCANInterruptHandled<<1)
			rcall	print
.endif
; debug **************

			reti
