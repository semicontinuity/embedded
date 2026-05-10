.INCLUDE	"m48def.inc"


; -----------------------------------------------------------------------------------------
; Schematics:
;
; PD2	I	External mains sync
; PD5	O	Channel 0 triac control
; -----------------------------------------------------------------------------------------


.CSEG
.ORG		0
.INCLUDE	"interrupt-table.asm"
.INCLUDE	"empty-int-handlers.asm"
.INCLUDE	"reset.asm"

.INCLUDE	"pwm.asm"
