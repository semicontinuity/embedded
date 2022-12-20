1. nRF52840 power supply
* Has internal LDO, DC-DC.
* By default the LDO regulators are enabled, and you do not need to configure it.
* DC/DC regulator is not enabled in firmware - need LC filter.

* The voltage mode is automatically detected based on where the supply voltage is connected.
* if it is connected to both VDDH and VDD the system enters normal voltage mode.
* if only VDDH is connected the system enters high voltage mode.
* VDD and VDDH are shortcircuited inside the QFN48 package. Therefore the QFN48 device is only usable in Normal Voltage supply mode, and not High Voltage supply mode.
* The output of the REG0 regulator stage is configured in the UICR, https://infocenter.nordicsemi.com/topic/ps_nrf52840/uicr.html?cp=4_0_0_3_4_0_7#register.REGOUT0
* VDD max = 3.6V
* Ref circ: https://infocenter.nordicsemi.com/index.jsp?topic=%2Fps_nrf52840%2Fref_circuitry.html

2. HolyIOT 18010
* MAY have inductors
* Presumed schematics: https://devzone.nordicsemi.com/f/nordic-q-a/59622/feed-line
* Обязательно используйте nrfvdd для программирования вместо vbus, иначе у вас есть шанс обжарить модуль, так как я использовал 3v3, но по умолчанию это 1v8 при использовании vbus.
* (https://github.com/joric/nrfmicro/wiki/Alternatives)
* Note that Holyot already has the DC-DC inductivity soldered in so you don't need 3V LDO to run MCU from internal DC-DC.
* "it does not support HV-mode, so you'll need a external voltage regulator." ???

* https://devzone.nordicsemi.com/f/nordic-q-a/71791/running-zephyr-on-holyiot-nrf52840-does-not-work-solved
* https://github.com/Ladniy/jiran-ble-lite

3. Flashing
* https://crtv-club.readthedocs.io/ru/latest/nrf52_stlink_flashing.html
* ? https://devzone.nordicsemi.com/f/nordic-q-a/69423/nrf52840-and-st-link-v2
* https://pcbreflux.blogspot.com/2016/09/nrf52832-first-steps-with-st-link-v2.html
* https://github.com/blackmagic-debug/blackmagic/issues/381
* "ST-LINK/V2 needs CMSIS-DAP patch or Blackmagic firmware"
