"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude.exe" -b 115200 -C "C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf" -p m328p -P \\.\COM3 -c arduino -U flash:w:test_leds.hex:i