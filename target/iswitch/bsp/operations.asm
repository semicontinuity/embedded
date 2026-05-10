; -----------------------------------------------------------------------------------------
; toggle the output depending on the action
; assume that the action is 'button pressed'
;
; param		channel
; param		logical_button
;
; debug **************
.ifdef	DEBUG

sHandlingAction:
.db			"Handling action", 13, 10, 0

.endif
; debug **************
;
; -----------------------------------------------------------------------------------------
handle_action:

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sHandlingAction<<1)
			ldi		zh, high(sHandlingAction<<1)
			rcall	print
.endif
; debug **************

; debug **************
.ifdef	DEBUG
			mov		r1, channel
			rcall	printByteAsHex			
			rcall	println
			mov		r1, logical_button
			rcall	printByteAsHex			
			rcall	println
.endif
; debug **************


			sbrc	channel, 0	; we check only bit 0 to distinguish 0x00 from 0x01
			rjmp	handle_logical_device_1

			sbrc	logical_button, 0	; we check only bit 0 to distinguish 0x00 from 0x01
			rjmp	handle_ld0_down

handle_ld0_up:
			sbi		PORTD, PORTBIT_OUTPUT_0
			rjmp	handle_switch_action_done
handle_ld0_down:
			cbi		PORTD, PORTBIT_OUTPUT_0
			rjmp	handle_switch_action_done


handle_logical_device_1:
			sbrc	logical_button, 0	; we check only bit 0 to distinguish 0x00 from 0x01
			rjmp	handle_ld1_down
handle_ld1_up:
			sbi		PORTD, PORTBIT_OUTPUT_1
			rjmp	handle_switch_action_done
handle_ld1_down:
			cbi		PORTD, PORTBIT_OUTPUT_1
handle_switch_action_done:
			ret


; -----------------------------------------------------------------------------------------
; handle the 'set' command
; param		channel
; param		value (r10)
; -----------------------------------------------------------------------------------------
handle_set:

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sHandlingSet<<1)
			ldi		zh, high(sHandlingSet<<1)
			rcall	print
.endif
; debug **************

			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; make X point to DEV_REG_CONTROL_0 if logical_device is 0
			; make X point to DEV_REG_CONTROL_1 if logical_device is 1
			ldi		xl, DEV_REG_CONTROL_ADDRESS_LOW
			ldi		xh, DEV_REG_CONTROL_ADDRESS_HIGH
			sbrc	channel, 0	; we check only bit 0 to distinguish 0x00 from 0x01
			inc		xl					; now X points to DEV_REG_CONTROL_1
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			st		X, r10

			ret

; -----------------------------------------------------------------------------------------
; handle the 'get' command
; param		channel
; -----------------------------------------------------------------------------------------
handle_get:

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sHandlingGet<<1)
			ldi		zh, high(sHandlingGet<<1)
			rcall	print
.endif
; debug **************
			
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; make X point to DEV_REG_CONTROL_0 if logical_device is 0
			; make X point to DEV_REG_CONTROL_1 if logical_device is 1
			ldi		xl, DEV_REG_CONTROL_ADDRESS_LOW
			ldi		xh, DEV_REG_CONTROL_ADDRESS_HIGH
			sbrc	channel, 0	; we check only bit 0 to distinguish 0x00 from 0x01
			inc		xl					; now X points to DEV_REG_CONTROL_1
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
; debug **************
.ifdef	DEBUG
			ld		r1, X
			rcall	printByteAsHex			
			rcall	println
.endif
; debug **************

			ldi		r18, 1		; length=1 byte
			rcall	can_send_packet_new

			ret



; debug **************
.ifdef	DEBUG

sHandlingSet:
.db			"Handling set", 13, 10, 0

sHandlingGet:
.db			"Handling get", 13, 10, 0

.endif
; debug **************
