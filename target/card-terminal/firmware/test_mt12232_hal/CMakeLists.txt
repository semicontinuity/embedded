cmake_minimum_required(VERSION 3.11)
project(test_mt12232_hal)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        main.c
        __all__.c
        ../../../../cpu/avr/drivers/display/mt12232_hal/lcd_graphics.c
        ../../../../cpu/avr/drivers/display/mt12232_hal/lcd_graphics.h
        ../../../../cpu/avr/drivers/display/mt12232_hal/mt12232_hal.h
        ../../../../cpu/avr/drivers/display/mt12232_hal/mt12232_hal.c
        ../../../../cpu/avr/drivers/display/mt12232_hal/mt12232_hal.h
        ../../../../cpu/avr/drivers/display/mt12232/lcd_graph_lib.c
        ../../../../cpu/avr/drivers/display/mt12232/lcd_graph_lib.h
        ../../../../cpu/avr/drivers/display/mt12232/bits_macros.h
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include ../../../../cpu/avr/drivers/display/mt12232 ../../../../cpu/avr/drivers/display/mt12232_hal)
add_executable(test_mt12232_hal ${SOURCE_FILES})

add_definitions(-D__AVR_AT90USB162__)
add_definitions(-DF_CPU=16000000UL)

add_definitions(-DMT12232__CS__PORT=D)
add_definitions(-DMT12232__CS__PIN=1)
