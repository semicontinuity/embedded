#!/bin/bash
BUS=$(i2cdetect -l | grep i2c-tiny-usb | cut -f1 | cut -c5-)
ADDRESS=$1
LED=$2 # 0-f
sudo i2ctransfer -y ${BUS} w4@0x${ADDRESS} 0x1${LED} 0x02 0x02 0x02 
