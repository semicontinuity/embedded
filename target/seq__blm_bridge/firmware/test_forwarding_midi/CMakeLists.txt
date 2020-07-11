cmake_minimum_required(VERSION 3.11)
project(test_forwarding_midi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

add_executable(test_forwarding_midi
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

        test_forwarding_midi__config.h
        test_forwarding_midi.ino

        midi_package.h

        midi_parser.h
        midi_sender.h
        midi_sender__arduino_usb_midi.h

        host__sysex_msg_handler.h
        host__sysex_msg_handler__callbacks.h
        host__sysex_msg_sender.h

        arduino_serial__reader.h
        midi_sender__arduino_serial.h
        )

include_directories(
        .
        /opt/gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include
        /opt/arduino-1.8.13/libraries/pt-1.4
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/variants/maple
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/cores/maple
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/include
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/stm32f1/include/series
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/usb/usb_lib
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/system/libmaple/usb/stm32f1
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/EEPROM
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/Wire
        /opt/arduino-1.8.13/hardware/Arduino_STM32-1.0.0/STM32F1/libraries/USBComposite
)


add_definitions(-DDSTM32F10X_MD)
add_definitions(-DMCU_STM32F103CB)
add_definitions(-DLC_INCLUDE="lc-addrlabels.h")
add_definitions(-DDEBUG=0)
