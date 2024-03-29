cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        ../../../../services/gp_ring_buffer.c
        ../../../../services/gp_ring_buffer.h

        ../../../../cpu/avr/asm.h
        ../../../../cpu/avr/macros.h
        ../../../../cpu/avr/asm_bit_var.h

        ../../../../cpu/avr/timer1.h
        ../../../../cpu/avr/timer1.c

        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__timer1.c

        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__physical.c

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

        ../../../../cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer.h

        ../../../../cpu/avr/services/keyboard/keyboard.h
        ../../../../cpu/avr/services/keyboard/keyboard.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_a.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_b.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_c.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_d.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_e.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_f.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_g.c

        ../../../../cpu/avr/services/keyboard/keyboard__port_b__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_b__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_c__buttons.c
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__buttons.h
        ../../../../cpu/avr/services/keyboard/keyboard__port_d__buttons.c

        keyboard_handler.c

        comm_usart_outbound__thread.h
        comm_usart_outbound__thread.c

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

include(CMakeLists.io.txt)
include(CMakeLists.keyboard.txt)
include(CMakeLists.gp_ring_buffer.txt)
