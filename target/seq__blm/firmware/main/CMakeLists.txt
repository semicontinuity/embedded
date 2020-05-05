cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/timer0.h
        ../../../../cpu/avr/timer2.c
        ../../../../cpu/avr/timer2.h

        ../../../../cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer__timer0b.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer__timer2a.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer__timer2b.c

        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__physical.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_b.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_c.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_d.c
        ../../../../cpu/avr/services/keyboard/keyboard.c
        ../../../../cpu/avr/services/keyboard/keyboard.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_b__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_b__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__buttons.c
        leds.h
        leds.c
        ../../bsp/drivers/comm/ws2812b.c
        ../../bsp/drivers/comm/ws2812b.h

        comm_keyboard.h
        comm_keyboard_simple.c
        comm_leds.c

        twi_slave__handler.h
        twi_slave__handler.c
        twi_slave__tracer.h

        main.c
        tracer__usart0.c
        services/tracer.h
        __all__.c
        )

include_directories(. ../../bsp ../../../.. /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega88P__)
add_definitions(-DF_CPU=8000000UL)
add_definitions(-DINLINE=)

include(CMakeLists.io.txt)
include(CMakeLists.keyboard.txt)
include(CMakeLists.comm_keyboard_simple.txt)
include(CMakeLists.comm_leds.txt)
include(CMakeLists.leds.txt)
include(CMakeLists.twi.txt)