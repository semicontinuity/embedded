cmake_minimum_required(VERSION 3.11)
project(seq_blm_master)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        blm_boards__comm.h
        blm_boards__comm__arduino_i2c.h
        leds__updater.h
        leds__buffer.h
        leds__updater__buffer.h
        leds__buffer__scanner.h
        leds__buffer__scanner__callbacks.h
        blm_boards__comm__debug_arduino_serial_midi.h

        debug__arduino_serial_midi.h

        blm_master__channel_msg_handler.h
        midi_package.h
        midi_parser.h
        midi_parser__pt.h
        midi_parser__callbacks__sysex_msg.h
        midi_parser__callbacks__channel_msg.h

        midi_receiver__serial_arduino_pt.h
        midi_sender.h
        midi_sender__serial_arduino.h

        blm_master__sysex_msg_handler.h
        blm_master__sysex_msg_handler__arduino_serial_midi.h

        seq_blm_master.ino
        ../../../../../../../../../../opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/cores/maple/libmaple/i2c.c
        ../../../../../../../../../../opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/cores/maple/libmaple/i2c_f1.c
        ../../../../../../../../../../opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/variants/maple/board.cpp
        ../../../../../../../../../../opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/libraries/Wire/utility/WireBase.cpp
        ../../../../../../../../../../opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/libraries/Wire/utility/WireBase.h
        ../../../../../../../../../../opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/libraries/Wire/Wire.cpp
        )

include_directories(
        .
        /opt/gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include
        /opt/arduino-1.8.10/libraries/pt-1.4
        /opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/variants/maple
        /opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/cores/maple
        /opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/system/libmaple/include
        /opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/system/libmaple/usb/usb_lib
        /opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/system/libmaple/usb/stm32f1
        /opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/libraries/EEPROM
        /opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/libraries/Wire
)

add_executable(${SOURCE_FILES})

add_definitions(-DDSTM32F10X_MD)
add_definitions(-DMCU_STM32F103CB)
add_definitions(-DLC_INCLUDE="lc-addrlabels.h")
add_definitions(-DBLM_SCALAR_NUM_COLOURS=2)
