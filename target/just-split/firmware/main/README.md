# Firmware for Just Split keyboard

## Base USART feature set
* Sends duplicate button key press/release reports via USART @ 38400.
* Incoming commands via USART @ 38400 to paint on OLED display and/or control LEDs.
* WDT used to auto-reset to the beginning of RX packet boundary after 15ms of RX inactivity.

## USART commands format

```

MSB     |                                                                                     LSB     
--------+----------------------------------------------------------------------------------------
bit 7=0 | bits 0-6: length of I2C data packet that follows           
bit 7=1 | bit 6=1 | bits 0-5: values of 6 individual LED channels           
        | bit 6=0 | bit 5=1 | Set LED bar bits from the following 4 bytes of data           
        | bit 6=0 | bit 5=0 | bits 0-4 == 31: Set all N LEDs from the following 3*N bytes of data
        | bit 6=0 | bit 5=0 | bits 0-4 == 30: Set all N LEDs from the following 3 bytes of data
        | bit 6=0 | bit 5=0 | bits 0-4 == N: Set LED number N from the following 3 bytes of data

```

## Register allocation

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
| 15 | LEDS_BAR__DATA__INDEX__REG / GP_RING_BUFFER__SIZE__REG          |
| 16 | GP_BUFFER__SIZE__REG                                            |
| 17 | allocated by compiler                                           |
| 18 | allocated by compiler                                           |
| 19 | allocated by compiler                                           |
| 20 | allocated by compiler                                           |
| 21 | allocated by compiler                                           |
| 22 | allocated by compiler                                           |
| 23 | allocated by compiler                                           |
| 24 | allocated by compiler                                           |
| 25 | allocated by compiler                                           |
| 26 | GP_RING_BUFFER__PTR__REG (L)                                    |
| 27 | GP_RING_BUFFER__PTR__REG (H)                                    |
| 28 | GP_BUFFER__PTR__REG (L)                                         |
| 29 | GP_BUFFER__PTR__REG (H)                                         |
| 30 | IO_MATRIX__SCANNER__THREAD__IP__REG (L)                         |
| 31 | IO_MATRIX__SCANNER__THREAD__IP__REG (H)                         |


## Programming with arduino bootloader (untested)

```
/opt/arduino-1.8.13/hardware/tools/avr/bin/avrdude -C /opt/arduino-1.8.13/hardware/tools/avr/etc/avrdude.conf -c arduino -patmega48p -U flash:w:main.hex:i -P /dev/ttyUSB0 -b19200
```