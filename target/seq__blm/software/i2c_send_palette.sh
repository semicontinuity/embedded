#!/bin/bash
BUS=$(i2cdetect -l | grep i2c-tiny-usb | cut -f1 | cut -c5-)
ADDRESS=$1
sudo i2ctransfer -y ${BUS} w7@0x${ADDRESS} 0x80 0x00 0x00 0x00 0x10 0x00 0x00
