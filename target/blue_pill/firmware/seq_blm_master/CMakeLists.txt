cmake_minimum_required(VERSION 3.11)
project(seq_blm_bridge)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

add_executable(seq_blm_bridge
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

        seq_blm_bridge__config.h
        seq_blm_bridge.ino

        midi_package.h

        blm_boards__comm__events__reader.h
        blm_boards__comm__events__handler.h
        blm_boards__comm__events__handler__midi.h
        blm_boards__comm__events__handler__test_mode.h
        blm_boards__comm__events__reader__arduino_i2c.h

        blm_boards__comm__leds__p4_commands__buffer.h
        host__leds_msg_handler__p4.h
        blm_boards__comm__leds__p4_commands__buffer__scanner.h
        blm_boards__comm__leds__p4_commands__buffer__scanner__callbacks.h
        blm_boards__comm__leds__p4_commands__arduino_i2c.h
        blm_boards__comm__leds__p4_commands__debug__arduino_serial_midi.h

        blm_boards__comm__leds__u128_commands__buffer.h
        host__leds_msg_handler__u128.h
        blm_boards__comm__leds__u128_commands__buffer__scanner.h
        blm_boards__comm__leds__u128_commands__buffer__scanner__callbacks.h
        blm_boards__comm__leds__u128_commands__arduino_i2c.h

        blm_boards__comm__leds__palette__buffer.h
        blm_boards__comm__leds__palette__uploader.h

        debug__midi_sysex.h
        debug__midi_sysex__parameters.h

        midi_parser.h
        midi_parser.h
        midi_parser__callbacks__sysex_msg.h
        midi_parser__callbacks__channel_msg.h

        midi_receiver__arduino_serial.h
        midi_sender.h
        midi_sender__arduino_serial.h
        midi_sender__arduino_usb_midi.h

        host__leds_msg.h
        host__channel_msg_handler.h
        host__alive_handler.h
        host__sysex_msg_handler.h
        host__sysex_msg_handler__callbacks.h
        host__sysex_msg_sender.h
        arduino_serial__reader.h)

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
