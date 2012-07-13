#include "device.h"

#include "cpu/avr/drivers/display/mt12864/driver.h"
#include "cpu/avr/drivers/display/mt12864/char-output.h"
#include "cpu/avr/drivers/display/mt12864/text-output.h"
#include "util/font/Font_6x8.h"

#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>

int main(void)
{
    mt12864_init();

    Draw_Text ("ABCDEFGHIJKLMNOPQRSTU", 0, 0, &Font_6x8, 0);
    Draw_Text ("absdefghijklmnopqrstu", 0, 8, &Font_6x8, 0);
    Draw_Text ("àáâãäå¸æçèéêëìíîïğñòó", 0, 16, &Font_6x8, 0);
    Draw_Text ("ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓ", 0, 24, &Font_6x8, 0);
    Draw_Text ("vwxyz~!@#$%^&*()_+{}:", 0, 32, &Font_6x8, 0);
    Draw_Text ("VW,./<>?;'[]=-`|==ışÿ", 0, 40, &Font_6x8, 0);
    Draw_Text ("01234567890123456789-", 0, 48, &Font_6x8, 0);
    Draw_Text ("ÔÕÖ×ØÙÚÛÜİŞßôõö÷øùúûü", 0, 56, &Font_6x8, 0);

    return 0;
}
