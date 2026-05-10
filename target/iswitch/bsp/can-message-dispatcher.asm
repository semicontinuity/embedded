dispatch_can_message:
			; Handle the received message (dispatch by opcode)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
check_for_action:
			or		opcode, opcode
			brne	_not_invoke

			; debug **************
.ifdef DEBUG
			ldi		zl, low(sHandlingInvoke<<1)
			ldi		zh, high(sHandlingInvoke<<1)
			rcall	print
.endif
			; debug **************

			rcall	handle_invoke	; opcode was 0x00
			rjmp	dispatch_done

_not_invoke:
			rcall	user_dispatch_can_message
			ret
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
