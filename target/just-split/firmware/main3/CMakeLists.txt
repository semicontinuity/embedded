cmake_minimum_required(VERSION 3.11)
project(main3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        ../../../../cpu/avr/asm.h
        ../../../../cpu/avr/macros.h
        ../../../../cpu/avr/asm_bit_var.h

        ../../../../cpu/avr/timer1.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer1.c

        ../../../../cpu/avr/drivers/io_matrix/io_matrix__in.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h
        ../../bsp/drivers/io_matrix/io_matrix__in.c
        ../../bsp/drivers/io_matrix/io_matrix__out_columns.h
        ../../bsp/drivers/io_matrix/io_matrix__out_rows.h
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

        keyboard_handler.c

        comm_usart_outbound__thread.h
        comm_usart_outbound__thread.c

        comm_usart_inbound__thread.h
        comm_usart_inbound__thread.c

        ../../bsp/services/tracer.h
        ../../bsp/services/tracer__nop.c

        comm_twi__outbound.c
        comm_twi__inbound.c

        twi_slave__handler.h
        twi_slave__handler.c
        twi_slave__handler__callbacks.h

        leds_bar__data.h
        leds_bar__data.c
        leds_bar__wdt.c

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
include(CMakeLists.gp_ring_buffer.txt)
include(CMakeLists.twi_slave_handler.txt)
