cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../cpu/avr/timer1.c
        ../../../../cpu/avr/timer1.h

        twi_slave__handler.h
        twi_slave__handler.c
        twi_slave__tracer.h

        main.c
        tracer__nop.c
        services/tracer.h
        __all__.c
        )

include_directories(. ../../bsp ../../../.. /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega88P__)
add_definitions(-DF_CPU=8000000UL)
add_definitions(-DINLINE=)

include(CMakeLists.twi.txt)