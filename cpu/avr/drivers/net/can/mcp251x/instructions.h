#ifndef __CPU__AVR__DRIVERS__NET__MCP251X__INSTRUCTIONS_H
#define __CPU__AVR__DRIVERS__NET__MCP251X__INSTRUCTIONS_H


#define MCP251X_INSTRUCTION_RESET		(0xC0)
#define MCP251X_INSTRUCTION_WRITE		(0x02)
#define MCP251X_INSTRUCTION_READ		(0x03)
#define MCP251X_INSTRUCTION_BIT_MODIFY		(0x05)
#define MCP251X_INSTRUCTION_READ_BUFFER_0_SIDH	(0x90)
#define MCP251X_INSTRUCTION_READ_BUFFER_0_D0	(0x92)
#define MCP251X_INSTRUCTION_READ_BUFFER_1_SIDH	(0x94)
#define MCP251X_INSTRUCTION_READ_BUFFER_1_D0	(0x96)
#define MCP251X_INSTRUCTION_READ_STATUS         (0xA0)
#define MCP251X_INSTRUCTION_RX_STATUS           (0xB0)
#define MCP251X_INSTRUCTION_REQUEST_TO_SEND     (0x80)
#define MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0  (0x01)
#define MCP251X_INSTRUCTION_REQUEST_TO_SEND_B1  (0x02)
#define MCP251X_INSTRUCTION_REQUEST_TO_SEND_B2  (0x04)
#define MCP251X_INSTRUCTION_LOAD_BUFFER_0_SIDH	(0x40)
#define MCP251X_INSTRUCTION_LOAD_BUFFER_0_D0	(0x41)
#define MCP251X_INSTRUCTION_LOAD_BUFFER_1_SIDH	(0x42)
#define MCP251X_INSTRUCTION_LOAD_BUFFER_1_D0	(0x43)
#define MCP251X_INSTRUCTION_LOAD_BUFFER_2_SIDH	(0x44)
#define MCP251X_INSTRUCTION_LOAD_BUFFER_2_D0	(0x45)

// Result byte of MCP251X_INSTRUCTION_RX_STATUS
//
// Contents:
// - (bits 7-6) MCP251X__RX_STATUS__BUFFER
// - (bit 5) unused
// - (bits 4-3) 
// -----------------------------------------------------------------------------

// Flags for buffers that have received the message
#define MCP251X__RX_STATUS__BUFFER__0           (0x40)
#define MCP251X__RX_STATUS__BUFFER__1           (0x80)

// Flags for message type
#define MCP251X__RX_STATUS__TYPE__EXT           (0x10)
#define MCP251X__RX_STATUS__TYPE__STD           (0x00)
#define MCP251X__RX_STATUS__TYPE__REMOTE        (0x08)
#define MCP251X__RX_STATUS__TYPE__DATA          (0x00)

// Matched filter
#define MCP251X__RX_STATUS__FILTER__MASK        (0x07)

#define MCP251X__RX_STATUS__FILTER__0           (0x00)
#define MCP251X__RX_STATUS__FILTER__1           (0x01)
#define MCP251X__RX_STATUS__FILTER__2           (0x02)
#define MCP251X__RX_STATUS__FILTER__3           (0x03)
#define MCP251X__RX_STATUS__FILTER__4           (0x04)
#define MCP251X__RX_STATUS__FILTER__5           (0x05)
#define MCP251X__RX_STATUS__FILTER__0_RXB1      (0x06)
#define MCP251X__RX_STATUS__FILTER__1_RXB1      (0x07)


// Result byte of MCP251X_INSTRUCTION_READ_STATUS
#define MCP251X__STATUS__RX0IF                  (0x01)
#define MCP251X__STATUS__RX1IF                  (0x02)
#define MCP251X__STATUS__TX0REQ                 (0x04)
#define MCP251X__STATUS__TX0IF                  (0x08)
#define MCP251X__STATUS__TX1REQ                 (0x10)
#define MCP251X__STATUS__TX1IF                  (0x20)
#define MCP251X__STATUS__TX2REQ                 (0x40)
#define MCP251X__STATUS__TX2IF                  (0x80)


#endif