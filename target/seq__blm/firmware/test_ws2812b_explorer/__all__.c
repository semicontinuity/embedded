#include <avr/io.h>

#include "util/formatter.c"
#include "util/parser.c"

#include "drivers/comm/ws2812b.c"
#include "services/ws2812b_renderer.c"
#include "services/console.c"
#include "services/console__in__polled.c"
#include "services/console_ws2812b.c"

#include "main.c"
