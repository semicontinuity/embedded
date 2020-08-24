#!/bin/bash
BUS=$(i2cdetect -l | grep i2c-tiny-usb | cut -f1 | cut -c5-)
ADDRESS=$1
sudo i2ctransfer -y ${BUS} w4@0x${ADDRESS} 0x${2} 0x${3} 0x${4} 0x${5}
