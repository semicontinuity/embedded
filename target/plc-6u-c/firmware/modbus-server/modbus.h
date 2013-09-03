#ifndef MODBUS_H
#define MODBUS_H

#define MODBUS_FUNCTION_READ_COILS                 (1)
#define MODBUS_FUNCTION_READ_DISCRETE_INPUTS       (2)
#define MODBUS_FUNCTION_READ_HOLDING_REGISTER      (3)
#define MODBUS_FUNCTION_READ_INPUT_REGISTER        (4)
#define MODBUS_FUNCTION_WRITE_SINGLE_COIL          (5)
#define MODBUS_FUNCTION_WRITE_REGISTER             (6)

#define MODBUS_FRAME_SIZE_MIN                      (4)

#define MODBUS_FRAME_OFFSET_ADDRESS                (0)
#define MODBUS_FRAME_OFFSET_FUNCTION               (1)
#define MODBUS_FRAME_OFFSET_DATA                   (2)

#endif