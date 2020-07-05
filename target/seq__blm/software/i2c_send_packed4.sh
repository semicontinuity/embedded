#!/bin/bash
BUS=$(i2cdetect -l | grep i2c-tiny-usb | cut -f1 | cut -c5-)
ADDRESS=$1
BYTE=$2
sudo i2ctransfer -y ${BUS} w1@0x${ADDRESS} 0x${BYTE}
