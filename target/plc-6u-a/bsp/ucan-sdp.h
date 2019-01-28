#ifndef __UCAN_SDP_H
#define __UCAN_SDP_H

#include "device.h"

#include "ucan.h"
#include "mcp251x/struct.h"

void handleUcanSdpFrame(register struct mcp251x_message_buffer* buffer);

#endif // __UCAN_SDP_H