cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

add_executable(main
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/DEMO_F030F4/PeripheralPins.c
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/DEMO_F030F4/PinNamesVar.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/DEMO_F030F4/variant.cpp
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/DEMO_F030F4/variant.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/Arduino.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/HardwareSerial.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/HardwareSerial.cpp
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/board.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/pins_arduino.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/wiring.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32/PeripheralPins.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32/PinConfigured.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32/PinNames.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32/PinNamesTypes.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32/analog.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32/stm32_def.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32/LL/stm32yyxx_ll_adc.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/libraries/SrcWrapper/src/stm32/analog.cpp
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/libraries/SrcWrapper/src/stm32/pinmap.c
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/system/Drivers/CMSIS/Device/ST/STM32F0xx/Include/stm32f0xx.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/system/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.c
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/system/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_adc.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/system/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_adc_ex.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/system/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_gpio.h
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/system/STM32F0xx/stm32f0xx_hal_conf.h
        ../../../../../../../../.arduino15/packages/STM32/tools/CMSIS/5.5.1/CMSIS/Core/Include/core_cm0.h
        midi_package.h
        midi_sender__arduino_serial.h
        main.ino

        midi_sender.h analog_nonblocking.h)

include_directories(
        .
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/cores/arduino/stm32/LL/
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/DEMO_F030F4
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/system/Drivers/CMSIS/Device/ST/STM32F0xx/Include
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/system/Drivers/STM32F0xx_HAL_Driver/Inc
        ../../../../../../../../.arduino15/packages/STM32/hardware/stm32/1.9.0/system/STM32F0xx
        ../../../../../../../../.arduino15/packages/STM32/tools/CMSIS/5.5.1/CMSIS/Core/Include

        /opt/gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include
        /opt/arduino-1.8.13/libraries/pt-1.4
)

add_definitions(-DLC_INCLUDE="lc-addrlabels.h")
add_definitions(-DDEBUG=0)
add_definitions(-DSTM32F0xx)
add_definitions(-DSTM32F030x6)
add_definitions(-DHAL_ADC_MODULE_ENABLED)

set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)
