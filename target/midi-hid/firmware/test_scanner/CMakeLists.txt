cmake_minimum_required(VERSION 3.11)
project(test_scanner)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../bsp/drivers/out/leds_rows.h
        ../../bsp/drivers/out/columns.h
        ../../bsp/services/scanner.c
        ../../bsp/services/scanner.h
        ../../bsp/services/scanner__rgb_leds.h
        ../../bsp/services/scanner__rgb_leds__buffered.c
        ../../bsp/drivers/scanner__thread__timer.c
        ../../bsp/drivers/scanner__thread__timer.h
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_scanner ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega328P__)
add_definitions(-DF_CPU=16000000UL)
#add_definitions(-DTWI__SLAVE__THREAD__IP__REG=30)
#add_definitions(-DFIXED_REGISTERS=-ffixed-r30 -ffixed-r31)


add_definitions(-DOUT__COLUMN0__PORT=C)
add_definitions(-DOUT__COLUMN0__PIN=0)
add_definitions(-DOUT__COLUMN1__PORT=C)
add_definitions(-DOUT__COLUMN1__PIN=1)
add_definitions(-DOUT__COLUMN2__PORT=C)
add_definitions(-DOUT__COLUMN2__PIN=2)
add_definitions(-DOUT__COLUMN3__PORT=C)
add_definitions(-DOUT__COLUMN3__PIN=3)

add_definitions(-DOUT__LED1R_ROW__PORT=D)
add_definitions(-DOUT__LED1R_ROW__PIN=2)
add_definitions(-DOUT__LED1G_ROW__PORT=D)
add_definitions(-DOUT__LED1G_ROW__PIN=3)
add_definitions(-DOUT__LED1B_ROW__PORT=D)
add_definitions(-DOUT__LED1B_ROW__PIN=4)

add_definitions(-DOUT__LED2R_ROW__PORT=D)
add_definitions(-DOUT__LED2R_ROW__PIN=5)
add_definitions(-DOUT__LED2G_ROW__PORT=D)
add_definitions(-DOUT__LED2G_ROW__PIN=6)
add_definitions(-DOUT__LED2B_ROW__PORT=D)
add_definitions(-DOUT__LED2B_ROW__PIN=7)

add_definitions(-DOUT__BUTTONS_LEDS_ROW__PORT=D)
add_definitions(-DOUT__BUTTONS_LEDS_ROW__PIN=0)

add_definitions(-Dtimer0__overflow__run=scanner__thread__run)
add_definitions(-DSCANNER__THREAD__IP__REG=30)
add_definitions(-DSCANNER__RGB_LEDS__DATA_PTR__REG=28)
