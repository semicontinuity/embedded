; -----------------------------------------------------------------------------------------
; Initialize CAN controller

; debug **************
.ifdef	DEBUG

sInitializingCANController:
.db			"Initializing CAN...", 13, 10, 0

sCANControllerInitialized:
.db			"CAN initialized", 13, 10, 0

.endif
; debug **************

init_mcp251x:
; -----------------------------------------------------------------------------------------
				
; debug **************
.ifdef	DEBUG
			ldi		zl, low(sInitializingCANController<<1)
			ldi		zh, high(sInitializingCANController<<1)
			rcall	print
.endif
; debug **************


			; Reset MCP2515
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			spi_start_transaction
			ldi		r16, MCP251X_INSTRUCTION_RESET
			rcall	spi_transmit
			spi_finish_transaction
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; debug **************
			; TODO: remove???
			rcall	delay
			; debug **************
			; Set CNF1
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_CNF1
			ldi		r18, 0x07	; TODO
			rcall	mcp251x_write_byte
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; debug **************
			; TODO: remove???
			rcall	delay
			; debug **************

			; Set CNF2
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_CNF2
			ldi		r18, 0x90	; TODO
			rcall	mcp251x_write_byte
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; debug **************
			; TODO: remove???
			rcall	delay
			; debug **************

			; Set CNF3
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_CNF3
			ldi		r18, 0x02	; TODO
			rcall	mcp251x_write_byte
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; debug **************
			; TODO: remove?
			rcall	delay
			; debug **************


			; Configure MCP251x CAN controller to properly send messages
			; According to the addressing scheme,
			; target=0000|0000000 (root node)
			; source=0000|0000001 (this node)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_TXB0SIDH
			ldi		r18, (0<<7)|(0<<0)	; part of target address
			rcall	mcp251x_write_byte
			ldi		r17, MCP251X_REGISTER_TXB0SIDL
			ldi		r18, (0<<5)|MCP251X_MASK_ID_EXIDE	; part of target address
			rcall	mcp251x_write_byte
			ldi		r17, MCP251X_REGISTER_TXB0EID8
			ldi		r18, (0<<7)|(1<<0)	; part of source address
			rcall	mcp251x_write_byte
			ldi		r17, MCP251X_REGISTER_TXB0EID0
			ldi		r18, (0<<5)			; part of source address
			rcall	mcp251x_write_byte
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; debug **************
			; TODO: remove???
			rcall	delay
			; debug **************

			; Configure MCP251x CAN controller to properly filter incoming messages
			; CAN controller should accept only messages directly addressed to itself.
			; SHCAN address of the node is 0:1
			; (Set RXM0 register inside MCP251x to examine all SID bits,
			;  but don't examine other bits)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_RXM0SIDH
			ldi		r18, 0xFF
			rcall	mcp251x_write_byte
			ldi		r17, MCP251X_REGISTER_RXM0SIDL
			ldi		r18, 0xE0 + 0x08	; examine SID bits; applied only to ext frames
			rcall	mcp251x_write_byte
			ldi		r17, MCP251X_REGISTER_RXM0EID8
			ldi		r18, 0x00			; don't examine
			rcall	mcp251x_write_byte
			ldi		r17, MCP251X_REGISTER_RXM0EID0
			ldi		r18, 0x00
			rcall	mcp251x_write_byte
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; debug **************
			; TODO: remove???
			rcall	delay
			; debug **************

			; Configure MCP251x CAN controller to properly filter incoming messages
			; addressed to our SHCAN address 0:1
			; We have to specify SID bits, other bits don't care.
			; SHCAN address is encoded into SIDH=00|000001, SIDL=000|*			
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_RXF0SIDH
			ldi		r18, 0x01
			rcall	mcp251x_write_byte
			ldi		r17, MCP251X_REGISTER_RXF0SIDL
			ldi		r18, 0x00
			rcall	mcp251x_write_byte
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; debug **************
			; TODO: remove???
			rcall	delay
			; debug **************

			; Receive buffer 0 inside MCP251x CAN controller will accept only ext. frames matching filter
			; (Initialize RXB0CTRL register inside MCP251x)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_RXB0CTRL
			ldi		r18, MCP251X_RXBCTRL_RECEIVE_EXT_FLT
			rcall	mcp251x_write_byte			
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; debug **************
			; TODO: remove???
			rcall	delay
			; debug **************

			; Enable interrupts from RXB0 inside MCP251x CAN controller
			; (Set RX0IE bit in CANINTE register inside MCP251x)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_CANINTE
			ldi		r18, MCP251X_MASK_INT_RX0
			rcall	mcp251x_write_byte
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			; debug **************
			; TODO: remove???
			rcall	delay
			; debug **************

			; Switch MCP251x CAN controller to NORMAL mode - it will start interfacing the bus.
			; (Initialize CANCTRL register inside MCP251x)
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ldi		r17, MCP251X_REGISTER_CANCTRL
			ldi		r18, MCP251X_OPMODE_NORMAL | MCP251X_CANCTRL_CLKEN | MCP251X_CANCTRL_SCLK_DIV_8
			rcall	mcp251x_write_byte
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

; debug **************
.ifdef	DEBUG
			ldi		zl, low(sCANControllerInitialized<<1)
			ldi		zh, high(sCANControllerInitialized<<1)
			rcall	print
.endif
; debug **************

			ret
