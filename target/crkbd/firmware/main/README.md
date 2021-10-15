
## Register allocations

|    |                                                                 |
|----|-----------------------------------------------------------------|
|  0 | compiler temp                                                   |
|  1 | compiler zero                                                   |
|  2 | IO_MATRIX__IN__COLUMN0__STATE__REG                              |
|  3 | IO_MATRIX__IN__COLUMN1__STATE__REG                              |
|  4 | IO_MATRIX__IN__COLUMN2__STATE__REG                              |
|  5 | IO_MATRIX__IN__COLUMN3__STATE__REG                              |
|  6 | KEYBOARD__PORT_A__PREVIOUS_STATE__REG                           |
|  7 | KEYBOARD__PORT_B__PREVIOUS_STATE__REG                           |
|  8 | KEYBOARD__PORT_C__PREVIOUS_STATE__REG                           |
|  9 | KEYBOARD__PORT_D__PREVIOUS_STATE__REG                           |
| 10 | KEYBOARD__PORT_A__MASK__REG                                     |
| 11 | KEYBOARD__PORT_B__MASK__REG                                     |
| 12 | KEYBOARD__PORT_C__MASK__REG                                     |
| 13 | KEYBOARD__PORT_D__MASK__REG                                     |
| 14 | KEYBOARD__COMMON_MASK__REG                                      |
| 15 | allocated by compiler                                           |
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


## Programming with arduino bootloader

```
/opt/arduino-1.8.13/hardware/tools/avr/bin/avrdude -C /opt/arduino-1.8.13/hardware/tools/avr/etc/avrdude.conf -c arduino -patmega168 -U flash:w:main.hex:i -P /dev/ttyUSB0 -b19200
```