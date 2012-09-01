#include "comm_service__descriptor_memory.h"

const uint8_t comm_sevice__descriptor_memory__value[] PROGMEM = {

    // Device descriptor
    // -----------------
    0x4B, 0x49,                         // idVendor
    0x01, 0x00,                         // idProduct
    0x00, 0x00,                         // bcdDevice
    0x10,                               // bAdminInterfaceType (0x00=AVR+MCP2515)
    0,                                  // iManufacturer
    1,                                  // iProduct = "Rolling shutter controller"
    2,                                  // iSerialNumber = "0001"
    2,                                  // iNumInterfaces
    2,                                  // iNumStrings

    // String lengths
    // ------------------
    26,
    4,
    16,
    6,

    // Strings
    // ------------------
    'R','o','l','l','i','n','g',' ','s','h','u','t','t','e','r',' ','c','o','n','t','r','o','l','l','e','r',
    '0','0','0','1',
    'M','o','t','o','r',' ','c','o','n','t','r','o','l','l','e','r',
    'K','e','y','p','a','d',

    // Interface 0: Motor controller
    // -----------------------------
    0xFF,                               // bInterfaceClass
    0xFF,                               // bInterfaceSubclass
    3,                                  // bNumSlots
    3,                                  // bNumReports
    3,                                  // iInterface = "Motor controller"

    // Interface 1: Keypad
    // -----------------------------
    0xFF,                               // bInterfaceClass
    0xFF,                               // bInterfaceSubclass
    1,                                  // bNumSlots
    1,                                  // bNumReports
    4                                   // iInterface = "Keypad"    
};
