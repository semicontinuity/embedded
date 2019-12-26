cmake_minimum_required(VERSION 3.11)
project(test-i2c-bridge-pb8pb9)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        src/app.c
        src/app.h
        src/i2c.c
        src/i2c.h
        src/i2c_config.h
        src/midi_output_config.h
        src/mios32_config.h
        src/hid_board.c
        src/hid_board.h

        ../../../../../../../github.com/semicontinuity/mios32/include/mios32/mios32_din.h
        ../../../../../../../github.com/semicontinuity/mios32/include/mios32/mios32_enc.h
        ../../../../../../../github.com/semicontinuity/mios32/include/mios32/mios32_lcd.h

        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_com.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_din.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_dout.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_enc.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_enc28j60.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_iic_bs.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_iic_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_lcd.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_mf.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_osc.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_sdcard.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_spi_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_srio.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_timestamp.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_uart_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/printf-stdarg.c

        ../../../../../../../github.com/semicontinuity/mios32/modules/app_lcd/universal/app_lcd.h
        ../../../../../../../github.com/semicontinuity/mios32/modules/app_lcd/universal/app_lcd.c
        ../../../../../../../github.com/semicontinuity/mios32/modules/glcd_font/glcd_font.h


        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional/startup_stm32f4xx.c

        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional/main.c
        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional/strtol.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/tasks.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/list.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/queue.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/timers.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/portable/MemMang/heap_4.c

        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_ain.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_board.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_bsl.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_delay.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_i2s.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_iic.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_irq.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_spi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_stopwatch.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_sys.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_timer.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_uart.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_usb.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_usb_com.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/mios32_usb_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/usb_conf.h
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/usbd_conf.h
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/usbd_desc.h
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx/usbh_conf.h

        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/CMSIS/Include/core_cm4.h

        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/CMSIS/ST/STM32F4xx/Include/stm32f4xx.h

        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/misc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_adc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_can.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_crc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_cryp.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dbgmcu.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dcmi.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_exti.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_flash.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_fsmc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_gpio.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_hash.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_i2c.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_iwdg.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_pwr.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rcc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rng.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rtc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sdio.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_spi.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_syscfg.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_tim.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_usart.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_wwdg.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/misc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c
        )
#        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional/mini_cpp.cpp
#../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional/freertos_heap.cpp


include_directories(
        src
        /opt/gcc-arm-none-eabi-8-2018-q4-major/arm-none-eabi/include
        ../../../../../../../github.com/semicontinuity/mios32/include/mios32
        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/include
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/portable/GCC/ARM_CM3
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/portable/MemMang
        ../../../../../../../github.com/semicontinuity/mios32/modules/ainser
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/CMSIS/ST/STM32F4xx/Include
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/CMSIS/Include

        ../../../../../../../github.com/semicontinuity/mios32/modules/glcd_font
)

add_executable(test-i2c-bridge-pb8pb9 ${SOURCE_FILES})

add_definitions(-DMIOS32_BOARD=MBHP_CORE_STM32F4)
add_definitions(-DMIOS32_FAMILY=STM32F4xx)
add_definitions(-DMIOS32_LCD=universal)
add_definitions(-DMIOS32_PROCESSOR=STM32F407VG)

add_definitions(-DMIOS32_BOARD_MBHP_CORE_STM32F4)
add_definitions(-DMIOS32_BOARD_STR=\"MBHP_CORE_STM32F4\")
add_definitions(-DMIOS32_LCD_universal)
add_definitions(-DMIOS32_LCD_STR=\"universal\")
add_definitions(-DMIOS32_FAMILY_STM32F4xx)
add_definitions(-DMIOS32_FAMILY_STR=\"STM32F4xx\")
add_definitions(-DMIOS32_PROCESSOR_STM32F407VG)

add_definitions(-DUSE_STDPERIPH_DRIVER)
add_definitions(-DUSB_SUPPORT_USER_STRING_DESC)
