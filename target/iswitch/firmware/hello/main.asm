.include	"m48def.inc"

.CSEG	
.include	"interrupt-table.asm"
; placed just before reset.asm so that any unexpected interrupt will cause reset
.include	"empty-int-handlers.asm"
.include	"reset.asm"


.equ		UBRR0L_VALUE=12	;4800 @ internal 1MHz, no x2
.include	"../../../shared/src/avrasm/uart.asm"
.include	"../../../shared/src/avrasm/debug-uart-polled.asm"
