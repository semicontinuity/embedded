// =============================================================================
// CAN Controller driver emulator.
// =============================================================================

#include "can_emu.h"

mcp251x_message_buffer can__txb0
#ifdef CANP_TXB0_EXIDE
= {
    .header = {
        .id = CANP_HEADER(
            CANP_TXB0_EXIDE, CANP_TXB0_TAG,
            CANP_TXB0_CPTY_NET, CANP_TXB0_CPTY_ADDR,
            CANP_TXB0_HOST_NET, CANP_TXB0_HOST_ADDR,
            CANP_TXB0_OWNER, CANP_TXB0_AUX, CANP_TXB0_REPORT_ID
        ),
        .dlc = CANP_TXB0_REPORT_SIZE
    },
    .data = {
        0, 0, 0, 0, 0, 0, 0, 0
    }
};
#else
;
#endif


mcp251x_message_buffer can__txb1
#ifdef CANP_TXB1_EXIDE
= {
    .header = {
        .id = CANP_HEADER(
            CANP_TXB1_EXIDE, CANP_TXB1_TAG,
            CANP_TXB1_CPTY_NET, CANP_TXB1_CPTY_ADDR,
            CANP_TXB1_HOST_NET, CANP_TXB1_HOST_ADDR,
            CANP_TXB1_OWNER, CANP_TXB1_AUX, CANP_TXB1_REPORT_ID
        ),
        .dlc = CANP_TXB1_REPORT_SIZE
    },
    .data = {
        0, 0, 0, 0, 0, 0, 0, 0
    }
};
#else
;
#endif


mcp251x_message_buffer can__txb2
#ifdef CANP_TXB2_EXIDE
= {
    .header = {
        .id = CANP_HEADER(
            CANP_TXB2_EXIDE, CANP_TXB2_TAG,
            CANP_TXB2_CPTY_NET, CANP_TXB2_CPTY_ADDR,
            CANP_TXB2_HOST_NET, CANP_TXB2_HOST_ADDR,
            CANP_TXB2_OWNER, CANP_TXB2_AUX, CANP_TXB2_REPORT_ID
        ),
        .dlc = CANP_TXB2_REPORT_SIZE
    },
    .data = {
        0, 0, 0, 0, 0, 0, 0, 0
    }
};
#else
;
#endif

// TODO: Configure RXB0CTRL and RXB1CTRL
