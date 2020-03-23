cmake_minimum_required(VERSION 3.11)
project(test_encoder_pins_to_usart)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        util/formatter.h
        util/formatter.c
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_encoder_pins_to_usart ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)

add_definitions(-DIN__ENCODER0__A__PORT=D)
add_definitions(-DIN__ENCODER0__A__PIN=6)
add_definitions(-DIN__ENCODER0__B__PORT=D)
add_definitions(-DIN__ENCODER0__B__PIN=5)
add_definitions(-DIN__ENCODER0__SWITCH__PORT=D)
add_definitions(-DIN__ENCODER0__SWITCH__PIN=7)

add_definitions(-DUSART0__BAUD_RATE=4800UL)
