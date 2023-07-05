#### UI and connections


4 DIN units

```
+----------------------------------------------------------------+
|  Contactor        RG LED     Cold water          Hot water     |
|  Status           Sensor A   Control +           Control +     |
|  + Control                   Status              Status        |
|  ( ) White        RG LED     ON (  ) Yellow    OFF (  ) Yellow |
|  LED+button 12mm  Sensor B   LED+button 12mm   LED+button 12mm |
|                                                                |
|                                                                |
|                                                                |
|                                                                |
|  Alarm            RG LED     Cold water          Hot water     |
|  Status +         Sensor C   Control +           Control +     |
|  Control                       Status              Status      |
|  ( ) Red          RG LED     (  ) Green         (  ) Green     |
|  LED+button 12mm  Sensor D   OFF                OFF            |
+----------------------------------------------------------------+
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



#### Parts
[Buttons drawing](https://www.google.com/imgres?imgurl=https%3A%2F%2Fstore.nerokas.co.ke%2Fimage%2Fcatalog%2FLed%2Ftactile%2520push%2520putton%2520with%2520led.jpg&tbnid=CuapTxC5KNGawM&vet=12ahUKEwiR5PXSj5P_AhXIE3cKHStmBrQQMygjegUIARCbAg..i&imgrefurl=https%3A%2F%2Fstore.nerokas.co.ke%2Findex.php%3Froute%3Dproduct%2Fproduct%26product_id%3D1356&docid=ClL0ARckmi5yWM&w=607&h=602&q=push%20button%20with%20led%2012%20mm%20dimensions&ved=2ahUKEwiR5PXSj5P_AhXIE3cKHStmBrQQMygjegUIARCbAg)


#### MCU pin assignment (ATMega16)

* Valve control inputs:         4x (physically connected with 4x buttons)
* Valve control outputs:        4x

* Valve status inputs:          4x
* Water leak sensors:           4x (physically connected with 4x LEDs)

* Valve status LEDs in buttons: 4x
* LEDs in 2 extra buttons:      2x
* 2 extra buttons               2x

* 2 extra inputs		2x (contactor state in + alarm in)
* 2 extra outputs               2x (contactor out + alarm out) 
* I2C                           2x
* RS485 / Serial                2x


#### Pin assignment - layout

Layer 1
```
  Valve state               Valve control in        Extra input
    V V V V                    V V V V                V V 
+----------------------------------------------------------------+
|                                                                | 
|                                                                |
|                                                                |
|                                                                |
|                                                                |
|                                                                |
| [Valve state in][Leak sensors]     [Valve ctrl in][AUX in][I2C]|
|                                                                |
|                                                                |
| [AUX led + btn][Valves out]        [RXTX][Valve LEDs][AUX out] |
|                                                                |
|                                                                |
|                                                                | 
|                                                                |
|                                                                |
|                                                                |
+----------------------------------------------------------------+
  V V V V                 |  |           |   |            |  |
  4x Valves Control                               
  (24V open drain)       24V (coils)   RS-485           Extra out

```


Layer 2
```
                  Water leak sensors + power out
                    V V         V V V V         V V
+----------------------------------------------------------------+
|                                                                | 
|                                                                |
|                                                                |
|                                                                |
|                                                                |
|                                                                |
|                                                                |
|                                                                |
|                                                                |
|                                                                |
|                                                                |
|                                                                |
+----------------------------------------------------------------+
                                | |
                               5V supply

```


#### Schematics ideas
* [KC868-E16T](https://habr.com/ru/companies/timeweb/articles/736428/)
