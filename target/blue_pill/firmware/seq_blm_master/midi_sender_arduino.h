#include "midi_sender.h"

// no running status optimisation
// only channel messages
// no locking: use from the loop thread only
void midi__send_package(midi_package_t p) {
    Serial2.write(p.evnt0);
    Serial2.write(p.evnt1);
    if ((p.evnt0 & 0xE0U) != 0xC0U) {
        Serial2.write(p.evnt2);
    }
}
