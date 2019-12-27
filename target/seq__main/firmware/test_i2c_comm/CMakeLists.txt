cmake_minimum_required(VERSION 3.11)
project(test_i2c_comm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        src/analog_inputs.c
        src/analog_inputs.h
        src/app.c
        src/app.h
        src/button_event.h
        src/encoders.c
        src/encoders.h
        src/i2c.c
        src/i2c.h
        src/i2c_config.h
        src/midi_output_config.h
        src/mios32_config.h
        src/rgb_matrix.c
        src/rgb_matrix.h

        ../../../../../../../svnmios.midibox.org/trunk/programming_models/traditional/startup_stm32f4xx.c

        ../../../../../../../svnmios.midibox.org/trunk/programming_models/traditional/main.c
        ../../../../../../../svnmios.midibox.org/trunk/programming_models/traditional/strtol.c
        ../../../../../../../svnmios.midibox.org/trunk/FreeRTOS/Source/tasks.c
        ../../../../../../../svnmios.midibox.org/trunk/FreeRTOS/Source/list.c
        ../../../../../../../svnmios.midibox.org/trunk/FreeRTOS/Source/queue.c
        ../../../../../../../svnmios.midibox.org/trunk/FreeRTOS/Source/timers.c
        ../../../../../../../svnmios.midibox.org/trunk/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
        ../../../../../../../svnmios.midibox.org/trunk/FreeRTOS/Source/portable/MemMang/heap_4.c
        )


include_directories(
        src
        /opt/gcc-arm-none-eabi-8-2018-q4-major/arm-none-eabi/include
        ../../../../../../../svnmios.midibox.org/trunk/include/mios32
        ../../../../../../../svnmios.midibox.org/trunk/programming_models/traditional
        ../../../../../../../svnmios.midibox.org/trunk/FreeRTOS/Source/include
        ../../../../../../../svnmios.midibox.org/trunk/FreeRTOS/Source/portable/GCC/ARM_CM3
        ../../../../../../../svnmios.midibox.org/trunk/FreeRTOS/Source/portable/MemMang
        ../../../../../../../svnmios.midibox.org/trunk/modules/ainser
)

add_executable(test_i2c_comm ${SOURCE_FILES})

add_definitions()
add_definitions(-DMIOS32_BOARD=MBHP_CORE_STM32F4)
add_definitions(-DMIOS32_FAMILY=STM32F4xx)
add_definitions(-DMIOS32_LCD=universal)
add_definitions(-DMIOS32_PROCESSOR=STM32F407VG)
