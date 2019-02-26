#ifndef __CPU__AVR__DRIVERS__NET__MCP251X__BITDEFS_H
#define __CPU__AVR__DRIVERS__NET__MCP251X__BITDEFS_H

// Bit definitions for register CANSTAT
#define MCP251X_ICOD0		(1)
#define MCP251X_ICOD1		(2)
#define MCP251X_ICOD2		(3)
#define MCP251X_OPMOD0		(5)
#define MCP251X_OPMOD1		(6)
#define MCP251X_OPMOD2		(7)

// Bit definitions for register CANCTRL
#define MCP251X_CLKPRE0		(0)
#define MCP251X_CLKPRE1		(1)
#define MCP251X_CLKEN		(2)
#define MCP251X_OSM		(3)
#define MCP251X_ABAT		(4)
#define MCP251X_REQOP0		(5)
#define MCP251X_REQOP1		(6)
#define MCP251X_REQOP2		(7)

// Bit definitions for register CANINTE
#define MCP251X_RX0IE		(0)
#define MCP251X_RX1IE		(1)
#define MCP251X_TX0IE		(2)
#define MCP251X_TX1IE		(3)
#define MCP251X_TX2IE		(4)
#define MCP251X_ERRIE		(5)
#define MCP251X_WAKIE		(6)
#define MCP251X_MERRIE		(7)

// Bit definitions for register CANINTF
#define MCP251X_RX0IF		(0)
#define MCP251X_RX1IF		(1)
#define MCP251X_TX0IF		(2)
#define MCP251X_TX1IF		(3)
#define MCP251X_TX2IF		(4)
#define MCP251X_ERRIF		(5)
#define MCP251X_WAKIF		(6)
#define MCP251X_MERRIF		(7)

// Bit definitions for register EFLG
#define MCP251X_EWARN		(0)
#define MCP251X_RXWAR		(1)
#define MCP251X_TXWAR		(2)
#define MCP251X_RXEP		(3)
#define MCP251X_TXEP		(4)
#define MCP251X_TXBO		(5)
#define MCP251X_RX0OVR		(6)
#define MCP251X_RX1OVR		(7)

// Bit definitions for registers RxFnSIDL
#define MCP251X_EXIDE		(3)

// Bit definitions for registers TXxCTRL
#define MCP251X_TXREQ		(3)


// Bit definitions for registers RXBxCTRL
#define MCP251X_RXRTR		(3)

// Bit definitions for registers RXBxSIDL
#define MCP251X_IDE		(3)
#define MCP251X_SRR		(4)

// Bit definitions for registers RXBxDLC
#define MCP251X_RTR		(6)


// Bit definitions for register CNF1
#define MCP251X_BRP0            (0)
#define MCP251X_BRP1            (1)
#define MCP251X_BRP2            (2)
#define MCP251X_BRP3            (3)
#define MCP251X_BRP4            (4)
#define MCP251X_BRP5            (5)
#define MCP251X_SJW0            (6)
#define MCP251X_SJW1            (7)

// Bit definitions for register CNF2
#define MCP251X_PRSEG0          (0)
#define MCP251X_PRSEG1          (1)
#define MCP251X_PRSEG2          (2)
#define MCP251X_PHSEG10         (3)
#define MCP251X_PHSEG11         (4)
#define MCP251X_PHSEG12         (5)
#define MCP251X_SAM             (6)
#define MCP251X_BLTMODE         (7)

// Bit definitions for register CNF3
#define MCP251X_PHSEG20         (0)
#define MCP251X_PHSEG21         (1)
#define MCP251X_PHSEG22         (2)
#define MCP251X_WAKFIL          (6)
#define MCP251X_SOF             (7)

// Bit definitions for register BFPCTRL
#define MCP251X_B0BFM           (0)
#define MCP251X_B1BFM           (1)
#define MCP251X_B0BFE           (2)
#define MCP251X_B1BFE           (3)
#define MCP251X_B0BFS           (4)
#define MCP251X_B1BFS           (5)


#endif