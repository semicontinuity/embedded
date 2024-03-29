# Firmware for the Harmony keyboard (hw v2)

## Button codes (left half)
```

| 0x04 | 0x03 | 0x02 | 0x01 | 0x00 |
| 0x0C | 0x0B | 0x0A | 0x09 | 0x08 |
| 0x14 | 0x13 | 0x12 | 0x11 | 0x10 |


       | 0x06 |
| 0x05 | 0x0D | 0x15 |
       | 0x16 |


| 0x0E |
```

## Pinout and buttons mapping
```
                                 +---==---+
                       PC6 RESET |1     28| PC5  0X0B
                0x16         PD0 |2     27| PC4  0x0A
                             TXD |3     26| PC3  0x09
"50" only (b#2) 0x10         PD2 |4     25| PC2  0x08 <- "48" only (both)
                0x11         PD3 |5     24| PC1  0x0D
                0x12         PD4 |6     23| PC0  0x0C
                             VCC |7     22|
                             GND |8     21|
                0x06         PB6 |9     20|
                0x0E         PB7 |10    19| PB5  0x03
                0x13         PD5 |11    18| PB4  0x02
                0x14         PD6 |12    17| PB3  0x01
                0x15         PD7 |13    16| PB2  0x00 <- fail (b#1)
                0x04         PB0 |14    15| PB1  0x05
                                 +--------+
```
Codes 0x00, 0x08, 0x10 do not work as expected (perhaps, framing errors because of baud rate difference - although there were no problems before).
Will leave these codes out - 1 column is also removed, so it's OK.


## Base USART feature set
* Sends duplicate button key press/release reports via USART @ 38400.


## Register allocation

|    |                                                                 |
|----|-----------------------------------------------------------------|
|  0 | compiler temp                                                   |
|  1 | compiler zero                                                   |
|  2 |                                                                 |
|  3 |                                                                 |
|  4 |                                                                 |
|  5 |                                                                 |
|  6 |                                                                 |
|  7 | KEYBOARD__PORT_B__PREVIOUS_STATE__REG                           |
|  8 | KEYBOARD__PORT_C__PREVIOUS_STATE__REG                           |
|  9 | KEYBOARD__PORT_D__PREVIOUS_STATE__REG                           |
| 10 |                                                                 |
| 11 | KEYBOARD__PORT_B__MASK__REG                                     |
| 12 | KEYBOARD__PORT_C__MASK__REG                                     |
| 13 | KEYBOARD__PORT_D__MASK__REG                                     |
| 14 | KEYBOARD__COMMON_MASK__REG                                      |
| 15 | GP_RING_BUFFER__SIZE__REG                                       |
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
| 26 | GP_RING_BUFFER__PTR__REG (L)                                    |
| 27 | GP_RING_BUFFER__PTR__REG (H)                                    |
| 28 | allocated by compiler                                           |
| 29 | allocated by compiler                                           |
| 30 |                                                                 |
| 31 |                                                                 |


## Programming with arduino bootloader (untested)

```
/opt/arduino-1.8.13/hardware/tools/avr/bin/avrdude -C /opt/arduino-1.8.13/hardware/tools/avr/etc/avrdude.conf -c arduino -patmega88p -U flash:w:main.hex:i -P /dev/ttyUSB0 -b19200
```
