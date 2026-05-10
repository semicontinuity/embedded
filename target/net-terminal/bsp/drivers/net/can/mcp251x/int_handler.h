#ifndef __DRIVERS__NET__CAN__MCP251X__INT_HANDLER_H
#define __DRIVERS__NET__CAN__MCP251X__INT_HANDLER_H


INLINE void mcp251x__int_handler__start(void);

/**
 *  Handler for the interrupt from MCP2515 CAN controller.
 */
INLINE void mcp2515__int_handler__run(void);


#endif

