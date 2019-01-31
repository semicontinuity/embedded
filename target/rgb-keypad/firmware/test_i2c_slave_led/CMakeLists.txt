cmake_minimum_required(VERSION 3.11)
project(test_i2c_slave_led)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../cpu/avr/twi.h
        ../../bsp/drivers/twi_slave.c
        ../../bsp/drivers/twi_slave.h
        __all__.c
        main.c
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_i2c_slave_led ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=16000000UL)
add_definitions(-DTWI_SLAVE__THREAD__IP__REG=30)
add_definitions(-DFIXED_REGISTERS=-ffixed-r30 -ffixed-r31)
