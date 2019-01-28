#ifndef __UCAN_GRPC_H
#define __UCAN_GRPC_H

#include "device.h"

#include "ucan.h"
#include "mcp251x/struct.h"

#include <stdint.h>


typedef prog_uint8_t grpc_function_id_t PROGMEM;
typedef prog_void(*grpc_function_ptr_t)(prog_void) PROGMEM;

typedef struct grpc_profile
{
    grpc_function_id_t      entryCount;
    grpc_function_id_t*     PROGMEM ids;
    grpc_function_ptr_t*    PROGMEM functions;
} grpc_profile;


//void handleGrpc(register struct mcp251x_message_buffer* __restrict buffer);

#endif // __UCAN_GRPC_H