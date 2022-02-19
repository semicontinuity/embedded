// comm_usart_inbound__thread:
// receives and interprets bytes from USART
// runs in the context of main thread
// -----------------------------------------------------------------------------
#include "comm_usart_inbound__thread.h"
#include "leds_bar__data.h"
#include "leds_backlight.h"
#include <cpu/avr/usart0.h>
#include <cpu/avr/wdt.h>
#include "util/bitops.h"
#include <services/gp_buffer.h>


#if defined(COMM_USART_INBOUND__THREAD__HEADER_RECEIVED__HOST) && defined(COMM_USART_INBOUND__THREAD__HEADER_RECEIVED__BIT)
DEFINE_BITVAR(comm_usart_inbound__thread__header_received, COMM_USART_INBOUND__THREAD__HEADER_RECEIVED__HOST, COMM_USART_INBOUND__THREAD__HEADER_RECEIVED__BIT);
#endif

uint8_t comm_usart_inbound__thread__event_header;


void comm_usart_inbound__thread__handle_event(uint8_t octet) {
    __asm__ __volatile__("comm_usart_inbound__thread__handle_event:");
    wdt__reset();

    if (comm_usart_inbound__thread__header_received__get()) {
        if (comm_usart_inbound__thread__event_header & 0x80U) {                     // One of LED commands?
            if (comm_usart_inbound__thread__event_header & 0x40U) {                 // Set indicator LED command?
                comm_usart_inbound__thread__header_received__set(0);                // No indicator LEDs on this board
            } else {                                                                // LED bar or backlight LEDs control
                gp_buffer__put(octet);

                if (comm_usart_inbound__thread__event_header & 0x20U) {             // Set LED bar command

                    if (gp_buffer__size__get() >= 3*LEDS_BACKLIGHT__COUNT + 4) {    // buffer area in the end filled up
                        // size is also updated (unnecessary here)
                        gp_buffer__size__set(3*LEDS_BACKLIGHT__COUNT);
                        leds_bar__data[0] = gp_buffer__get();
                        leds_bar__data[1] = gp_buffer__get();
                        leds_bar__data[2] = gp_buffer__get();
                        leds_bar__data[3] = gp_buffer__get();
                        comm_usart_inbound__thread__header_received__set(0);
                    }

                } else {                                                            // LED backlight LEDs control

                    if (comm_usart_inbound__thread__event_header == 0x9F) {         // Set all N LEDs from the following 3*N bytes of data

                        if (gp_buffer__size__get() >= 3*LEDS_BACKLIGHT__COUNT) {    // All data received
                            comm_usart_inbound__thread__header_received__set(0);
                            leds_backlight__refresh__set(1);
                        }

                    } else  {

                        if (gp_buffer__size__get() >= 3*LEDS_BACKLIGHT__COUNT + 3) {// buffer area in the end filled up

                            const uint8_t a = gp_buffer__data[3 * LEDS_BACKLIGHT__COUNT + 0];
                            const uint8_t b = gp_buffer__data[3 * LEDS_BACKLIGHT__COUNT + 1];
                            const uint8_t c = gp_buffer__data[3 * LEDS_BACKLIGHT__COUNT + 2];

                            if (comm_usart_inbound__thread__event_header == 0x9E) { // Set all N LEDs from the following 3 bytes of data
                                gp_buffer__start();
                                for (uint8_t led = LEDS_BACKLIGHT__COUNT; led > 0; --led) {
                                    gp_buffer__put(a);
                                    gp_buffer__put(b);
                                    gp_buffer__put(c);
                                }
                            } else {                                                // Set LED number N from the following 3 bytes of data
                                uint8_t led = comm_usart_inbound__thread__event_header & 0x1F;
                                gp_buffer__size__set(led + led + led);
                                gp_buffer__put(a);
                                gp_buffer__put(b);
                                gp_buffer__put(c);
                            }

                            comm_usart_inbound__thread__header_received__set(0);
                            leds_backlight__refresh__set(1);
                        }

                    }
                }
            }
        } else {                                                                    // Comm proxy command (e.g. I2C display)
            gp_buffer__put(octet);

            if (gp_buffer__size__get() >= comm_usart_inbound__thread__event_header) {
                comm_usart_inbound__thread__header_received__set(0);                // Just read to buffer and do nothing more
            }
        }

    } else {
        comm_usart_inbound__thread__header_received__set(1);
        comm_usart_inbound__thread__event_header = octet;
        if (((comm_usart_inbound__thread__event_header & 0x80U) == 0x00U) ||
            (comm_usart_inbound__thread__event_header == 0x9F)) {
            // Comm proxy command or Set all N LEDs from the following 3*N bytes of data command
            // Will write incoming bytes from the start of the buffer.
            gp_buffer__start();
        } else {
            // Will write incoming bytes to the buffer area in the end, after space for backlight LEDs data.
            gp_buffer__size__set(3*LEDS_BACKLIGHT__COUNT);
        }
    }
}


void comm_usart_inbound__thread__start(void) {
    __asm__ __volatile__("comm_usart_inbound__thread__start:");
    usart0__rx__enabled__set(1);
}

bool comm_usart_inbound__thread__is_runnable(void) {
    return __builtin_expect(usart0__rx__complete__value__get(), false);
}

void comm_usart_inbound__thread__run(void) {
    __asm__ __volatile__("comm_usart_inbound__thread__run:");
    comm_usart_inbound__thread__handle_event(usart0__getc());
}
