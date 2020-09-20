cmake_minimum_required(VERSION 3.11)
project(main_avr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        midi_package.h
        midi_sender__arduino_serial.h
        midi_sender.h
        main_avr.ino
        )

include_directories(. /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include /opt/arduino-1.8.13/libraries/pt-1.4 ../../../../../../../../.arduino15/packages/arduino/hardware/megaavr/1.8.6/cores/arduino/)
add_executable(main_avr ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega328P__)
add_definitions(-DF_CPU=16000000UL)

add_definitions(-DLC_INCLUDE="lc-addrlabels.h")
add_definitions(-DDEBUG=0)

set_target_properties(main_avr PROPERTIES LINKER_LANGUAGE CXX)