## Register allocations

|    |                                                                 |
|----|-----------------------------------------------------------------|
|  0 | compiler temp                                                   |
|  1 | compiler zero                                                   |
|  2 | allocated by compiler                                           |
|  3 | allocated by compiler                                           |
|  4 | allocated by compiler                                           |
|  5 | allocated by compiler                                           |
|  6 | allocated by compiler                                           |
|  7 | COMM_LEDS__HEADER__REG                                          |
|  8 | allocated by compiler                                           |
|  9 | allocated by compiler                                           |
| 10 | allocated by compiler                                           |
| 11 | KEYBOARD__PORT_B__PREVIOUS_STATE__REG                           |
| 12 | KEYBOARD__PORT_C__PREVIOUS_STATE__REG                           |
| 13 | KEYBOARD__PORT_D__PREVIOUS_STATE__REG                           |
| 14 | allocated by compiler                                           |
| 15 | allocated by compiler                                           |
| 16 | KEYBOARD__PORT_B__MASK__REG                                     |
| 17 | KEYBOARD__PORT_C__MASK__REG                                     |
| 18 | KEYBOARD__PORT_D__MASK__REG                                     |
| 19 | COMM_KEYBOARD__EVENT__REG                                       |
| 20 | COMM_LEDS__DATA__INDEX__REG                                     |
| 21 | allocated by compiler                                           |
| 22 | allocated by compiler                                           |
| 23 | allocated by compiler                                           |
| 24 | allocated by compiler                                           |
| 25 | allocated by compiler                                           |
| 26 | allocated by compiler                                           |
| 27 | allocated by compiler                                           |
| 28 | allocated by compiler                                           |
| 29 | allocated by compiler                                           |
| 30 | COMM_LEDS__MEMORY__PTR__REG (L)                                 |
| 31 | COMM_LEDS__MEMORY__PTR__REG (H)                                 |


## Flag allocations

|        |   |                                                         |
|--------|---|---------------------------------------------------------|
| GPIOR0 | 0 | COMM_LEDS__HEADER_RECEIVED                              |
| GPIOR0 | 1 | COMM_LEDS__HEADER_PARSED                                |
| GPIOR0 | 2 | LEDS__REFRESH                                           |


## Notes

The WS2812 pin is kept low between transmissions, so LEDs are kept in reset.
Data transmission to LEDs can commence right away, without issuing reset pulse.
As a consequence, the interval between LED updates must be at least 50uS.
