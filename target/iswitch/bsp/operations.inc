; This file contains a list of operation codes encoded in CAN Messages
; A payload of a CAN message is up to 8 bytes:
; <OPCODE> [ARG1] .. [ARG7]
;
; A table of opcodes:
;

.equ	OPCODE_INVOKE	= 0x00
.equ	OPCODE_RESET	= 0xFF
