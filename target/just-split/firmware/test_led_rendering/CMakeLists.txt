cmake_minimum_required(VERSION 3.11)
project(test_led_rendering)

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
