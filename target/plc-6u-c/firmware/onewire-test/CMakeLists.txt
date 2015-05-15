cmake_minimum_required(VERSION 2.8.4)
project(onewire-test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
    onewire.c
    onewire__bus__inverted_buffer.c
)


include_directories(. ../../bsp ../../../../ ../../../../../../avrgcc/avr/include ../../../../../../avrgcc/lib/gcc/avr/4.8.1/include)
add_executable(onewire-test ${SOURCE_FILES})


add_definitions(-D__AVR_ATmega8535__)
add_definitions(-DMCU=atmega8535)
add_definitions(-DOPT="2 -Wa,-a,-ad")

# System
# ==============================================================================
add_definitions(-DF_CPU=16000000UL)


# Outputs
# ==============================================================================
add_definitions(-DOUT__RTS__PORT=D)
add_definitions(-DOUT__RTS__PIN=7)

# USART
# ==============================================================================
add_definitions(-DUSART0__BAUD_RATE=250000UL)

# 1-Wire
# ==============================================================================
add_definitions(-DONEWIRE__OUT__PORT=D)
add_definitions(-DONEWIRE__OUT__PIN=6)
add_definitions(-DONEWIRE__IN__PORT=D)
add_definitions(-DONEWIRE__IN__PIN=5)

add_definitions(-DONEWIRE__BITBANG_THREAD__IP__REG=26)
add_definitions(-DONEWIRE__BITBANG_THREAD__BIT_COUNT__REG=16)
add_definitions(-DONEWIRE__BITBANG_THREAD__DATA__REG=17)

add_definitions(-DONEWIRE__THREAD__IP__REG=28)

add_definitions(-DONEWIRE__TIMER__FAST_CONF=TIMER2_CONF_PRESCALER_32|TIMER2_CONF_WGM_CTC)
add_definitions(-DONEWIRE__TIMER__SLOW_CONF=TIMER2_CONF_PRESCALER_256|TIMER2_CONF_WGM_CTC)
add_definitions(-DONEWIRE__TIMER__TIME_QUANTUM=4)


# Display
# ==============================================================================
add_definitions(-DDISPLAY_DIGIT0__PORT=A)
add_definitions(-DDISPLAY_DIGIT1__PORT=C)

add_definitions(-DDISPLAY_SEGMENT_A__PIN=2)
add_definitions(-DDISPLAY_SEGMENT_B__PIN=3)
add_definitions(-DDISPLAY_SEGMENT_C__PIN=6)
add_definitions(-DDISPLAY_SEGMENT_D__PIN=5)
add_definitions(-DDISPLAY_SEGMENT_E__PIN=4)
add_definitions(-DDISPLAY_SEGMENT_F__PIN=1)
add_definitions(-DDISPLAY_SEGMENT_G__PIN=0)
add_definitions(-DDISPLAY_SEGMENT_DP__PIN=7)
