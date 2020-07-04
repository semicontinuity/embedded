#!/bin/bash
BUS=$1
ADDRESS=$2
sudo i2ctransfer -y ${BUS} r1@0x${ADDRESS}
