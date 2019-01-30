cmake_minimum_required(VERSION 2.8.4)
project(test_i2c_slave_led)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
)


include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_i2c_slave_led ${SOURCE_FILES})


add_definitions(-D__AVR_ATmega48__)
add_definitions(-DMCU=atmega48)

# System
# ==============================================================================
add_definitions(-DF_CPU=16000000UL)
