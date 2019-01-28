; --------------------------------------------------------------------------------------
; print CR+LF
; temp		r16, r0
; --------------------------------------------------------------------------------------
println:
		ldi		r16, 13
		mov		r0, r16
		rcall	printChar
		ldi		r16, 10
		mov		r0, r16
		rcall	printChar
		ret

; --------------------------------------------------------------------------------------
; transmit a character via USART
; param		r0		character
; temp		r16		
; --------------------------------------------------------------------------------------
printChar:
		; wait for empty transmit buffer
		lds		r16, UCSR0A
		sbrs	r16, UDRE0
		rjmp	printChar
		; Put data (r0) into buffer, sends the data
		sts		UDR0, r0
		ret


; --------------------------------------------------------------------------------------
; print a string (from flash)
; param		Z		pointer to string
; temp		r0,r16
; --------------------------------------------------------------------------------------
print:
		lpm		r0, z+
		tst		r0
		breq	print_done
		rcall	printChar
		rjmp	print
print_done:
		ret


; --------------------------------------------------------------------------------------
; print a byte in a hexadecimal format to USART
; param		r1		a byte to print
; temp		r0,r16
; --------------------------------------------------------------------------------------
printByteAsHex:
		mov		r0, r1
		lsr		r0
		lsr		r0
		lsr		r0
		lsr		r0
		rcall	printNibbleAsHex
		mov		r0, r1
		ldi		r16, 0x0F		
		and		r0, r16
		rcall	printNibbleAsHex
		ret

; --------------------------------------------------------------------------------------
; print a nibble (lower 4 bits) as a hexadecimal character to USART
; param		r0		a byte to print
; temp		r16
; --------------------------------------------------------------------------------------
printNibbleAsHex:
		ldi		r16, 10
		cp		r0, r16
		brlo	lower_than_10
		ldi		r16,  'A'-'0' - 10
		add		r0, r16
lower_than_10:
		ldi		r16, '0'
		add		r0, r16
		rcall	printChar
		ret
