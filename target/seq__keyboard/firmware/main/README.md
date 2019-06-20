## Register allocations (circular buffers)

|    |                                                                 |
|----|-----------------------------------------------------------------|
|  0 | compiler temp                                                   |
|  1 | compiler zero                                                   |
|  2 | DATA__LEDS__INDEX__REG                                          |
|  3 | KEYBOARD__COMMON_MASK__REG                                      |
|  4 | IO_MATRIX__IN__COLUMN0__STATE__REG                              |
|  5 | IO_MATRIX__IN__COLUMN1__STATE__REG                              |
|  6 | IO_MATRIX__IN__COLUMN2__STATE__REG                              |
|  7 | IO_MATRIX__IN__COLUMN3__STATE__REG                              |
|  8 | KEYBOARD__PORT_A__PREVIOUS_STATE__REG                           |
|  9 | KEYBOARD__PORT_B__PREVIOUS_STATE__REG                           |
| 10 | KEYBOARD__PORT_C__PREVIOUS_STATE__REG                           |
| 11 | KEYBOARD__PORT_D__PREVIOUS_STATE__REG                           |
| 12 | KEYBOARD__PORT_A__MASK__REG                                     |
| 13 | KEYBOARD__PORT_B__MASK__REG                                     |
| 14 | KEYBOARD__PORT_C__MASK__REG                                     |
| 15 | KEYBOARD__PORT_D__MASK__REG                                     |
| 16 | allocated by compiler                                           |
| 17 | allocated by compiler                                           |
| 18 | allocated by compiler                                           |
| 19 | allocated by compiler                                           |
| 20 | allocated by compiler                                           |
| 21 | allocated by compiler                                           |
| 22 | allocated by compiler                                           |
| 23 | allocated by compiler                                           |
| 24 | allocated by compiler                                           |
| 25 | allocated by compiler                                           |
| 26 | TX_RING_BUFFER__HEAD__REG (L)                                   |
| 27 | TX_RING_BUFFER__HEAD__REG (H)                                   |
| 28 | TX_RING_BUFFER__TAIL__REG (L)                                   |
| 29 | TX_RING_BUFFER__TAIL__REG (H)                                   |
| 30 | IO_MATRIX__SCANNER__THREAD__IP__REG (L)                         |
| 31 | IO_MATRIX__SCANNER__THREAD__IP__REG (H)                         |


## Register allocations (simple)

|    |                                                                 |
|----|-----------------------------------------------------------------|
|  0 | compiler temp                                                   |
|  1 | compiler zero                                                   |
|  2 | DATA__LEDS__INDEX__REG                                          |
|  3 | KEYBOARD__COMMON_MASK__REG                                      |
|  4 | IO_MATRIX__IN__COLUMN0__STATE__REG                              |
|  5 | IO_MATRIX__IN__COLUMN1__STATE__REG                              |
|  6 | IO_MATRIX__IN__COLUMN2__STATE__REG                              |
|  7 | IO_MATRIX__IN__COLUMN3__STATE__REG                              |
|  8 | KEYBOARD__PORT_A__PREVIOUS_STATE__REG                           |
|  9 | KEYBOARD__PORT_B__PREVIOUS_STATE__REG                           |
| 10 | KEYBOARD__PORT_C__PREVIOUS_STATE__REG                           |
| 11 | KEYBOARD__PORT_D__PREVIOUS_STATE__REG                           |
| 12 | KEYBOARD__PORT_A__MASK__REG                                     |
| 13 | KEYBOARD__PORT_B__MASK__REG                                     |
| 14 | KEYBOARD__PORT_C__MASK__REG                                     |
| 15 | KEYBOARD__PORT_D__MASK__REG                                     |
| 16 | KEYBOARD_EVENT__REG                                             |
| 17 | allocated by compiler                                           |
| 18 | allocated by compiler                                           |
| 19 | allocated by compiler                                           |
| 20 | allocated by compiler                                           |
| 21 | allocated by compiler                                           |
| 22 | allocated by compiler                                           |
| 23 | allocated by compiler                                           |
| 24 | allocated by compiler                                           |
| 25 | allocated by compiler                                           |
| 26 | allocated by compiler                                           |
| 27 | allocated by compiler                                           |
| 28 | allocated by compiler                                           |
| 29 | allocated by compiler                                           |
| 30 | IO_MATRIX__SCANNER__THREAD__IP__REG (L)                         |
| 31 | IO_MATRIX__SCANNER__THREAD__IP__REG (H)                         |


## Register allocations (queues)

|    |                                                                 |
|----|-----------------------------------------------------------------|
|  0 | compiler temp                                                   |
|  1 | compiler zero                                                   |
|  2 | DATA__LEDS__INDEX__REG                                          |
|  3 | KEYBOARD__COMMON_MASK__REG                                      |
|  4 | IO_MATRIX__IN__COLUMN0__STATE__REG                              |
|  5 | IO_MATRIX__IN__COLUMN1__STATE__REG                              |
|  6 | IO_MATRIX__IN__COLUMN2__STATE__REG                              |
|  7 | IO_MATRIX__IN__COLUMN3__STATE__REG                              |
|  8 | KEYBOARD__PORT_A__PREVIOUS_STATE__REG                           |
|  9 | KEYBOARD__PORT_B__PREVIOUS_STATE__REG                           |
| 10 | KEYBOARD__PORT_C__PREVIOUS_STATE__REG                           |
| 11 | KEYBOARD__PORT_D__PREVIOUS_STATE__REG                           |
| 12 | COMM_ENCODER__ENCODER0__DELTA__REG                              |
| 13 | COMM_ENCODER__ENCODER1__DELTA__REG                              |
| 14 | COMM_ENCODER__ENCODER2__DELTA__REG                              |
| 15 | COMM_ENCODER__ENCODER3__DELTA__REG                              |
| 16 | KEYBOARD__PORT_A__MASK__REG                                     |
| 17 | KEYBOARD__PORT_B__MASK__REG                                     |
| 18 | KEYBOARD__PORT_C__MASK__REG                                     |
| 19 | KEYBOARD__PORT_D__MASK__REG                                     |
| 20 | COMM_EVENTS__EVENT__REG                                         |
| 21 | allocated by compiler                                           |
| 22 | allocated by compiler                                           |
| 23 | allocated by compiler                                           |
| 24 | allocated by compiler                                           |
| 25 | allocated by compiler                                           |
| 26 | allocated by compiler                                           |
| 27 | allocated by compiler                                           |
| 28 | allocated by compiler                                           |
| 29 | allocated by compiler                                           |
| 30 | IO_MATRIX__SCANNER__THREAD__IP__REG (L)                         |
| 31 | IO_MATRIX__SCANNER__THREAD__IP__REG (H)                         |

## General-purpose I/O register allocations

### GPIOR0
|    |                                                                 |
|----|-----------------------------------------------------------------|
|  0 | COMM_BUTTONS__BUTTON0__EVENT_PENDING                            |
|  1 | COMM_BUTTONS__BUTTON0__EVENT_VALUE                              |
|  2 | COMM_BUTTONS__BUTTON1__EVENT_PENDING                            |
|  3 | COMM_BUTTONS__BUTTON1__EVENT_VALUE                              |
|  4 | COMM_BUTTONS__BUTTON2__EVENT_PENDING                            |
|  5 | COMM_BUTTONS__BUTTON2__EVENT_VALUE                              |
|  6 | COMM_BUTTONS__BUTTON3__EVENT_PENDING                            |
|  7 | COMM_BUTTONS__BUTTON3__EVENT_VALUE                              |
