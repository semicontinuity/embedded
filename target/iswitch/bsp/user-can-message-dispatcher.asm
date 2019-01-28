user_dispatch_can_message:
			dec		opcode
			brne	check_for_set
			rcall	handle_action	; opcode was 0x01
			rjmp	dispatch_done
check_for_set:
			dec		opcode
			brne	check_for_get
			rcall	handle_set		; opcode was 0x02
			rjmp	dispatch_done
check_for_get:
			dec		opcode
			brne	dispatch_done
			rcall	handle_get		; opcode was 0x03
			rjmp	dispatch_done

dispatch_done:
			ret
