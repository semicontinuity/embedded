import sys

class LCD(object):
    lcd_prev_reading = 0
    lcd_lsb = False
    lcd_init_seen = False
    lcd_display_memory  = bytearray(128)
    lcd_display_address = 0
    lcd_cgram_memory  = bytearray(64)
    lcd_cgram_address = -1

    def describe_command_write(self, lcd_byte):
        if lcd_byte & 0b10000000 == 0b10000000:
            self.lcd_display_address = lcd_byte & 0x7F
            description = "Set Display Address %02X" % self.lcd_display_address
        elif lcd_byte & 0b11000000 == 0b01000000:
            description = "Set CGRAM Address %02X" % (lcd_byte & 0x3F)
        elif lcd_byte & 0b11100000 == 0b00100000:
            bus_width = "8" if lcd_byte & 0b00010000 == 0b00010000 else "4"
            n_lines = "2" if lcd_byte & 0b00001000 == 0b00001000 else "1"
            font_set = "5x10" if lcd_byte & 0b00000100 == 0b00000100 else "5x7"
            description = "LCD init %s-bit bus, %s lines, %s font" % (bus_width, n_lines, font_set)
        elif lcd_byte & 0b11110000 == 0b00010000:
            shift_on = "On" if lcd_byte & 0b00001000 == 0b00001000 else "Off"
            shift_dir = "Right" if lcd_byte & 0b00000100 == 0b00000100 else "Left"
            description = "Move Cursor/Shift Display: display shift: %s, direction: %s" % (shift_on, shift_dir)
        elif lcd_byte & 0b11111000 == 0b00001000:
            # Enable Display/Cursor
            display = "On" if lcd_byte & 0b00000100 == 0b00000100 else "Off"
            cursor = "On" if lcd_byte & 0b00000010 == 0b00000010 else "Off"
            blink = "On" if lcd_byte & 0b00000001 == 0b00000001 else "Off"
            description = "Display: %s, Cursor: %s, Blink: %s" % (display, cursor, blink)
        elif lcd_byte & 0b11111100 == 0b00000100:
            # Set Cursor Move Direction
            inc_cursor = "On" if lcd_byte & 0b00000010 == 0b00000010 else "Off"
            shift_display = "On" if lcd_byte & 0b00000001 == 0b00000001 else "Off"
            description = "Increment cursor: %s, Shift display: %s" % (inc_cursor, shift_display)
        elif lcd_byte & 0b11111110 == 0b00000010:
            # Home
            description = "Return Cursor and LCD to home position"
        elif lcd_byte & 0b11111111 == 0b00000001:
            # Clear
            description = "Clear LCD and home cursor"
        else:
            description = "UNKNOWN CMD %02X" % lcd_byte
        return description

    def describe_command_read(self, lcd_byte):
        return "Read status: Busy flag=%s" % "Yes" if lcd_byte & 0x80 else "No"

    def describe_data_write(self, lcd_byte):
        if self.lcd_display_address > -1:
            self.lcd_display_memory[self.lcd_display_address] = lcd_byte
            self.lcd_display_address = self.lcd_display_address + 1
            if self.lcd_display_address == 128:
                self.lcd_display_address = 0
        else:
            self.lcd_cgram_memory[self.lcd_cgram_address] = lcd_byte
            self.lcd_cgram_address = self.lcd_cgram_address + 1
            if self.lcd_cgram_address == 64:
                self.lcd_cgram_address = 0
        return "%02X\n[%s]" % (lcd_byte, self.lcd_display_memory)

    def describe_data_read(self, lcd_byte):
        return "%02X" % lcd_byte



    def handle(self, lcd_reading):
        """
        event bits 0-3: data bits, bit 4: RES, bit 5: R/W
        return: string with description of event
        """
        lcd_data = lcd_reading & 0x0F
        description = ""

        if self.lcd_init_seen:
            if self.lcd_lsb:
                # received LSB (2nd nibble)
                res_rw = lcd_reading & 0x30
                res_rw_prev = self.lcd_prev_reading & 0x30
                if res_rw == res_rw_prev:
                    lcd_byte = lcd_data | ((self.lcd_prev_reading & 0x0F) << 4)
                    if res_rw == 0x00:
                        description = self.describe_command_write(lcd_byte)
                    elif res_rw == 0x10:
                        description = self.describe_data_write(lcd_byte)
                    elif res_rw == 0x20:
                        description = self.describe_command_read(lcd_byte)
                    else:
                        description = self.describe_data_read(lcd_byte)
                else:
                    description = "<Mismatch of RES and/or RW: %02X %02X>" % (res_rw, res_rw_prev)

                self.lcd_prev_reading = 0
                self.lcd_lsb = False
            else:
                # received MSB (1st nibble)
                description = "<MSB>"
                self.lcd_prev_reading = lcd_reading
                self.lcd_lsb = True
        else:
            if "{0:04b}".format(lcd_data) == '0011':
                description = "LCD pre-init"
            elif "{0:04b}".format(lcd_data) == '0010':
                self.lcd_init_seen = True
                description = "LCD init preamble"
        return "[%s] [%s] [%s] %s" % ("R" if lcd_reading & 0x20 else "W",
                                           "DAT" if lcd_reading & 0x10 else "CMD",
                                           "{0:04b}".format(lcd_data),
                                            description)


def handle_buttons(buttons):
    return "[%s] [%s] [%s] [%s] [%s] [%s]" % ("B5" if buttons & 0x20 else "  ",
                                              "B4" if buttons & 0x10 else "  ",
                                              "B3" if buttons & 0x08 else "  ",
                                              "B2" if buttons & 0x04 else "  ",
                                              "B1" if buttons & 0x02 else "  ",
                                              "B0" if buttons & 0x01 else "  ")

def handle_leds(leds):
    return "[%s] [%s] [%s]" % ("L2" if leds & 0x08 else "  ",
                              "L1" if leds & 0x04 else "  ",
                              "L0" if leds & 0x02 else "  ")


lcd = LCD()

def handle_event(event):
    if event & 0xC0 == 0x80:
        return "B\t%s" % handle_buttons(event & 0x3F)
    elif event & 0xC0 == 0x00:
        return "L\t%s" % handle_leds(event & 0x0E)
    elif event & 0xC0 == 0x40:
        return "D\t%s" % lcd.handle(event & 0x3F)
    else:
        return "U"


while 1:
    c = sys.stdin.read(1)
    if len(c) == 0:
        break

    event = ord(c)
    print "%02X\t%s" % (event, handle_event(event))
