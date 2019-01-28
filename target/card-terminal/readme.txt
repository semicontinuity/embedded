Card terminal

Device in development, featuring smartcard or SIM card slot, SPI interface, LCD display, keypad, serial and USB port.

Possible uses:

* CCID-compliant USB card terminal fith keypad and display
* USB HID device
* USB CDC device (USB-to-serial)
* Application host - providing resources to application running on a AVR card (Funcard)
* USB-to-SPI converter
* AVR programmer
* Generic development board


For serial connector, it is possible to use 6-pin or 4-pin FireWire connectors
(small size, hard to attach wrong cable, right number of pins,
crossed pairs in the cable - good for crossing RX/TX, RTS/CTS)

Revision A board is designed for AT90USB162 and SIM card slot.
Due to a small number of pins, peripherals are multiplexed and some glue logic is required.
