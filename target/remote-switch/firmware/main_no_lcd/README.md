# main_no_lcd

Firmware for the remote switch board (no LCD variant).
Reads temperature from a DS18X20 1-wire sensor and exposes it via Modbus RTU.

## Timer0 and Timer2 usage

Timer0 is **shared** between two components, used at different times and in different modes:

| Phase | Owner | Timer0 mode |
|---|---|---|
| 1-wire transaction (bit I/O) | `onewire__t0t2` driver | Fast bit-span timer: prescaler 8 or 64, preloaded for precise bit slot timeouts |
| Conversion wait + scheduling | `temperature_reader` | Slow tick: prescaler 1024, normal WGM (~16ms overflow period at 16MHz) |

After each 1-wire transaction completes, `temperature_reader` reconfigures timer0 back to slow tick mode. The overflow pending flag is used both to schedule the temperature reader thread and to count down the DS18B20 conversion wait (`TEMPERATURE_READER__CONVERSION_DELAY_COUNT` overflows ≈ 750ms).

**Timer2** is used exclusively by the `onewire__t0t2` driver to **shape individual 1-wire bit waveforms**:
- Generates the 0→1 bus transition at the correct time within each bit slot (OC2 interrupt)
- Reads the bus state and stops at the sample point (T2OVF interrupt)
- For WRITE1/READ: drives bus low for 6µs, releases at 6µs, samples at 15µs
- For WRITE0: drives bus low for 60µs, releases at 60µs, samples at 69µs
- For RESET: drives bus low for 480µs, releases, samples presence at 552µs

Timer0 signals end-of-bit-slot (at 70µs for data bits, 960µs for reset), allowing the onewire thread to proceed to the next bit.

## Thread interaction: temperature_reader ↔ onewire

```
temperature_reader thread          onewire thread
        |                               |
        |-- conversion_request() ------>|
        |   setup tx: SKIP_ROM+CONV_T   |
        |   onewire__transaction__run() |
        |                               |-- reset bus (timer0+timer2)
        |                               |-- send bytes bit by bit
        |                               |   (timer0=bit-span, timer2=bit-form)
        |<-- VT_YIELD (each bit done) --|
        |   onewire__thread__run()      |
        |   until !is_alive()           |
        |                               |-- done, timer0=DEFAULT
        |                               |
        |-- conversion_await() -------->|
        |   timer0 = PRESCALER_1024     |
        |   delay_counter = N           |
        |<-- VT_YIELD (each overflow)   |
        |   clear pending, decrement    |
        |   until counter == 0          |
        |   (~750ms elapsed)            |
        |                               |
        |-- conversion_read() --------->|
        |   setup tx: SKIP_ROM+READ     |
        |   setup rx: response[9]       |
        |   onewire__transaction__run() |
        |                               |-- reset bus (timer0+timer2)
        |                               |-- send bytes, receive 9 bytes
        |                               |   (timer0=bit-span, timer2=bit-form)
        |<-- VT_YIELD (each bit done) --|
        |   onewire__thread__run()      |
        |   until !is_alive()           |
        |                               |-- done, timer0=DEFAULT
        |                               |
        |-- conversion_report()         |
        |   reading = (response[0] |    |
        |     response[1]<<8) << 4      |
        |   on_changed()                |
        |                               |
        |  (loop forever)               |
```

## Configuration

See [`main_no_lcd.conf`](main_no_lcd.conf) for all compile-time parameters, including:

- `TEMPERATURE_READER__CONVERSION_DELAY_COUNT` — number of timer0 overflows to wait for DS18B20 conversion (~750ms)
- `ONEWIRE__BIT_SPAN_TIMER__FAST_CONF_TIMEOUT` / `SLOW_CONF_TIMEOUT` — timer0 preload values for 1-wire bit slot duration
- `ONEWIRE__BIT_FORM_TIMER__WRITE1_DRIVE_HIGH_TIME` / `WRITE1_READ_TIME` — timer2 values for WRITE1/READ bit waveform
- `ONEWIRE__BIT_FORM_TIMER__WRITE0_DRIVE_HIGH_TIME` / `WRITE0_READ_TIME` — timer2 values for WRITE0 bit waveform
- `ONEWIRE__BIT_FORM_TIMER__RESET_DRIVE_HIGH_TIME` / `RESET_READ_TIME` — timer2 values for reset pulse waveform
