import sys
import serial
import time
from threading import Thread


ser = serial.Serial('COM9', 9600)

calibrate_zero_request=bytearray([0xFF, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78])
ser.write(calibrate_zero_request)
