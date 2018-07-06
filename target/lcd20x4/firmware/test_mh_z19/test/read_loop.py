import sys
import serial
import time
from threading import Thread


ser = serial.Serial('COM9', 9600)

if False:
    calibrate_zero_request=bytearray([0xFF, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78])
    ser.write(calibrate_zero_request)
    time.sleep(12)


read_request=bytearray([0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79])
while 1:
    ser.write(read_request)
    data = ser.read(9)
    print ord(data[2])*256 + ord(data[3]), ord(data[4])-40
    time.sleep(12)
