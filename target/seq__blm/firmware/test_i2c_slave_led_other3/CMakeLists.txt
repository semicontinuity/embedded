cmake_minimum_required(VERSION 3.11)
project(test_i2c_slave_led_other3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../bsp/drivers/out/led1.h
        I2CSlave.c
        I2CSlave.h
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../.. /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_i2c_slave_led_other3 ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega328P__)
add_definitions(-DF_CPU=16000000UL)
add_definitions(-DWS2812B__PORT=D)
add_definitions(-DWS2812B__PIN=1)
