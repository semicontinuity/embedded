// Firmware for USB MIDI adapter for AHT10 temperature/humidity sensor.
// This sensor has I2C interface, and the logical choice would be to utilize USB-to-I2C adapter, e.g. usb-tiny-i2c.
// However, not all embedded linux distributions come with the driver for this adapter.
// Instead, this device provides sensor readings via USB MIDI interface, as USB MIDI drivers are widely available.

// Readings are reported with MIDI Pitch Bend message (that has 14-bit value payload): 1110nnnn  0fffffff  0ccccccc
// - temperature: MIDI channel 1 (nnnn=0000)
// - humidity: MIDI channel 2 (nnnn=0001)

// Hardware uses ATTiny85 (digispark)
// I2C connections:
// - SDA: PB0
// - SCL: PB2

// ============================================================================================================================

// Install DigiMIDI library from https://github.com/heartscrytech/DigisparkMIDI
#include <DigiMIDI.h>

DigiMIDIDevice midi;

// 14 bits of value: 0.bbbbbbbbbbbbbb: fractional value:
// Compute T as v*200.0 - 50.0
void send_temperature(int reading_14bits) {
  midi.sendPitchBend(reading_14bits, 1);
}

// 14 bits of value: 0.bbbbbbbbbbbbbb: fractional value:
// Compute H as v*100.0
void send_humidity(int reading_14bits) {
  midi.sendPitchBend(reading_14bits, 2);
}

// ============================================================================================================================

#define SDA_PORT PORTB
#define SDA_PIN 0
#define SCL_PORT PORTB
#define SCL_PIN 2
// Install SoftI2CMaster library from https://github.com/felias-fogg/SoftI2CMaster
#include <SoftI2CMaster.h>

// ============================================================================================================================
// Adopted from https://github.com/enjoyneering/AHTxx to use SoftI2CMaster library

#define AHT10_ADDRESS_7BIT                0x38
#define AHTXX_SOFT_RESET_REG              0xBA  //soft reset register
#define AHT1X_INIT_REG                    0xE1  //initialization register, for AHT1x only
#define AHTXX_START_MEASUREMENT_REG       0xAC  //start measurement register

/* calibration register controls */
#define AHT1X_INIT_CTRL_NORMAL_MODE       0x00  //normal mode on/off       bit[6:5], for AHT1x only
#define AHT1X_INIT_CTRL_CYCLE_MODE        0x20  //cycle mode on/off        bit[6:5], for AHT1x only
#define AHT1X_INIT_CTRL_CMD_MODE          0x40  //command mode  on/off     bit[6:5], for AHT1x only
#define AHTXX_INIT_CTRL_CAL_ON            0x08  //calibration coeff on/off bit[3]
#define AHTXX_INIT_CTRL_NOP               0x00  //NOP control, send after any "AHT1X_INIT_CTRL..."

/* measurement register controls */
#define AHTXX_START_MEASUREMENT_CTRL      0x33  //measurement controls, suspect this is temperature & humidity DAC resolution
#define AHTXX_START_MEASUREMENT_CTRL_NOP  0x00  //NOP control, send after any "AHTXX_START_MEASUREMENT_CTRL..."

#define AHTXX_CMD_DELAY          10      //delay between commands, in milliseconds
#define AHTXX_MEASUREMENT_DELAY  80      //wait for measurement to complete, in milliseconds

uint8_t aht10_readings_raw[6];


void aht10_reset(void) {
    if (!i2c_start((AHT10_ADDRESS_7BIT<<1)|I2C_WRITE)) {
        return;
    }
    i2c_write(AHTXX_SOFT_RESET_REG);
    i2c_stop();
}

void aht10_initialize(uint8_t value) {
    if (!i2c_start((AHT10_ADDRESS_7BIT<<1)|I2C_WRITE)) {
        return;
    }
    i2c_write(AHT1X_INIT_REG);
    i2c_write(value);
    i2c_write(AHTXX_INIT_CTRL_NOP);
    i2c_stop();
}

void aht10_set_normal_mode(void) {
    aht10_initialize(AHTXX_INIT_CTRL_CAL_ON | AHT1X_INIT_CTRL_NORMAL_MODE);
}

void aht10_read_raw(void) {
    if (!i2c_start((AHT10_ADDRESS_7BIT<<1)|I2C_WRITE)) {
        return;
    }
    i2c_write(AHTXX_START_MEASUREMENT_REG);
    i2c_write(AHTXX_START_MEASUREMENT_CTRL);
    i2c_write(AHTXX_START_MEASUREMENT_CTRL_NOP);
    i2c_stop();

    delay(AHTXX_MEASUREMENT_DELAY - AHTXX_CMD_DELAY);

    if (!i2c_start((AHT10_ADDRESS_7BIT<<1)|I2C_READ)) {
        return;
    }
    aht10_readings_raw[0] = i2c_read(false);
    aht10_readings_raw[1] = i2c_read(false);
    aht10_readings_raw[2] = i2c_read(false);
    aht10_readings_raw[3] = i2c_read(false);
    aht10_readings_raw[4] = i2c_read(false);
    aht10_readings_raw[5] = i2c_read(true);
    i2c_stop();
}


// ============================================================================================================================

void setup() {
  
  if (!i2c_init()) return;
  aht10_reset();
  delay(100);
  aht10_set_normal_mode();
}

// ============================================================================================================================

void loop() {
  midi.update();

  aht10_read_raw();

  // 20-bit value truncated to 14-bit
  uint16_t humidity_bits = ((aht10_readings_raw[1] << 8) | aht10_readings_raw[2]) >> 2;
  send_humidity((int)humidity_bits);

  // 20-bit value truncated to 14-bit
  uint16_t temperature_bits = ((aht10_readings_raw[3] & 0x0F) << 8) | aht10_readings_raw[4];
  temperature_bits <<= 2;
  temperature_bits |= (aht10_readings_raw[5] & 3); // attach 2 more lower bits => 14 bits total
  send_temperature((uint16_t)temperature_bits);

  delay(1000);
}
