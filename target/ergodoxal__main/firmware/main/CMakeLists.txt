cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        ../../../../cpu/avr/asm_bit_var.h
        ../../../../cpu/avr/macros.h

        ../../../../cpu/avr/timer1.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer1.c
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h

        ../../../../cpu/avr/drivers/io_matrix/io_matrix__in.h
        ../../bsp/drivers/io_matrix/io_matrix__in.c
        ../../bsp/drivers/io_matrix__out_rows.h
        ../../bsp/drivers/io_matrix__out_columns.h
        io_matrix__scanner__thread.h
        io_matrix__scanner__thread.c

        ../../../../cpu/avr/timer0.h
        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/timer2.h
        ../../../../cpu/avr/timer2.c

        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__a.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__a__timer0a.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__b.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__b__timer0b.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__c.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__c__timer2a.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__d.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__d__timer2b.c


        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__matrix.c

        ../../../../cpu/avr/drivers/keyboard/keyboard__port_a__pins__mapping.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_a.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_b__pins__mapping.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_b.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_c__pins__mapping.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_c.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_d__pins__mapping.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping__port_d.c

        ../../../../cpu/avr/drivers/keyboard/keyboard__port_e__pins__mapping.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_e__pins__mapping.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_f__pins__mapping.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_f__pins__mapping.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_g__pins__mapping.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_g__pins__mapping.c


        ../../../../cpu/avr/services/keyboard/keyboard.h
        ../../../../cpu/avr/services/keyboard/keyboard.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_a.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_b.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_c.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_d.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_e.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_f.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_g.c

        ../../../../cpu/avr/services/keyboard/keyboard__port_a__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_a__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_b__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_b__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__buttons.c

        comm_keyboard.h
        comm_keyboard.c

        comm_inbound.h
        comm_inbound.c

        ../../bsp/drivers/out/led_a.h
        ../../bsp/drivers/out/led_b.h
        ../../bsp/drivers/out/led_c.h
        ../../bsp/drivers/out/led_d.h
        ../../bsp/drivers/out/led_e.h
        ../../bsp/drivers/out/led_f.h
        ../../bsp/drivers/out/led_g.h

        ../../bsp/services/tracer.h
        ../../bsp/services/tracer__nop.c

        main.c
        __all__.c
        ../../../../cpu/avr/asm_bit_var.h)

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)
add_definitions(-DINLINE=)
add_definitions(-DUSART0__BAUD_RATE=38400)

include(CMakeLists.io_matrix__scanner.txt)
include(CMakeLists.io_matrix.txt)
include(CMakeLists.io.txt)
include(CMakeLists.keyboard.txt)
include(CMakeLists.comm_keyboard.txt)
