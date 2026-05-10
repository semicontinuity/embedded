.INCLUDE	"spi.inc"


; -----------------------------------------------------------------------------------------
; Transmit data via SPI
; param		r16		byte to transmit
; return	r16		received byte
;		r1		temp (used when DEBUG=1)
;		r0		temp (used when DEBUG=1)
; DEBUG		txbyte>SPSR|SPCR>rxbyte
; -----------------------------------------------------------------------------------------
spi_transmit:
			out		SPDR, r16

; debug **************
.ifdef	DEBUG
			mov		r1, r16
			rcall	printByteAsHex	; r1=byte (unch); r0,r16 temp
			ldi		r16, '>'
			mov		r0, r16
			rcall	printChar	; r0=char, r16 temp
.endif
; debug **************

wait_spi_transmit_complete:
			in		r16, SPSR	; When a serial transfer is complete, the SPIF Flag is set.
			sbrs	r16, SPIF	; skip next instruction if bit is set (read SPDR and exit)
			rjmp	wait_spi_transmit_complete

; debug **************
.ifdef	DEBUG
			mov		r1, r16
			; print SPSR content.
			rcall	printByteAsHex	; r1=byte (unch); r0,r16 temp

			ldi		r16, '|'
			mov		r0, r16
			rcall	printChar	; r0=char, r16 temp
			
			in		r1, SPCR
			rcall	printByteAsHex	; r1=byte (unch); r0,r16 temp

			ldi		r16, '>'
			mov		r0, r16
			rcall	printChar	; r0=char, r16 temp

			in		r1, SPDR
			rcall	printByteAsHex	; r1=byte (unchanged); temp r0,r16
			rcall	println		; temp r0,16
			mov		r16, r1	; r16 contains received byte
.else
			in		r16, SPDR
.endif
; debug **************
			ret
