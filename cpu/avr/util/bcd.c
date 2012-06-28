// =============================================================================
// Limited support for binary-to-bcd conversion.
// Used e.g. for printing decimal numbers, or displaying them on displays.
//
// Currently, only numbers with the range 0-511 are supported.
// =============================================================================

#include <cpu/avr/util/bcd.h>

uint8_t const BCD_OF_HIGH_NIBBLE[] = {
    0x00, 0x00,
    0x00, 0x16,
    0x00, 0x32,
    0x00, 0x48,
    0x00, 0x64,
    0x00, 0x80,
    0x00, 0x96,
    0x01, 0x12,
    0x01, 0x28,
    0x01, 0x44,
    0x01, 0x60,
    0x01, 0x76,
    0x01, 0x92,
    0x02, 0x08,
    0x02, 0x24,
    0x02, 0x40,
};

/**
 * Converts the value (with the range 0-511) to BCD representation. 
 */
uint16_t uint9_to_bcd(const uint16_t number) {

    // Algorithm:
    // Split number into nibbles: c=(bit 8), b=(bits 7-4), a=(bits 3-0).
    // Then compute BCD(number) = BCD(a) + BCD(b) + BCD(c).
    //    BCD(a) is computed with BCD correction.
    //    BCD(b) is taken from the table BCD_OF_HIGH_NIBBLE.
    //    BCD(c) is 0x0512 if number is in the range 256-511, 0x0000 otherwise.

    register uint8_t r_h;  // result's high byte (hundreds)
    register uint8_t r_l;  // higher's low byte (tens and ones)
    register uint8_t a;    // will hold 'a' and then BCD of it.

    // Extract a = bits 3-0 of number.
    __asm__ __volatile__ (
        "mov  %0, %A1\n\t"
        "andi %0, 0x0F\n\t"
        : "=d"(a)
        : "r"(number)
    );
    
    // BCD correction of 'a'
    __asm__ __volatile__ (
        "subi %0, -6              \n\t"       // add 6 to correct. will set H flag for 0..9, clear for 10..15
        "brhc L_%=                \n\t"       // if half carry was NOT set, skip the following:
        "subi %0, 6               \n\t"       //     restore 'a' by subtracting 6
"L_%=:"
        : "+d"(a)
    );

    // Extract b = bits 7-4 of number. Shift it to get the proper offset in the BCD_OF_HIGH_NIBBLE.
    register uint8_t b;
    __asm__ __volatile__ (
        "mov  %0, %A1  \n\t"
        "andi %0, 0xF0 \n\t"
        "swap %0       \n\t"
        "add  %0, %0   \n\t"
        : "=d"(b)
        : "r"(number)
    );

    // Load BCD(b) into r_h and r_l
    register uint8_t const * bcd = BCD_OF_HIGH_NIBBLE;
    bcd += b;
    r_h = *(bcd);
    r_l = *(bcd+1);


    // Compute BCD(a) + BCD(b). BCD(b) is in r_h and r_l.
    // b is re-used to save the SREG.
    __asm__ __volatile__ (
        "subi %0, -102                  \n\t" // add 0x66 to r_l produce half-carry and carry
        "add  %0, %2                    \n\t" // r_l += a (binary)
        "in   __tmp_reg__, __SREG__     \n\t"	// save SREG to b
        "adc  %1, __zero_reg__          \n\t" // if carry was set, increment r_h.
        "sbrs __tmp_reg__, 0            \n\t" // if carry was not set...
        "subi %0, 0x60                  \n\t" //     restore high nibble of r_l
        "sbrs __tmp_reg__, 5            \n\t" // if half-carry was not set...
        "subi %0, 0x06                  \n\t" //     restore low nibble of r_l
        : "+d"(r_l), "+d"(r_h)
        : "r"(a)
    );

    // If 'number' is in the range 256-511, BCD add 0x0256 to the result.
    // b is re-used to save the SREG.
    __asm__ __volatile__ (
        "andi %B2, 0x01                 \n\t" // Check if bit 8 is set (number in range 256-511)
        "breq L_%=                      \n\t" // If not set, skip...

        "subi %0, -(0x66)-(0x56)        \n\t" // add 0x56 (lower 2 digits of 256 in BCD), and also 0x66 to r_l produce half-carry and carry
        "in   __tmp_reg__, __SREG__     \n\t"	// save SREG to b

        "sbci %1, -3                    \n\t" // Need to add 0x02 (hundreds) + carry after "addi" == "add 2, then add 1 if no borrow"
        "sbrc __tmp_reg__, 0            \n\t" // if there was no borrow (C clear)...
        "subi %0, 0x60                  \n\t" //     restore high nibble of r_l
        "sbrc __tmp_reg__, 5            \n\t" // if there was no half-borrow (H clear)...
        "subi %0, 0x06                  \n\t" //     restore low nibble of r_l
    "L_%=:"
        : "+d"(r_l), "+d"(r_h)
        : "r"(number)
    );

    return (r_h<<8) + r_l;
}
