; -----------------------------------------------------------------------------------------
; Handle the "INVOKE" command received
; param		r11:r10	SRAM address
; -----------------------------------------------------------------------------------------
handle_invoke:
			movw	zl, r10	; load the first word of the message to register z			
			icall			; call the subroutine (physical address is sent to us)
			ret


; -----------------------------------------------------------------------------------------
; Send to the host the contents of the specified byte of SRAM
; param		r13:r12	SRAM address
; -----------------------------------------------------------------------------------------
get_byte_from_sram:
			movw	xl, r12		; X = r12 = address pointing to byte in SRAM		
			ldi		r18, 1		; length=1 byte
			rcall	can_send_packet_new
			ret

; -----------------------------------------------------------------------------------------
; Put to the specified location of SRAM the given byte
; param		r13:r12	SRAM address
; param		r14		data
; -----------------------------------------------------------------------------------------
put_byte_to_sram:
			movw	zl, r12
			st		Z, r14
			ret


; -----------------------------------------------------------------------------------------
; Send to the host the contents of the specified byte of FLASH
; param		r13:r12	FLASH address
; -----------------------------------------------------------------------------------------
get_byte_from_flash:

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sReadingByteFromFlash<<1)
			ldi		zh, high(sReadingByteFromFlash<<1)
			rcall	print
			mov		r1, r13
			rcall	printByteAsHex
			mov		r1, r12
			rcall	printByteAsHex
			rcall	println
.endif
; debug **************

			movw	zl, r12
			lpm		r8, Z		; byte from FLASH loaded into r8
; debug **************
.ifdef	DEBUG
			ldi		zl, low(sRead<<1)
			ldi		zh, high(sRead<<1)
			rcall	print
			mov		r1, r8
			rcall	printByteAsHex			
			rcall	println
.endif
; debug **************

			ldi		xl, 8		; X points to r8 containing the byte read from FLASH
			ldi		xh, 0
			ldi		r18, 1		; length=1 byte
			rcall	can_send_packet_new	; (r18:length; X:buffer)
			ret
			ret


; debug **************
.ifdef	DEBUG

sReadingByteFromFlash:
.db			"R FLASH address ", 0
sRead:
.db			"Read ", 0

.endif
; debug **************
