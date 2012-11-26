Voltage relay
(The device for protection against abnormal mains voltage)
================================================================================

This device monitors the mains voltage,
and if the voltage is outside of the specified range, the load is disconnected.
When the voltage returns back to normal, the load is reconnected back.

See the schematics and board layout in the directory platform/mains-protection.

This work is based on the similar device, described at
http://www.bezkz.su/publ/zashhity_ot_perepadov_naprjazhenija/mikrokontrollery_avr_zashhishhajut_apparaturu_ot_anamalnogo_naprjazhenija/36-1-0-238
The schematics is essentially the same, with the few minor changes:

- The MCU is changed to ATMEGA48
- LED is moved to PD3+PD4 to free up serial port.
- A serial port is connected (not used yet).
- Added buzzer to PC1.

Possible improvements
--------------------------------------------------------------------------------
- Make sure that device works after brown-outs (are ports re-initialized?)
- Add opto-isolated UART and support it in firmware (to control the device via UART)