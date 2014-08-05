// =============================================================================
// Pool controller extender - main module.
// =============================================================================

#ifndef __MAIN_H
#define __MAIN_H

#include <stdbool.h>
#include <stdint.h>

// =============================================================================
// Handlers
// =============================================================================

void comm__rx__on_data(const uint8_t value);

bool comm__tx__has_next(void);

uint8_t comm__tx__next(void);

void comm__tx__on_done(void);

void pool_controller__on_lcd_event(const uint8_t value);

void pool_controller__on_keypad_event(const uint8_t value);

void pool_controller__on_led_event(const uint8_t value);

void pool_controller__on_system_timer_event(void);


#endif
