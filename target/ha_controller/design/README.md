#### UI and connections


3 DIN units, 52mm: (!!!)

```
  4x Valve Control Inputs     24V           24V Negative 
  (parellel with buttons)    Power          Water leak sensors
  V V V V                     | |               V V V V
+----------------------------------------------------------------+
| Contactor                    Cold water          Hot water     |
|  Control +          ( )      Control +           Control +     |
|  Status                      Status              Status        |
|   ( ) White                ON (  ) Yellow    OFF (  ) Yellow   |
| LED+button 12mm     ( )    LED+button 12mm   LED+button 12mm   |
|                                                                |
|                                                                |
|                                                                |
|                                                                |
|  Alarm                       Cold water          Hot water     |
|  Status +           ( )      Control +           Control +     |
|  Reset                       Status              Status        |
|   ( ) Red                     (  ) Green         (  ) Green    |
| LED+button 12mm     ( )       OFF                OFF           |
|                                                                |
|                      \__  Water leak sensors status            |
|                           R+G bi-color leds                    |
+----------------------------------------------------------------+
  V V V V                 ^ V                   ^ ^ ^ ^
  4x Valves Control       Contactor Control      4x Valve Status
  (24V open drain)        Contactor Output       (24V negative)
```

* All outputs are open-collector type, 24V compatible
* All inputs are active-low, 24V compatible

* Contactor control (from other controller):
  * Negative pulse (shorted to ground) - toggle
  * Parallelled with button
* Contactor output:
  * Displayed on LED (actual position - unknown, can have external contact)
    * Can DIY external contact?
  * Drives contactor coil: 0V => engaged
  * 24V, high power
  * Protection required (fuse)
  * Coild Diode?
* Valves
  * External control inputs
    * Parallelled with buttons
    * Negative pulse (shorted to ground) - engage (ON/OFF)
  * Control outputs
    * 24V open collector, shorted to ground => engage
  * Operation
    * Valve status displayed on LEDs
    * Short press or low level: engage
      * LED starts blinking slowly for time T
      * If endstop reached, LED remains ON
      * If endstop not reached, bot LEDs blink fast (failure)
    * Long press: lock
      * Same operation, but valve remains "locked" in target position
      * Short presses (button or external input) are ignored
* Water leak sensors
  * Directly connect sensors
  * Protection required (TVS + fuse)
  * Optical?
  * Status displayed with dual-color LEDs
    * 24V measured - no water - GREEN
    * 0V measure - water - RED
  * When engaged, valves are closed
    * Alarm output signalled (configurable)
* Alarm input
* Alarm output
* RS-485 interface
* Serial interface or SIM module
