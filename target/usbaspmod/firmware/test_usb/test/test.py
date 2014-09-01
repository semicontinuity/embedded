import os
import sys
import usb.core

dev = usb.core.find(idVendor=0x16c0, idProduct=0x05dc)
if dev is not None:
    print 'Found PowerSwitch device'    
else:
    print 'PowerSwitch device not found'
