# Remote Switch Firmware (main_no_lcd)

This firmware controls a remote switch device that can be operated through physical buttons or remotely via Modbus RTU protocol. The device provides 4 independent channels for controlling loads (such as lights, appliances, etc.) and can monitor temperature through a connected 1-Wire sensor.

## Key Features

### Physical Control
- **4 Physical Buttons**: Each button controls one of the 4 load channels
- **Button Operation**: Pressing a button toggles the corresponding load on/off
- **LED Indicators**: Each channel has an LED that shows the current state (on/off)

### Remote Control
- **Modbus RTU Protocol**: Full Modbus RTU implementation for remote control
- **Coil Control**: 
  - Read/write 4 coils (addresses 0-3) to control the 4 load channels
  - Each coil corresponds to one physical button/LED
- **Temperature Monitoring**: 
  - Reads temperature from connected DS18x20 sensor
  - Available as input register at address 0
- **Status Registers**:
  - Holding registers track communication statistics:
    - Valid frames received
    - Invalid frames received
    - Frames sent
    - Protocol errors
    - Buffer overflows

### Configuration
- **Baud Rate Selection**: Set via button combination at startup
  - Buttons 1-4 pressed in different combinations select baud rates from 1200 to 250000
  - Selected baud rate is saved to EEPROM for persistent configuration
- **Automatic Baud Rate Detection**: If no buttons are pressed at startup, uses the last saved baud rate

## User Operation

### Normal Operation
1. Press any of the 4 physical buttons to toggle the corresponding load/LED
2. The LED indicates the current state of each channel (on/off)
3. Remotely control the same 4 channels via Modbus commands
4. Monitor temperature readings through Modbus input registers

### Baud Rate Configuration
At startup:
1. Press button combinations to select communication speed:
   - Button 1+2+3 (others released): 1200 baud
   - Button 1+2 (3+4 released): 4800 baud
   - Button 1+3+4 (2 released): 9600 baud
   - And so on for other combinations
2. Release all buttons to save the setting
3. The device will use this baud rate for all subsequent communications

### Modbus Interface
- **Coils (0-3)**: Control the 4 load channels (readable/writable)
- **Input Register (0)**: Temperature reading from 1-Wire sensor
- **Holding Registers (0-4)**: Communication statistics (readable/writable)

## Technical Details
This firmware is designed for AVR microcontrollers and implements:
- Button debouncing using watchdog timer
- Modbus RTU protocol stack
- 1-Wire communication for temperature sensor
- Non-volatile configuration storage in EEPROM
- Real-time temperature monitoring thread