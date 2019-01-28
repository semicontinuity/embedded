.INCLUDE	"../../../shared/src/avrasm/mcp251xdef.inc"

; -----------------------------------------------------------------------------------------
; Write byte to MCP25xx register
; param		r17		address
; param		r18		byte to transmit
; -----------------------------------------------------------------------------------------
mcp251x_write_byte:

; debug **************
.ifdef	DEBUG
			; print debug message in format "Rxx<yy"
			ldi		r16, 'R'
			mov		r0, r16
			rcall	printChar		; r0=char, r16 temp
			mov		r1, r17
			rcall	printByteAsHex		; r1=byte (unch); r0,r16 temp
			ldi		r16, '='
			mov		r0, r16
			rcall	printChar		; r0=char, r16 temp
			mov		r1, r18
			rcall	printByteAsHex		; r1=byte (unch); r0,r16 temp
			rcall	println			; temp r0,16
.endif
; debug **************

			spi_start_transaction

			ldi		r16, MCP251X_INSTRUCTION_WRITE
			rcall	spi_transmit			; r16: input + output (ignore)

			mov		r16, r17		; address
			rcall	spi_transmit			; r16: input + output (ignore)

			mov		r16, r18		; data
			rcall	spi_transmit			; r16: input + output (ignore)

			spi_finish_transaction
			ret


; -----------------------------------------------------------------------------------------
; Write bytes to a set of MCP251x registers
; param		r17		r17		CAN register address
; param		r18>0	0		number of bytes to write
; param		X		X+r18	pointer to the memory location to store the data
; -----------------------------------------------------------------------------------------
mcp251x_write_bytes:
			spi_start_transaction

			ldi		r16, MCP251X_INSTRUCTION_WRITE
			rcall	spi_transmit

; debug **************
.ifdef	DEBUG
			; print debug message in format "Rxx<yyzz.."
			ldi		r16, 'R'
			mov		r0, r16
			rcall	printChar
			mov		r1, r17
			rcall	printByteAsHex
			ldi		r16, '='
			mov		r0, r16
			rcall	printChar
			rcall	println
.endif
; debug **************
			
			mov		r16, r17		; address
			rcall	spi_transmit

mcp251x_write_bytes__next:			
			ld		r16, x+

; debug **************
.ifdef	DEBUG
			push	r16
			mov		r1, r16
			rcall	printByteAsHex
			pop		r16
.endif
; debug **************

			rcall	spi_transmit
			dec		r18
			brne	mcp251x_write_bytes__next	

			spi_finish_transaction

			ret


; -----------------------------------------------------------------------------------------
; Read byte from MCP251x register
; param		r17		CAN register address
; return	r16		contents of the CAN register
; -----------------------------------------------------------------------------------------
mcp251x_read_byte:
			spi_start_transaction

			ldi		r16, MCP251X_INSTRUCTION_READ
			rcall	spi_transmit		; r16: input + output (ignore)

			mov		r16, r17	; address
			rcall	spi_transmit            ; r16: input + output (ignore)

			rcall	spi_transmit		; r16: input (ignore) + output

			spi_finish_transaction
; debug **************
.ifdef	DEBUG
			push	r16
			mov		r18, r16
			ldi		r16, 'R'
			mov		r0, r16
			rcall	printChar		; r0=char, r16 temp
			mov		r1, r17
			rcall	printByteAsHex		; r1=byte (unch); r0,r16 temp
			ldi		r16, ':'
			mov		r0, r16
			rcall	printChar		; r0=char, r16 temp
			mov		r1, r18
			rcall	printByteAsHex		; r1=byte (unch); r0,r16 temp
			rcall	println			; temp r0,16
			pop		r16
.endif
; debug **************

			ret


; -----------------------------------------------------------------------------------------
; Read bytes from a set of MCP251x registers
; param		r17		r17		CAN register address
; param		r18>0	0		number of bytes to read
; param		X		X+r18	pointer to the memory location to store the data
; return	SRAM	contents of the registers 
; -----------------------------------------------------------------------------------------
mcp251x_read_bytes:
			spi_start_transaction

			ldi		r16, MCP251X_INSTRUCTION_READ
			rcall	spi_transmit

			mov		r16, r17		; address
			rcall	spi_transmit

mcp251x_read_bytes__next:
			rcall	spi_transmit
			st		x+,r16
			dec		r18
			brne	mcp251x_read_bytes__next	

			spi_finish_transaction
			ret
