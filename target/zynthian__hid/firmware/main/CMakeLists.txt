cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        ../../bsp/drivers/in/encoder__step.h
        ../../bsp/drivers/in/encoder__step.c
        ../../bsp/drivers/in/encoder0.h
        ../../bsp/drivers/in/encoder0.c
        ../../bsp/drivers/in/encoder0__switch.h
        ../../bsp/drivers/in/encoder0__switch.c

        ../../../../cpu/avr/drivers/keyboard/keyboard__port_a__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_a__debounce_timer__timer0a__flag.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer__timer0b__flag.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer__timer2a__flag.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer__timer2b__flag.c

        ../../../../cpu/avr/twi.h
        twi_slave__handler.h
        twi_slave__handler.c
        comm_events_simple.c
        comm_buttons.h
        comm_buttons_queues.c
        comm_encoder.h
        comm_encoder_queues.c

        ../../bsp/drivers/out/led_a.h
        ../../bsp/drivers/out/led_b.h
        ../../bsp/drivers/out/alarm.h

        main.c
        __all__.c
        )


include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)

include(CMakeLists.io.txt)
include(CMakeLists.encoders.txt)
include(CMakeLists.encoders_switches.txt)
include(CMakeLists.comm_buttons_queues.txt)
include(CMakeLists.comm_encoder_queues.txt)
include(CMakeLists.comm_events_simple.txt)
include(CMakeLists.twi.txt)