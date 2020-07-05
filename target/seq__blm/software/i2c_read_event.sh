#!/bin/bash
BUS=$(i2cdetect -l | grep i2c-tiny-usb | cut -f1 | cut -c5-)
ADDRESS=$1
sudo i2ctransfer -y ${BUS} r1@0x${ADDRESS}
