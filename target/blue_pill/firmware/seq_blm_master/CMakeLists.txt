cmake_minimum_required(VERSION 3.11)
project(seq_blm_master)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        seq_blm_master.ino
        midi_package.h
        midi_handler_blm.h
        serial_midi_receiver_pt.h
        sysex_handler_blm.h
        sysex_handler_blm_arduino.h
        ../../../../../../../../../../opt/arduino-1.8.10/hardware/Arduino_STM32/STM32F1/variants/maple/board.cpp
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
