#!/bin/bash
ADDRESS=$1
[[ -z $ADDRESS ]] && echo "Argument: I2C address (hex)" >&2 && exit 1
BUS=$(i2cdetect -l | grep i2c-tiny-usb | cut -f1 | cut -c5-)
[[ -z $BUS ]] && echo "i2c-tiny-usb not detected" >&2 && exit 1

while true ; do
  EVENT=$(sudo i2ctransfer -y ${BUS} r1@0x${ADDRESS})
  [[ -z $LOOP ]] && echo $EVENT && break
  [[ $EVENT != "0x00" ]] && echo $EVENT
done
