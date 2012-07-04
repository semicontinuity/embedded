Card terminal

A future device, featuturing smartcard slot, 1x or 2x SDIO slots, LCD display, keypad, serial and USB port.

Possible uses:

* CCID-compliant USB card terminal
* USB HID device
* USB CDC device (USB-to-serial)
* Application host - providing resources to application running on a AVR card
* USB-to-SPI converter


Case: white plastic, about 100x80x20



Board design:

Size: about 76x96


for serial connector, it is possible to use 6-pin or 4-pin FireWire connectors
(small size, hard to attach wrong cable, right number of pins,
crossed pairs in the cable - good for crossing RX/TX, RTS/CTS)

 serial connector       mini-usb connector 
 V                      V
 +-----------------------+
 |                       |
 |      MT12232A         |
 |                       |
 +-----------------------+
 |                       |
 +-------+       +-------+
 |       |       |       |
 | SD    |       | SD    |
 +-------+-------+-------+
 |                       |
 |                       |
 |                       |
 | smart card slot       |
 |                       |
 |                       |
 |                       |
 +-----------------------+

microprocessors:

AT90USB162: small number of pins (if want to use serial and SPI)
AT83xxx355: ?