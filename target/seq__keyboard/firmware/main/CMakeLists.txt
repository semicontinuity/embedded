cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        ../../../../cpu/avr/timer1.h
        ../../../../cpu/avr/timer1.c
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer1.c

        ../../../../cpu/avr/timer0.h
        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__in.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__in.c
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer0.c
        ../../bsp/drivers/io_matrix__out_rows.h
        ../../bsp/drivers/io_matrix__out_columns.h
        io_matrix__scanner__thread.h
        io_matrix__scanner__thread.c

        ../../../../cpu/avr/timer2.h
        ../../../../cpu/avr/timer2.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__matrix.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_a.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_b.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_c.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_d.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__timer2.c
        ../../../../cpu/avr/services/keyboard/keyboard.h
        ../../../../cpu/avr/services/keyboard/keyboard.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_a__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_a__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_b__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_b__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__buttons.c

        ../../../../cpu/avr/services/keyboard/keyboard__port_a__encoders.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_a__encoders.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_b__encoders.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_b__encoders.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__encoders.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__encoders.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__encoders.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__encoders.c

        ../../../../cpu/avr/twi.h
        twi_slave__handler.h
        twi_slave__handler.c
        comm_leds.c
        comm_keyboard.h
        comm_keyboard_simple.c

        ../../bsp/drivers/out/led_a.h
        ../../bsp/drivers/out/led_b.h

        data.c
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)

include(CMakeLists.data.txt)
include(CMakeLists.io_matrix__scanner.txt)
include(CMakeLists.io_matrix.txt)
include(CMakeLists.io.txt)
include(CMakeLists.keyboard.txt)
include(CMakeLists.comm_keyboard_simple.txt)
include(CMakeLists.twi.txt)