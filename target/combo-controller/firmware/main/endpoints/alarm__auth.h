#ifndef __ENDPOINTS__ALARM__AUTH_H
#define __ENDPOINTS__ALARM__AUTH_H


#include "flags/notifications_pending__alarm__auth.h"
#include "flags/notifications_pending.h"


INLINE void alarm__auth__broadcast(void) {
    notifications_pending__alarm__auth__set(1);
    notifications_pending__set(1);
}


#endif