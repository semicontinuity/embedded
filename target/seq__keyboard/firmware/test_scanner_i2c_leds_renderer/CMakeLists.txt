cmake_minimum_required(VERSION 3.11)
project(test_scanner_i2c_leds_renderer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/timer0.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer0.c
        ../../bsp/drivers/io_matrix__out_rows.h
        ../../bsp/drivers/io_matrix__out_columns.h
        io_matrix__scanner__thread.h
        io_matrix__scanner__thread.c

        ../../../../cpu/avr/twi.h
        twi_slave__handler.h
        twi_slave__handler.c

        ../../bsp/drivers/out/led_a.h
        ../../bsp/drivers/out/led_b.h

        data.c
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_scanner_i2c_leds_renderer ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)

# Data
add_definitions(-DDATA__LEDS__INDEX__REG=2)

# I/O matrix scanner
add_definitions(-DIO_MATRIX__SCANNER__THREAD__IP__REG=30)
add_definitions(-Dio_matrix__scanner__thread__function=timer0__overflow__interrupt__VECTOR)
add_definitions(-Dio_matrix__scanner__thread__function_attrs="\\"__attribute__\(\(signal\)\)ISR_NAKED\\"")
add_definitions(-Dio_matrix__scanner__thread__function_naked=1)
add_definitions(-Dio_matrix__scanner__thread__yield_with_reti=1)
add_definitions(-DIO_MATRIX__SCANNER__THREAD__TIMER__CONF__INITIALIZED=TIMER0_CONF_DEFAULT)
add_definitions(-DIO_MATRIX__SCANNER__THREAD__TIMER__CONF__STARTED=TIMER0_CONF_NO_PRESCALER)

# I/O matrix
add_definitions(-DIO_MATRIX__OUT__ROWS__PORT=D)
add_definitions(-DIO_MATRIX__OUT__LED1R_ROW__PORT=IO_MATRIX__OUT__ROWS__PORT)
add_definitions(-DIO_MATRIX__OUT__LED1R_ROW__PIN=2)
add_definitions(-DIO_MATRIX__OUT__LED1G_ROW__PORT=IO_MATRIX__OUT__ROWS__PORT)
add_definitions(-DIO_MATRIX__OUT__LED1G_ROW__PIN=3)
add_definitions(-DIO_MATRIX__OUT__LED1B_ROW__PORT=IO_MATRIX__OUT__ROWS__PORT)
add_definitions(-DIO_MATRIX__OUT__LED1B_ROW__PIN=4)
add_definitions(-DIO_MATRIX__OUT__LED2R_ROW__PORT=IO_MATRIX__OUT__ROWS__PORT)
add_definitions(-DIO_MATRIX__OUT__LED2R_ROW__PIN=5)
add_definitions(-DIO_MATRIX__OUT__LED2G_ROW__PORT=IO_MATRIX__OUT__ROWS__PORT)
add_definitions(-DIO_MATRIX__OUT__LED2G_ROW__PIN=6)
add_definitions(-DIO_MATRIX__OUT__LED2B_ROW__PORT=IO_MATRIX__OUT__ROWS__PORT)
add_definitions(-DIO_MATRIX__OUT__LED2B_ROW__PIN=7)
add_definitions(-DIO_MATRIX__OUT__BUTTONS_LEDS_ROW__PORT=IO_MATRIX__OUT__ROWS__PORT)
add_definitions(-DIO_MATRIX__OUT__BUTTONS_LEDS_ROW__PIN=0)

add_definitions(-DIO_MATRIX__OUT__COLUMNS__PORT=C)
add_definitions(-DIO_MATRIX__OUT__COLUMN0__PORT=IO_MATRIX__OUT__COLUMNS__PORT)
add_definitions(-DIO_MATRIX__OUT__COLUMN0__PIN=0)
add_definitions(-DIO_MATRIX__OUT__COLUMN1__PORT=IO_MATRIX__OUT__COLUMNS__PORT)
add_definitions(-DIO_MATRIX__OUT__COLUMN1__PIN=1)
add_definitions(-DIO_MATRIX__OUT__COLUMN2__PORT=IO_MATRIX__OUT__COLUMNS__PORT)
add_definitions(-DIO_MATRIX__OUT__COLUMN2__PIN=2)
add_definitions(-DIO_MATRIX__OUT__COLUMN3__PORT=IO_MATRIX__OUT__COLUMNS__PORT)
add_definitions(-DIO_MATRIX__OUT__COLUMN3__PIN=3)

add_definitions(-DOUT__LED_A__PORT=B)
add_definitions(-DOUT__LED_A__PIN=6)
add_definitions(-DOUT__LED_B__PORT=B)
add_definitions(-DOUT__LED_B__PIN=7)

add_definitions(-DTWI__SLAVE__ADDRESS=0x20)
