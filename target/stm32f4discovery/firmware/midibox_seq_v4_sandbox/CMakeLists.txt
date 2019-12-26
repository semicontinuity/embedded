cmake_minimum_required(VERSION 3.11)
project(midibox_seq_v4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        mios32/tasks.c
        mios32/mios32_config.h

        mod/seq_mod.h
        mod/seq_mod.c

        core/app.c
        core/seq_hwcfg.c
        core/seq_ui.c
        core/seq_ui_pages.c
        core/seq_ui_todo.c
        core/seq_ui_menu.c
        core/seq_ui_bookmarks.c
        core/seq_ui_edit.c
        core/seq_ui_mute.c
        core/seq_ui_pmute.c
        core/seq_ui_pattern.c
        core/seq_ui_pattern_remix.c
        core/seq_ui_song.c
        core/seq_ui_trkevnt.c
        core/seq_ui_trkinst.c
        core/seq_ui_trkmode.c
        core/seq_ui_trkdir.c
        core/seq_ui_trkdiv.c
        core/seq_ui_trklen.c
        core/seq_ui_trktran.c
        core/seq_ui_trkgrv.c
        core/seq_ui_trkmorph.c
        core/seq_ui_trkrnd.c
        core/seq_ui_trkeuclid.c
        core/seq_ui_trkjam.c
        core/seq_ui_trgasg.c
        core/seq_ui_fx.c
        core/seq_ui_fx_echo.c
        core/seq_ui_fx_humanize.c
        core/seq_ui_fx_robotize.c
        core/seq_ui_fx_limit.c
        core/seq_ui_fx_lfo.c
        core/seq_ui_fx_dupl.c
        core/seq_ui_fx_scale.c
        core/seq_ui_manual.c
        core/seq_ui_util.c
        core/seq_ui_bpm.c
        core/seq_ui_bpm_presets.c
        core/seq_ui_opt.c
        core/seq_ui_save.c
        core/seq_ui_midi.c
        core/seq_ui_sysex.c
        core/seq_ui_disk.c
        core/seq_ui_eth.c
        core/seq_ui_midimon.c
        core/seq_ui_mixer.c
        core/seq_ui_cv.c
        core/seq_ui_info.c
        core/seq_ui_stepsel.c
        core/seq_ui_trgsel.c
        core/seq_ui_parsel.c
        core/seq_ui_inssel.c
        core/seq_ui_tracksel.c
        core/seq_ui_trklive.c
        core/seq_cv.c
        core/seq_midi_port.c
        core/seq_midi_in.c
        core/seq_midi_sysex.c
        core/seq_midi_router.c
        core/seq_midply.c
        core/seq_midexp.c
        core/seq_midimp.c
        core/seq_blm.c
        core/seq_cc.c
        core/seq_cc_labels.c
        core/seq_core.c
        core/seq_scale.c
        core/seq_groove.c
        core/seq_morph.c
        core/seq_humanize.c
        core/seq_robotize.c
        core/seq_lfo.c
        core/seq_chord.c
        core/seq_pattern.c
        core/seq_record.c
        core/seq_live.c
        core/seq_file.c
        core/seq_file_b.c
        core/seq_file_m.c
        core/seq_file_s.c
        core/seq_file_g.c
        core/seq_file_c.c
        core/seq_file_gc.c
        core/seq_file_t.c
        core/seq_file_bm.c
        core/seq_file_presets.c
        core/seq_file_hw.c
        core/seq_layer.c
        core/seq_random.c
        core/seq_trg.c
        core/seq_par.c
        core/seq_mixer.c
        core/seq_song.c
        core/seq_label.c
        core/seq_lcd.c
        core/seq_lcd_logo.c
        core/seq_ui_fx_loop.c
        core/seq_terminal.c
        core/seq_statistics.c
        core/seq_led.c
        core/seq_blm8x8.c
        core/seq_tpd.c

        ./../../../../../mios32/include/mios32/mios32_din.h
        ./../../../../../mios32/include/mios32/mios32_enc.h
        ./../../../../../mios32/include/mios32/mios32_lcd.h

        ./../../../../../mios32/mios32/common/mios32_com.c
        ./../../../../../mios32/mios32/common/mios32_din.c
        ./../../../../../mios32/mios32/common/mios32_dout.c
        ./../../../../../mios32/mios32/common/mios32_enc.c
        ./../../../../../mios32/mios32/common/mios32_enc28j60.c
        ./../../../../../mios32/mios32/common/mios32_iic_bs.c
        ./../../../../../mios32/mios32/common/mios32_iic_midi.c
        ./../../../../../mios32/mios32/common/mios32_lcd.c
        ./../../../../../mios32/mios32/common/mios32_mf.c
        ./../../../../../mios32/mios32/common/mios32_midi.c
        ./../../../../../mios32/mios32/common/mios32_osc.c
        ./../../../../../mios32/mios32/common/mios32_sdcard.c
        ./../../../../../mios32/mios32/common/mios32_spi_midi.c
        ./../../../../../mios32/mios32/common/mios32_srio.c
        ./../../../../../mios32/mios32/common/mios32_iic_io.c
        ./../../../../../mios32/mios32/common/mios32_timestamp.c
        ./../../../../../mios32/mios32/common/mios32_uart_midi.c
        ./../../../../../mios32/mios32/common/printf-stdarg.c

        ./../../../../../mios32/programming_models/traditional/startup_stm32f4xx.c

        ./../../../../../mios32/programming_models/traditional/main.c
        ./../../../../../mios32/programming_models/traditional/strtol.c
        ./../../../../../mios32/FreeRTOS/Source/tasks.c
        ./../../../../../mios32/FreeRTOS/Source/list.c
        ./../../../../../mios32/FreeRTOS/Source/queue.c
        ./../../../../../mios32/FreeRTOS/Source/timers.c
        ./../../../../../mios32/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
        ./../../../../../mios32/FreeRTOS/Source/portable/MemMang/heap_4.c

        ./../../../../../mios32/mios32/STM32F4xx/mios32_ain.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_board.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_bsl.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_delay.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_i2s.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_iic.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_irq.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_spi.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_stopwatch.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_sys.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_timer.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_uart.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_usb.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_usb_com.c
        ./../../../../../mios32/mios32/STM32F4xx/mios32_usb_midi.c
        ./../../../../../mios32/mios32/STM32F4xx/usb_conf.h
        ./../../../../../mios32/mios32/STM32F4xx/usbd_conf.h
        ./../../../../../mios32/mios32/STM32F4xx/usbd_desc.h
        ./../../../../../mios32/mios32/STM32F4xx/usbh_conf.h

        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/CMSIS/Include/core_cm4.h

        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/CMSIS/ST/STM32F4xx/Include/stm32f4xx.h

        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/misc.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_adc.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_can.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_crc.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_cryp.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dbgmcu.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dcmi.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_exti.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_flash.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_fsmc.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_gpio.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_hash.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_i2c.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_iwdg.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_pwr.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rcc.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rng.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rtc.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sdio.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_spi.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_syscfg.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_tim.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_usart.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_wwdg.h
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/misc.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c

        # ./../../../../../mios32/modules/app_lcd/universal/app_lcd.h
        # ./../../../../../mios32/modules/app_lcd/universal/app_lcd.c

        ./../../../../../mios32/modules/app_lcd/clcd_parallel/app_lcd.h
        ./../../../../../mios32/modules/app_lcd/clcd_parallel/app_lcd.c

        ./../../../../../mios32/modules/blm/blm.c
        ./../../../../../mios32/modules/blm/blm.h
        ./../../../../../mios32/modules/blm_scalar_master/blm_scalar_master.c
        ./../../../../../mios32/modules/blm_scalar_master/blm_scalar_master.h
        ./../../../../../mios32/modules/aout/aout.c
        ./../../../../../mios32/modules/aout/aout.h

        ./../../../../../mios32/modules/glcd_font/glcd_font.h

        ./../../../../../mios32/modules/sequencer/seq_bpm.c
        ./../../../../../mios32/modules/sequencer/seq_bpm.h
        ./../../../../../mios32/modules/sequencer/seq_midi_out.c
        ./../../../../../mios32/modules/sequencer/seq_midi_out.h

        ./../../../../../mios32/modules/file/file.c
        ./../../../../../mios32/modules/file/file.h

        ./../../../../../mios32/modules/uip/uip/uip.c
        ./../../../../../mios32/modules/uip/uip/uip_arp.c
        ./../../../../../mios32/modules/uip/uip/uiplib.c
        ./../../../../../mios32/modules/uip/uip/psock.c
        ./../../../../../mios32/modules/uip/uip/timer.c
        ./../../../../../mios32/modules/uip/uip/uip-neighbor.c
        ./../../../../../mios32/modules/uip/lib/memb.c
        ./../../../../../mios32/modules/uip/mios32/clock-arch.c
        ./../../../../../mios32/modules/uip/mios32/STM32F4xx/network-device.c

        ./../../../../../mios32/modules/uip_task_standard/uip_task.c
        ./../../../../../mios32/modules/uip_task_standard/dhcpc.c
        ./../../../../../mios32/modules/uip_task_standard/osc_server.c
        ./../../../../../mios32/modules/uip_task_standard/osc_client.c
        ./../../../../../mios32/modules/uip_task_standard/uip_terminal.c

        )
