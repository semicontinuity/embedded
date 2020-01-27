// Translates button events from BLM boards into MIDI messages.
// BLM Maser protocol for button events:
// +---------------------------------------+-----------------------------------+
// | BLM16x16 Buttons                      | 9<row> <column> <button-state>    |
// | Extra column buttons                  | 9<row> <40+column> <button-state> |
// | Extra row buttons                     | 90 <60+column> <button-state>     |
// | Additional extra buttons (e.g. Shift) | 9F <60+function> <button-state>   |
// +---------------------------------------+-----------------------------------+
// <button-state>: 00: depressed, 7F: pressed
// -----------------------------------------------------------------------------
#include <stdint.h>
#include "midi_sender.h"

void blm_boards__comm_events__handler__midi__on_button_event(uint8_t board, uint8_t button, bool is_pressed) {
    // No extra rows / columns / buttons exist at the moment
    uint8_t matrix_x = board & 0x03U;
    uint8_t matrix_y = board >> 2U;
    uint8_t local_x = button & 0x03U;
    uint8_t local_y = button >> 2U;
    uint8_t column = (matrix_x << 2U) + local_x;
    uint8_t row = (matrix_y << 2U) + local_y;

    midi_package_t p = {.ALL = 0};
    p.event = NoteOn;
    p.chn = row;
    p.note = column;
    p.velocity = is_pressed ? 0x7F : 0x00;
    midi_sender__send_package(p);
}
