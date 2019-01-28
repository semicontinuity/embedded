Roller shutter controller
================================================================================

This device makes possible to control roller shutters via CAN bus,
in addition to direct control with 2 buttons "UP" and "DOWN".


Operating the shutters with buttons
--------------------------------------------------------------------------------
The buttons work simply, as if the controller is not present at all:
When the button is pressed, the shutters move, when released, the movement stops.
The control of the shutters from buttons can be disabled (EEPROM setting).


Remote control of the shutters.
--------------------------------------------------------------------------------
The shutters can be remotely controlled with messages on the CAN bus, to which the controller is attached.
The current firmware uses propriatary CANP protocol.
 

Hardware connections
--------------------------------------------------------------------------------
The device connections are:
- 4 poles to connect the CAN bus with additional power line (5-50V DC).
- 4 poles to connect UP and DOWN push buttons.
- 4 poles to connect mains and roller shutters.


Possible improvements:
--------------------------------------------------------------------------------
- advanced control with buttons - e.g. move shutters to a pre-defined position on short press.
- advanced control with buttons - e.g. fully open/close on two short presses.
- infrared control (IR sensor can be connected to USART header).
- current sensing.
- temperature measurement.
