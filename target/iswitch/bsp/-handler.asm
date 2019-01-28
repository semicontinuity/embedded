; INCLUDE FILE

; --------------------------------------------------------------------------------------			
; param		channel			contains the channel ID (channel is a pair of up+down buttons)
; param		logical_button	contains 0 if 'up' button was toggled, 1 if 'down'
; param		action			contains 0 if button was pressed, 1 if released
; --------------------------------------------------------------------------------------
handle_button_action:
			; handling the detected event
			
			; debug **************
			ldi		zl, low(sHandlingButtonAction<<1)
			ldi		zh, high(sHandlingButtonAction<<1)
			rcall	print
			; debug **************


			; first, current_buttons_state becomes previous_buttons_state.
			; it will be used next time
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			mov 	previous_buttons_state, current_buttons_state
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; fetch the control register corresponding to the active channel:
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; make y point to channel_0_data if channel is 0
			; make y point to channel_1_data if channel is 1
			ldi		yl, low(channel_0_data)
			ldi		yh, high(channel_0_data)
			sbrc	channel, 0	; we check only bit 0 to distinguish 0x00 from 0x01
			subi	yl, -10		; now X points to channel_1_data
			ld		current_control_register, y
			; now the register 'current_control_register' is loaded
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


			; check if the 'action' was 'pressed' (bit=0) or 'released' (bit=1)
			; ignore 'released' events
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;			sbrs	action, 0			; we check only bit 0 to distinguish 0x00 from 0x01
			;rjmp	check_can_bit		; button was released, pass to the next check
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; Should we handle the action?
			; Check the BITNUM_SWITCH_ENABLED flag in the appropriate logical device control register
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; bit is 1 => toggle the output, 0 => do nothing
			;sbrc	current_control_register, BITNUM_SWITCH_ENABLED				
			rcall	handle_dimmer_action			
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


check_can_bit:
			; check the BITNUM_CAN_NOTIFICATION flag in the appropriate logical divice control register
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; bit is 1 => send the CAN packet, 0 => don't send
			;sbrs	current_control_register, BITNUM_CAN_NOTIFICATION
			;reti	; nothing more to do, just return
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; send the 3-byte packet containing {channel, logical_button, action}
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; make x point to channel (start of data buffer, channel)
			; (NB: x already points to DEV_REG_CONTROL_x. xh is most likely 0)
			;ldi		xl, EVENT_DESC_ADDRESS_LOW
			;ldi		xh, EVENT_DESC_ADDRESS_HIGH
			;ldi		r18, EVENT_DESC_LENGTH			; length=3 bytes
			;rcall	can_send_packet_new
			ret
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			


; debug **************
sHandlingButtonAction:
.db			"Handling BTN action",13,10,0
; debug **************
