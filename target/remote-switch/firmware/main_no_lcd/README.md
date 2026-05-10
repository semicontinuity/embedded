# main_no_lcd

Firmware for the remote switch board (no LCD variant).
Reads temperature from a DS18X20 1-wire sensor and exposes it via Modbus RTU.

## Timer0 usage

Timer0 is **shared** between two components, used at different times and in different modes:

| Phase | Owner | Timer0 mode |
|---|---|---|
| 1-wire transaction (bit I/O) | `onewire__t0t2` driver | Fast bit-span timer: prescaler 8 or 64, preloaded for precise bit slot timeouts |
| Conversion wait + scheduling | `temperature_reader` | Slow tick: prescaler 1024, normal WGM (~16ms overflow period at 16MHz) |

After each 1-wire transaction completes, `temperature_reader` reconfigures timer0 back to slow tick mode. The overflow pending flag is used both to schedule the temperature reader thread and to count down the DS18B20 conversion wait (`TEMPERATURE_READER__CONVERSION_DELAY_COUNT` overflows ≈ 750ms).

## Thread interaction: temperature_reader ↔ onewire

```
temperature_reader thread          onewire thread              Timer0
        |                               |                         |
        |-- conversion_request() ------>|                         |
        |   setup tx: SKIP_ROM+CONV_T   |                         |
        |   onewire__transaction__run() |                         |
        |                               |-- reset bus             |
        |                               |-- send bytes bit by bit |
        |                               |   (timer0 = fast)       |
        |<-- VT_YIELD (each tick) ------|                         |
        |   onewire__thread__run()      |                         |
        |   until !is_alive()           |                         |
        |                               |-- done, timer0=DEFAULT  |
        |                               |                         |
        |-- conversion_await() -------->|                         |
        |   timer0 = PRESCALER_1024     |                    slow tick
        |   delay_counter = N           |                         |
        |<-- VT_YIELD (each overflow) --|-------- tick ---------->|
        |   clear pending, decrement    |                         |
        |   until counter == 0          |                         |
        |   (~750ms elapsed)            |                         |
        |                               |                         |
        |-- conversion_read() --------->|                         |
        |   setup tx: SKIP_ROM+READ     |                         |
        |   setup rx: response[9]       |                         |
        |   onewire__transaction__run() |                         |
        |                               |-- reset bus             |
        |                               |-- send bytes bit by bit |
        |                               |-- receive 9 bytes       |
        |                               |   (timer0 = fast)       |
        |<-- VT_YIELD (each tick) ------|                         |
        |   onewire__thread__run()      |                         |
        |   until !is_alive()           |                         |
        |                               |-- done, timer0=DEFAULT  |
        |                               |                         |
        |-- conversion_report()         |                         |
        |   reading = (response[0] |    |                         |
        |     response[1]<<8) << 4      |                         |
        |   on_changed()                |                         |
        |                               |                         |
        |  (loop forever)               |                         |
```

## Configuration

See [`main_no_lcd.conf`](main_no_lcd.conf) for all compile-time parameters, including:

- `TEMPERATURE_READER__CONVERSION_DELAY_COUNT` — number of timer0 overflows to wait for DS18B20 conversion (~750ms)
- `ONEWIRE__BIT_SPAN_TIMER__FAST_CONF_TIMEOUT` / `SLOW_CONF_TIMEOUT` — timer0 preload values for 1-wire bit timing
- `ONEWIRE__BIT_FORM_TIMER__*` — timer2 values for 1-wire bit waveform shaping
