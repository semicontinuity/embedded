cmake_minimum_required(VERSION 3.11)
project(test_scanner_i2c_keyboard)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        data.h
        data.c

        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/timer0.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h
        ../../../../cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer__timer0.c
        ../../bsp/drivers/io_matrix__in.c
        ../../bsp/drivers/io_matrix__in.h
        ../../bsp/drivers/io_matrix__out_rows.h
        ../../bsp/drivers/io_matrix__out_columns.h
        io_matrix__scanner__thread.h
        io_matrix__scanner__thread.c

        ../../../../cpu/avr/timer2.c
        ../../../../cpu/avr/timer2.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__timer2.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins.h
        ../../../../cpu/avr/services/keyboard/keyboard.h
        ../../../../cpu/avr/services/keyboard/keyboard.c
        ../../bsp/drivers/keyboard__pins__matrix.c

        ../../../../services/tx_ring_buffer.h
        ../../../../services/tx_ring_buffer.c

        ../../bsp/drivers/out/alarm.h

        comm.h
        comm__switch.c
        I2CSlave.h
        I2CSlave.c
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_scanner_i2c_keyboard ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)
add_definitions(-DINLINE=)

# I/O matrix scanner
add_definitions(-DIO_MATRIX__SCANNER__THREAD__IP__REG=30)
add_definitions(-Dio_matrix__scanner__thread__function=timer0__overflow__interrupt__VECTOR)
add_definitions(-Dio_matrix__scanner__thread__function_attrs="\\"__attribute__\(\(signal\)\)ISR_NAKED\\"")
add_definitions(-Dio_matrix__scanner__thread__function_naked=1)
add_definitions(-Dio_matrix__scanner__thread__yield_with_reti=1)
add_definitions(-DIO_MATRIX__SCANNER__THREAD__TIMER__CONF__INITIALIZED=TIMER0_CONF_DEFAULT)
add_definitions(-DIO_MATRIX__SCANNER__THREAD__TIMER__CONF__STARTED=TIMER0_CONF_NO_PRESCALER)

# I/O matrix
add_definitions(-DIO_MATRIX__IN__PORT=B)
add_definitions(-DIO_MATRIX__IN__ROW0__PIN=0)
add_definitions(-DIO_MATRIX__IN__ROW1__PIN=1)
add_definitions(-DIO_MATRIX__IN__ROW2__PIN=2)
add_definitions(-DIO_MATRIX__IN__ROW3__PIN=3)
add_definitions(-DIO_MATRIX__IN__ROW4__PIN=4)
add_definitions(-DIO_MATRIX__IN__ROW5__PIN=5)

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

add_definitions(-DIO_MATRIX__IN__COLUMN0__STATE__REG=4)
add_definitions(-DIO_MATRIX__IN__COLUMN1__STATE__REG=5)
add_definitions(-DIO_MATRIX__IN__COLUMN2__STATE__REG=6)
add_definitions(-DIO_MATRIX__IN__COLUMN3__STATE__REG=7)

# Keyboard handler
add_definitions(-Dtimer2__overflow__run=keyboard__debounce_timer__expired)
add_definitions(-DTIMER2_OVERFLOW_vect_naked)
add_definitions(-DKEYBOARD__PORT_A__USED=1)
add_definitions(-DKEYBOARD__PORT_B__USED=1)
add_definitions(-DKEYBOARD__PORT_C__USED=1)
add_definitions(-DKEYBOARD__PORT_D__USED=1)
add_definitions(-DKEYBOARD__PORT_A__PREVIOUS_STATE__REG=8)
add_definitions(-DKEYBOARD__PORT_B__PREVIOUS_STATE__REG=9)
add_definitions(-DKEYBOARD__PORT_C__PREVIOUS_STATE__REG=10)
add_definitions(-DKEYBOARD__PORT_D__PREVIOUS_STATE__REG=11)
add_definitions(-DKEYBOARD__PORT_A__MASK__REG=12)
add_definitions(-DKEYBOARD__PORT_B__MASK__REG=13)
add_definitions(-DKEYBOARD__PORT_C__MASK__REG=14)
add_definitions(-DKEYBOARD__PORT_D__MASK__REG=15)
add_definitions(-DKEYBOARD__COMMON_MASK__REG=3)

# Keyboard pins (on logical ports)
add_definitions(-DIN__BUTTON0__PORT=A)
add_definitions(-DIN__BUTTON0__PIN=2)
add_definitions(-DIN__BUTTON1__PORT=A)
add_definitions(-DIN__BUTTON1__PIN=3)
add_definitions(-DIN__BUTTON2__PORT=A)
add_definitions(-DIN__BUTTON2__PIN=4)
add_definitions(-DIN__BUTTON3__PORT=A)
add_definitions(-DIN__BUTTON3__PIN=5)
add_definitions(-DIN__BUTTON4__PORT=B)
add_definitions(-DIN__BUTTON4__PIN=2)
add_definitions(-DIN__BUTTON5__PORT=B)
add_definitions(-DIN__BUTTON5__PIN=3)
add_definitions(-DIN__BUTTON6__PORT=B)
add_definitions(-DIN__BUTTON6__PIN=4)
add_definitions(-DIN__BUTTON7__PORT=B)
add_definitions(-DIN__BUTTON7__PIN=5)
add_definitions(-DIN__BUTTON8__PORT=C)
add_definitions(-DIN__BUTTON8__PIN=2)
add_definitions(-DIN__BUTTON9__PORT=C)
add_definitions(-DIN__BUTTON9__PIN=3)
add_definitions(-DIN__BUTTON10__PORT=C)
add_definitions(-DIN__BUTTON10__PIN=4)
add_definitions(-DIN__BUTTON11__PORT=C)
add_definitions(-DIN__BUTTON11__PIN=5)
add_definitions(-DIN__BUTTON12__PORT=D)
add_definitions(-DIN__BUTTON12__PIN=2)
add_definitions(-DIN__BUTTON13__PORT=D)
add_definitions(-DIN__BUTTON13__PIN=3)
add_definitions(-DIN__BUTTON14__PORT=D)
add_definitions(-DIN__BUTTON14__PIN=4)
add_definitions(-DIN__BUTTON15__PORT=D)
add_definitions(-DIN__BUTTON15__PIN=5)

# TX Ring Buffer
add_definitions(-DTX_RING_BUFFER__ALIGNED=1)
add_definitions(-DTX_RING_BUFFER__SIZE=128)
add_definitions(-DTX_RING_BUFFER__HEAD__REG=26)
add_definitions(-DTX_RING_BUFFER__TAIL__REG=28)
#add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__HOST=PORTD)
#add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__BIT=1)
#add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__IN_BIT_IO_MEM=1)
add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__HOST=GPIOR0)
add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__BIT=0)
add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__IN_BIT_IO_MEM=1)
add_definitions(-DTX_RING_BUFFER__NOT_FULL__HOST=GPIOR0)
add_definitions(-DTX_RING_BUFFER__NOT_FULL__BIT=1)
add_definitions(-DTX_RING_BUFFER__NOT_FULL__IN_BIT_IO_MEM=1)

# I/O
add_definitions(-DOUT__ALARM__PORT=D)
add_definitions(-DOUT__ALARM__PIN=1)

# TWI
add_definitions(-DTWI__SLAVE__ADDRESS=0x20)
