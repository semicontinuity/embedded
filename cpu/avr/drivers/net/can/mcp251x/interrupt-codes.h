#ifndef __CPU__AVR__DRIVERS__MCP251X__INTERRUPT_CODES_H
#define __CPU__AVR__DRIVERS__MCP251X__INTERRUPT_CODES_H

// Values for the bit field ICOD
#define MCP251X_ICOD_NOTHING	(0)
#define MCP251X_ICOD_ERROR	(1)
#define MCP251X_ICOD_WAK	(2)
#define MCP251X_ICOD_TX0	(3)
#define MCP251X_ICOD_TX1	(4)
#define MCP251X_ICOD_TX2	(5)
#define MCP251X_ICOD_RX0	(6)
#define MCP251X_ICOD_RX1	(7)

#define ICOD_BITS_MASK		(0xE0)
#define ICOD_BITS_MASKED(icod)	((icod)<<1)

#endif