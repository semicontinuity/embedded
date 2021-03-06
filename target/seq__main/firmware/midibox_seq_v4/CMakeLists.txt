cmake_minimum_required(VERSION 3.11)
project(midibox_seq_v4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/mios32/mios32_config.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/mios32/tasks.c

        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/app.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/app.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_blm8x8.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_blm8x8.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_blm.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_blm.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_cc.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_cc.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_cc_labels.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_cc_labels.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_chord.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_chord.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_core.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_core.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_cv.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_cv.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_b.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_b.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_bm.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_bm.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_c.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_c.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_g.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_gc.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_gc.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_g.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_hw.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_hw.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_m.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_m.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_presets.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_presets.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_s.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_s.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_t.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_file_t.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_groove.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_groove.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_humanize.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_humanize.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_hwcfg.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_hwcfg.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_label.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_label.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_layer.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_layer.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_lcd.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_lcd.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_lcd_logo.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_lcd_logo.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_lcd_logo.inc
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_led.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_led.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_lfo.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_lfo.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_live.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_live.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midexp.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midexp.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midi_in.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midi_in.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midimp.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midimp.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midi_port.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midi_port.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midi_router.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midi_router.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midi_sysex.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midi_sysex.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midply.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_midply.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_mixer.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_mixer.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_mod.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_mod.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_morph.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_morph.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_par.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_par.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_pattern.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_pattern.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_random.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_random.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_record.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_record.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_robotize.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_robotize.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_scale.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_scale.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_song.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_song.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_statistics.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_statistics.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_terminal.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_terminal.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_tpd.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_tpd.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_trg.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_trg.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_bookmarks.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_bpm.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_bpm_presets.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_cv.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_disk.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_edit.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_eth.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_fx.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_fx_dupl.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_fx_echo.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_fx_humanize.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_fx_lfo.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_fx_limit.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_fx_loop.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_fx_robotize.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_fx_scale.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_info.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_inssel.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_manual.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_menu.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_midimon.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_mixer.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_mute.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_opt.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_pages.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_pages.h
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_parsel.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_pattern.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_pattern_remix.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_pmute.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_save.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_song.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_stepsel.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_sysex.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_todo.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_tracksel.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trgasg.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trgsel.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trkdir.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trkdiv.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trkeuclid.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trkevnt.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trkgrv.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trkinst.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trkjam.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trklen.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trklive.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trkmode.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trkmorph.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trkrnd.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_trktran.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/seq_ui_util.c
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core/tasks.h

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

        ../../../../../../../github.com/semicontinuity/mios32/modules/app_lcd/clcd_parallel/app_lcd.h
        ../../../../../../../github.com/semicontinuity/mios32/modules/app_lcd/clcd_parallel/app_lcd.c
        ../../../../../../../github.com/semicontinuity/mios32/modules/blm/blm.c
        ../../../../../../../github.com/semicontinuity/mios32/modules/blm/blm.h
        ../../../../../../../github.com/semicontinuity/mios32/modules/file/file.c
        ../../../../../../../github.com/semicontinuity/mios32/modules/file/file.h
        ../../../../../../../github.com/semicontinuity/mios32/modules/glcd_font/glcd_font.h

        ../../../../../../../github.com/semicontinuity/mios32/modules/sequencer/seq_bpm.c
        ../../../../../../../github.com/semicontinuity/mios32/modules/sequencer/seq_bpm.h
        ../../../../../../../github.com/semicontinuity/mios32/modules/sequencer/seq_midi_out.c
        ../../../../../../../github.com/semicontinuity/mios32/modules/sequencer/seq_midi_out.h

        ../../../../../../../github.com/semicontinuity/mios32/modules/uip_task_standard/uip_task.h


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
        ../../../../../../../github.com/semicontinuity/mios32/modules/aout
        ../../../../../../../github.com/semicontinuity/mios32/modules/app_lcd/clcd_parallel
        ../../../../../../../github.com/semicontinuity/mios32/modules/blm
        ../../../../../../../github.com/semicontinuity/mios32/modules/blm_scalar_master
        ../../../../../../../github.com/semicontinuity/mios32/modules/fatfs/src
        ../../../../../../../github.com/semicontinuity/mios32/modules/file
        ../../../../../../../github.com/semicontinuity/mios32/modules/glcd_font
        ../../../../../../../github.com/semicontinuity/mios32/modules/midifile
        ../../../../../../../github.com/semicontinuity/mios32/modules/notestack
        ../../../../../../../github.com/semicontinuity/mios32/modules/random
        ../../../../../../../github.com/semicontinuity/mios32/modules/sequencer
        ../../../../../../../github.com/semicontinuity/mios32/modules/uip/uip
        ../../../../../../../github.com/semicontinuity/mios32/modules/uip_task_standard

        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/mios32
        ../../../../../../../github.com/semicontinuity/mios32/apps/sequencers/midibox_seq_v4/core
        /opt/gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include
        ../../../../../../../github.com/semicontinuity/mios32/include/mios32
        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/include
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/portable/GCC/ARM_CM3
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/portable/MemMang

        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32F4xx_StdPeriph_Driver/inc
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/CMSIS/ST/STM32F4xx/Include
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/CMSIS/Include
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32_USB_Device_Library/Core/inc
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32_USB_HOST_Library/Core/inc
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F4xx/v1.1.0/STM32_USB_OTG_Driver/inc

        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F4xx
)

add_executable(midibox_seq_v4 ${SOURCE_FILES})

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

add_definitions(-D__GNU_VISIBLE)
