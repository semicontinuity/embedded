// =============================================================================
// Error-tolerant UART protocol handler
// Protocol:
// The only supported command is SET BUTTONS TAO (simulate button event)
//
// Every event is coded in two bytes:
// 1st byte: 00XXXXXX, where XXXXXX is the bit mask of buttons pressed.
// 2nd byte: 11XXXXXX, where XXXXXX is the bit mask of buttons pressed.
// the bit masks in these two bytes must be the same, otherwise it's an error.
// =============================================================================
#ifndef __PROTOCOL_HANDLER_H
#define __PROTOCOL_HANDLER_H


void protocol_handler__accept(uint8_t value);


#endif
