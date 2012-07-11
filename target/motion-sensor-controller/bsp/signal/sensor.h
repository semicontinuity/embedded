// User signal:	SENSOR
// Purpose:	Aggregated sensor output
// Direction:	Output
// Active:	High
// AVR signal:	PC3


//    +--------------------------------+
//    |                                |
// +--+  +--+                          +--+
// |     |  |                             |
// |     |  |                             |
// |     |  |                             |
// |  MCU|  |                             |
// |     |  |   * .         * .           |
// |     |  |   . .         . .           |
// |     |  |   . .         . .           |
// +--+  +--+   . .         . .        +--+
//    |         . .         . .        |
//    +--------------------------------+

#define SENSOR_PORT          (PORTC)
#define SENSOR_DIR           (DDRC)
#define SENSOR_PIN           (3)