#./../../../../../mios32/programming_models/traditional/mini_cpp.cpp
#./../../../../../mios32/programming_models/traditional/freertos_heap.cpp


include_directories(
        /opt/gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include
        mios32
        core
        ./../../../../../mios32/include/mios32
        ./../../../../../mios32/include/mios32
        ./../../../../../mios32/programming_models/traditional
        ./../../../../../mios32/FreeRTOS/Source/include
        ./../../../../../mios32/FreeRTOS/Source/portable/GCC/ARM_CM3
        ./../../../../../mios32/FreeRTOS/Source/portable/MemMang
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/CMSIS/ST/STM32F4xx/Include
        ./../../../../../mios32/drivers/STM32F4xx/v1.1.0/CMSIS/Include

        ./../../../../../mios32/modules/app_lcd/clcd_parallel
        ./../../../../../mios32/modules/blm
        ./../../../../../mios32/modules/blm_scalar_master
        ./../../../../../mios32/modules/aout
        ./../../../../../mios32/modules/sequencer
        ./../../../../../mios32/modules/file
        ./../../../../../mios32/modules/notestack
        ./../../../../../mios32/modules/ainser
        ./../../../../../mios32/modules/glcd_font
        ./../../../../../mios32/modules/uip/uip
        ./../../../../../mios32/modules/uip/lib
        ./../../../../../mios32/modules/uip/mios32
        ./../../../../../mios32/modules/uip/mios32/STM32F4xx
        ./../../../../../mios32/modules/uip_task_standard
        ./../../../../../mios32/modules/uip_task_standard
        ./../../../../../mios32/modules/fatfs/src
)

