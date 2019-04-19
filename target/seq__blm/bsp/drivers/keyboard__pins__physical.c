#include "drivers/keyboard__pins.h"

#include "drivers/in/button0.h"
#include "drivers/in/button1.h"
#include "drivers/in/button2.h"
#include "drivers/in/button3.h"
#include "drivers/in/button4.h"
#include "drivers/in/button5.h"
#include "drivers/in/button6.h"
#include "drivers/in/button7.h"
#include "drivers/in/button8.h"
#include "drivers/in/button9.h"
#include "drivers/in/button10.h"
#include "drivers/in/button11.h"
#include "drivers/in/button12.h"
#include "drivers/in/button13.h"
#include "drivers/in/button14.h"
#include "drivers/in/button15.h"


void keyboard__pins__init(void) {
    button0__init();
    button1__init();
    button2__init();
    button3__init();
    button4__init();
    button5__init();
    button6__init();
    button7__init();
    button8__init();
    button9__init();
    button10__init();
    button11__init();
    button12__init();
    button13__init();
    button14__init();
    button15__init();
}
