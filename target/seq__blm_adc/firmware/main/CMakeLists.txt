cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

add_executable(main
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/DEMO_F030F4/variant.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/Arduino.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/HardwareSerial.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/HardwareSerial.cpp
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32/PinConfigured.h
        midi_package.h
        midi_sender__arduino_serial.h
        main.ino

        midi_sender.h)

include_directories(
        .
        ../../../../../../../../arduino/packages/STM32/hardware/stm32/1.9.0/cores/arduino
        ../../../../../../../../arduino/packages/STM32/hardware/stm32/1.9.0/variants/DEMO_F030F4
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32

        /opt/gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include
        /opt/arduino-1.8.13/libraries/pt-1.4
)

add_definitions(-DLC_INCLUDE="lc-addrlabels.h")
add_definitions(-DDEBUG=0)

set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)
