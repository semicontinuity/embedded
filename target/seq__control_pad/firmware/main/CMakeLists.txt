cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        ../../../../cpu/avr/timer1.c
        ../../../../cpu/avr/timer1.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer1.c
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__in.c
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__in.h
        io_matrix__scanner__thread.c
        io_matrix__scanner__thread.h
        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/timer2.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__matrix.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_a.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_b.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_c.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_d.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_a__debounce_timer__timer0a.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer__timer0b.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer__timer2a.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer__timer2b.c
        ../../../../cpu/avr/services/keyboard/keyboard.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_a__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_b__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__buttons.c

        ../../bsp/drivers/in/encoder0.h
        ../../bsp/drivers/in/encoder0.c
        ../../bsp/drivers/in/encoder0__switch.h
        ../../bsp/drivers/in/encoder0__switch.c
        ../../bsp/drivers/in/encoder__step.h
        ../../bsp/drivers/in/encoder__step.c

        ../../../../cpu/avr/twi.h
        twi_slave__handler.h
        twi_slave__handler.c
        comm_events_simple.c
        comm_leds.c
        comm_keyboard_simple.c
        comm_keyboard.h
        comm_encoder.c

        ../../bsp/drivers/out/led_a.h
        ../../bsp/drivers/out/led_b.h
        ../../bsp/drivers/out/alarm.h

        data.c
        ../../bsp/services/tracer__nop.c
        ../../bsp/services/tracer.h
        main.c
        __all__.c
        )


include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega88P__)
add_definitions(-DF_CPU=8000000UL)

include(CMakeLists.data.txt)
include(CMakeLists.io_matrix__scanner.txt)
include(CMakeLists.io_matrix.txt)
include(CMakeLists.io.txt)
include(CMakeLists.encoder.txt)
include(CMakeLists.keyboard.txt)
include(CMakeLists.comm_events_simple.txt)
include(CMakeLists.comm_encoder.txt)
include(CMakeLists.twi.txt)