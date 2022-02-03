Working spin-off of main firmware.

* Commented out WDT (not sure)
* Increased matrix scanning multiplier to 16
* Increased debouncing timer value to 127 (~16ms)

Seems to work, altough there was 1 fantom keypress in the (row-2) neighboring HW row per ~5000 key presses.

* Noise immunity issue? HW rows are left floating, perhaps, add pull-ups?
* Add capacitor to power supply wires?
