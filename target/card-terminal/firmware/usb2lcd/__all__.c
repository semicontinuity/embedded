//static void USB_DeviceTask(void);



#include "cpu/avr/drivers/display/mt12232/terminal.c"
#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.c"
#include "util/font/Font_6x8.c"
#include "usb2lcd.c"
#include "Descriptors.c"


#include "Common/Common.h"
#include "Drivers/USB/USB.h"
//#include "Drivers/USB/Core/Events.h"

#include "Drivers/USB/Core/Events.c"

#include "Drivers/USB/Core/AVR8/Device_AVR8.c"
#include "Drivers/USB/Core/AVR8/USBController_AVR8.c"
#include "Drivers/USB/Core/AVR8/USBInterrupt_AVR8.c"
#include "Drivers/USB/Core/AVR8/Endpoint_AVR8.c"
#include "Drivers/USB/Core/AVR8/EndpointStream_AVR8.c"

#include "Drivers/USB/Core/ConfigDescriptors.c"
#include "Drivers/USB/Core/DeviceStandardReq.c"

#include "Drivers/USB/Class/Device/CDCClassDevice.c"

#include "Drivers/USB/Core/USBTask.c"


