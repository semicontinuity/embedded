#ifndef __ENDPOINTS__SECURITY__STATE_H
#define __ENDPOINTS__SECURITY__STATE_H

#include <stdint.h>


INLINE void security__state__request_broadcast(void);

INLINE void security__state__broadcast(void);

INLINE void security__state__set_data(const uint8_t* data);


#endif