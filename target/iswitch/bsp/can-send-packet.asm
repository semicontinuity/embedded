; -----------------------------------------------------------------------------------------
; Send CAN packet

; debug **************
.ifdef	DEBUG

sSendingCANPacket:
.db			"TX CAN packet...", 13, 10, 0

sInitiatedTransmission:
.db			"TX Requested", 13, 10, 0

.endif
; debug **************




; param	X	<>		data to send
; param	r18			length
; TODO: initialize transmit buffers!
; -----------------------------------------------------------------------------------------
can_send_packet_new:
			ldi		r17, MCP251X_REGISTER_TXB0DLC

; param	X	<>		data to send
; param	r18			length
; param	r17			MCP251X_REGISTER_TXB0DLC for TX buffer 0,
;					MCP251X_REGISTER_TXB1DLC for TX buffer 1,
;					MCP251X_REGISTER_TXB2DLC for TX buffer 2
; TODO: initialize transmit buffers!
; -----------------------------------------------------------------------------------------
can_send_packet_generic:			

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sSendingCANPacket<<1)
			ldi		zh, high(sSendingCANPacket<<1)
			rcall	print
.endif
; debug **************

			; Set packet length
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			rcall	mcp251x_write_byte	; r17=controller register, r18=byte to transmit (=length)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			; Transfer packet from memory to CAN controller
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; change MCP251X_REGISTER_TXBxDLC to MCP251X_REGISTER_TXBxD0
			subi	r17, (MCP251X_REGISTER_TXB0DLC-MCP251X_REGISTER_TXB0D0)
;			ldi		r17, MCP251X_REGISTER_TXB0D0
			rcall	mcp251x_write_bytes	; r17=controller register, r18=length; X=buffer pointer
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; Send a packet = Set TXBxCTRL
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			; change MCP251X_REGISTER_TXBxD0 to MCP251X_REGISTER_TXBxCTRL
			subi	r17, (MCP251X_REGISTER_TXB0D0-MCP251X_REGISTER_TXB0CTRL)
;			ldi		r17, MCP251X_REGISTER_TXB0CTRL
			ldi		r18, 0x08	; TODO: 0x08=txreq
			rcall	mcp251x_write_byte
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sInitiatedTransmission<<1)
			ldi		zh, high(sInitiatedTransmission<<1)
			rcall	print
.endif
; debug **************

			ret
