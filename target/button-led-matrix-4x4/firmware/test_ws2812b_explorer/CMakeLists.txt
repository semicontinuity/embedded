cmake_minimum_required(VERSION 3.11)
project(test_ws2812b_explorer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../bsp/drivers/comm/ws2812b.h
        ../../bsp/drivers/comm/ws2812b.c
        services/ws2812b_renderer.c
        services/ws2812b_renderer.h
        services/console_ws2812b.c
        services/console_ws2812b.h
        services/console.h
        services/console.c
        services/console__in.h
        services/console__in__polled.c
        util/formatter.h
        util/formatter.c
        util/parser.h
        util/parser.c
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_ws2812b_explorer ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)

add_definitions(-DUSART0__BAUD_RATE=38400UL)
