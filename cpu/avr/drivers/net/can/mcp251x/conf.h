// =============================================================================
// The constants for MCP251x configuration.
// Describe the valid combination of bits in the registers CNF1, CNF2 and CNF3.
// =============================================================================

#ifndef __CPU__AVR__DRIVERS__NET__MCP251X__CONF_H
#define __CPU__AVR__DRIVERS__NET__MCP251X__CONF_H

// Bit masks applicable for the register CNF1.
// #############################################################################

// Parameter MCP251X__CONF__SYNC_JUMP_WIDTH_BITS, starts at bit SJW0
#define MCP251X_SYNC_JUMP_WIDTH_MASK            (0x03)
#define MCP251X_SYNC_JUMP_WIDTH_1TQ             (0x00)
#define MCP251X_SYNC_JUMP_WIDTH_2TQ             (0x01)
#define MCP251X_SYNC_JUMP_WIDTH_3TQ             (0x02)
#define MCP251X_SYNC_JUMP_WIDTH_4TQ             (0x03)

// Parameter MCP251X__CONF__BAUD_RATE_PRESCALER_BITS, starts at bit BRP0
#define MCP251X_BAUD_RATE_PRESCALER_MASK        (0x3F)


// Bit masks applicable for the register CNF2.
// #############################################################################

// Parameter MCP251X__CONF__BIT_TIME_LENGTH_MODE, starts at bit BLTMODE
#define MCP251X_BIT_TIME_LENGTH_MODE_MASK       (0x01)
#define MCP251X_BIT_TIME_LENGTH_MODE_PHSEG      (0x01)
#define MCP251X_BIT_TIME_LENGTH_MODE_PS1_OR_IPT (0x00)

// Parameter MCP251X__CONF__BUS_SAMPLING_MODE, starts at bit SAM
#define MCP251X_BUS_SAMPLING_MODE_MASK          (0x01)
#define MCP251X_BUS_SAMPLING_MODE_X3            (0x01)
#define MCP251X_BUS_SAMPLING_MODE_X1            (0x00)

// Parameter MCP251X__CONF__PROP_SEGMENT_1_BITS, starts at bit PHSEG10
#define MCP251X_PROP_SEGMENT_1_LENGTH_MASK      (0x07)

// Parameter MCP251X__CONF__PROP_SEGMENT_BITS, starts at bit PRSEG0
#define MCP251X_PROP_SEGMENT_LENGTH_MASK        (0x07)


// Bit masks applicable for the register CNF3.
// #############################################################################

// Parameter MCP251X__CONF__CLKOUT_MODE, starts at bit SOF
#define MCP251X_CLKOUT_MODE_MASK                (0x01)
#define MCP251X_CLKOUT_MODE_SOF_SIGNAL          (0x01)
#define MCP251X_CLKOUT_MODE_CLKOUT_SIGNAL       (0x00)

// Parameter MCP251X__CONF__WAKEUP_FILTER_MODE, starts at bit WAKFIL
#define MCP251X_WAKEUP_FILTER_MODE_MASK         (0x01)
#define MCP251X_WAKEUP_FILTER_ENABLED           (0x01)
#define MCP251X_WAKEUP_FILTER_DISABLED          (0x00)

// Parameter MCP251X__CONF__PROP_SEGMENT_2_BITS, starts at bit PHSEG20
#define MCP251X_PROP_SEGMENT_2_LENGTH_MASK      (0x07)


#endif