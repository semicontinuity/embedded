#!/bin/bash
while true; do
  EVENT=$(./i2c_read_event.sh 08)
  [[ $EVENT != 0x00 ]] && echo ${EVENT}
done