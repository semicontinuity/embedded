cmake_minimum_required(VERSION 3.11)
project(test_read_all_rows__state_update)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        ../../../../cpu/avr/macros.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__in.h
        ../../bsp/drivers/io_matrix/io_matrix__in.c
        ../../bsp/drivers/io_matrix__out_columns.h
        ../../bsp/drivers/io_matrix__out_rows.h

        main.c
        __all__.c
        ../../../../cpu/avr/asm_bit_var.h)

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)
add_definitions(-DINLINE=)
add_definitions(-DUSART0__BAUD_RATE=38400)

include(CMakeLists.io_matrix.txt)
include(CMakeLists.io_matrix__scanner.txt)
