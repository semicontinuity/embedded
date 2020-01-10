#ifndef _APP_H
#define _APP_H

#include <mios32.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

extern void APP_Init(void);
extern void APP_Background(void);
extern void APP_Tick(void);
extern void APP_MIDI_Tick(void);
extern void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package);

#endif /* _APP_H */
