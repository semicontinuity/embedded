#!/bin/bash
BUS=$1
ADDRESS=$2
BYTE=$3
sudo i2ctransfer -y ${BUS} w1@0x${ADDRESS} 0x${BYTE}
