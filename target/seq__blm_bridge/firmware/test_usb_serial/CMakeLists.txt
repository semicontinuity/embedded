cmake_minimum_required(VERSION 3.11)
project(test_usb_serial)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

add_executable(test_usb_serial
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/variants/maple/variant.h
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/variants/maple/board.cpp
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/cores/maple/boards.h
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/cores/maple/libmaple/gpio_f1.c
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/cores/maple/libmaple/i2c.c
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/cores/maple/libmaple/i2c_f1.c
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/i2c_private.h
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/stm32f1/include/series/gpio.h
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/stm32f1/include/series/i2c.h
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/stm32f1/include/series/stm32.h
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/Wire/utility/WireBase.cpp
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/Wire/utility/WireBase.h
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/Wire/Wire.cpp
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/USBComposite/USBComposite.h
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/USBComposite/USBComposite.cpp
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/USBComposite/USBCompositeSerial.h
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/USBComposite/USBCompositeSerial.cpp
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/USBComposite/USBMIDI.h
        ../../../../../../../../../../opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/USBComposite/USBMIDI.cpp

        test_usb_serial__config.h
        test_usb_serial.ino
)

include_directories(        .
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/include
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/stm32f1/include
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/stm32f1/include/series
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/usb/usb_lib
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/usb/stm32f1
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/cores/maple
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/variants/generic_stm32f103c
        /opt/gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include
        /opt/arduino-1.8.13/libraries/pt-1.4
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/variants/maple
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/EEPROM
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/Wire
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/USBComposite
)


add_definitions(-DDSTM32F10X_MD)
add_definitions(-DMCU_STM32F103CB)
add_definitions(-DLC_INCLUDE="lc-addrlabels.h")
add_definitions(-DDEBUG=0)

add_definitions(-DSERIAL_USB)
add_definitions(-DARDUINO=10813)
add_definitions(-DBOARD_generic_stm32f103c)
add_definitions(-DARDUINO_GENERIC_STM32F103C)
add_definitions(-D__STM32F1__)
add_definitions(-DARDUINO_ARCH_STM32)
add_definitions(-DARDUINO_ARCH_STM32F1)
add_definitions(-DGENERIC_BOOTLOADER)
add_definitions(-DMCU_STM32F103C8)
