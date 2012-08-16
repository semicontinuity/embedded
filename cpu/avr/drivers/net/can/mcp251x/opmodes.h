// =============================================================================
// The constants for MCP251x Operation modes.
// Describe the valid combination of bits in the registers
// CANCTRL (REQOP*) and CANSTAT (OPMOD*).
// =============================================================================

#ifndef __CPU__AVR__DRIVERS__NET__MCP251X__OPMODES_H
#define __CPU__AVR__DRIVERS__NET__MCP251X__OPMODES_H

#define MCP251X_OPMODE_NORMAL		(0x00)
#define MCP251X_OPMODE_SLEEP		(0x20)
#define MCP251X_OPMODE_LOOPBACK		(0x40)
#define MCP251X_OPMODE_LISTEN_ONLY	(0x60)
#define MCP251X_OPMODE_CONFIGURATION	(0x80)

#endif