// =============================================================================
// Controller.
// Translates button events into motor motion.
// =============================================================================

#include <avr/eeprom.h>
#include "buttons_scanner.h"
#include "motor_controller.h"


uint8_t EEMEM ee__controller__enabled = CONTROLLER__ENABLED;
uint8_t controller__enabled;


inline static void controller__init(void) {
    controller__enabled = eeprom_read_byte(&ee__controller__enabled);
}


inline static void controller__run(void) {
    if (controller__enabled) {
        if (buttons_scanner__button1__is_changed()) {
            if (buttons_scanner__button1__is_released())
                motor_controller__stop();
            else
                motor_controller__move_up();
        }
        if (buttons_scanner__button2__is_changed()) {
            if (buttons_scanner__button2__is_released())
                motor_controller__stop();
            else
                motor_controller__move_down();
        }
    }
}