add_executable(midibox_seq_v4 ${SOURCE_FILES})


add_definitions(-DMIOS32_FAMILY=STM32F4xx)
add_definitions(-DMIOS32_PROCESSOR=STM32F407VG)

add_definitions(-DMIOS32_BOARD=MBHP_CORE_STM32F4)
add_definitions(-DMIOS32_BOARD_MBHP_CORE_STM32F4)
add_definitions(-DMIOS32_BOARD_STR=\"MBHP_CORE_STM32F4\")

#add_definitions(-DMIOS32_BOARD=STM32F407VG_DIYMORE)
#add_definitions(-DMIOS32_BOARD_STM32F407VG_DIYMORE)
#add_definitions(-DMIOS32_BOARD_STR=\"STM32F407VG_DIYMORE\")

add_definitions(-DMIOS32_LCD=clcd_parallel)
add_definitions(-DMIOS32_LCD_clcd_parallel)
add_definitions(-DMIOS32_LCD_STR=\"clcd_parallel\")

#add_definitions(-DMIOS32_LCD=universal)
#add_definitions(-DMIOS32_LCD_universal)
#add_definitions(-DMIOS32_LCD_STR=\"universal\")

add_definitions(-DMIOS32_FAMILY_STM32F4xx)
add_definitions(-DMIOS32_FAMILY_STR=\"STM32F4xx\")
add_definitions(-DMIOS32_PROCESSOR_STM32F407VG)

add_definitions(-DUSE_STDPERIPH_DRIVER)
add_definitions(-DUSB_SUPPORT_USER_STRING_DESC)
