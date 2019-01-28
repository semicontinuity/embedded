#ifndef __ARCH__AVR__MACH_HPP__
#define __ARCH__AVR__MACH_HPP__

#if defined (__AVR_AT94K__)
#  include "arch/avr/mach-at94k.hpp"
#elif defined (__AVR_AT43USB320__)
#  include "arch/avr/mach-43u32x.hpp"
#elif defined (__AVR_AT43USB355__)
#  include "arch/avr/mach-43u35x.hpp"
#elif defined (__AVR_AT76C711__)
#  include "arch/avr/mach-76c711.hpp"
#elif defined (__AVR_AT86RF401__)
#  include "arch/avr/mach-86r401.hpp"
#elif defined (__AVR_AT90PWM1__)
#  include "arch/avr/mach-90pwm1.hpp"
#elif defined (__AVR_AT90PWM2__)
#  include "arch/avr/mach-90pwmx.hpp"
#elif defined (__AVR_AT90PWM2B__)
#  include "arch/avr/mach-90pwm2b.hpp"
#elif defined (__AVR_AT90PWM3__)
#  include "arch/avr/mach-90pwmx.hpp"
#elif defined (__AVR_AT90PWM3B__)
#  include "arch/avr/mach-90pwm3b.hpp"
#elif defined (__AVR_AT90PWM216__)
#  include "arch/avr/mach-90pwm216.hpp"
#elif defined (__AVR_AT90PWM316__)
#  include "arch/avr/mach-90pwm316.hpp"
#elif defined (__AVR_AT90PWM81__)
#  include "arch/avr/mach-90pwm81.hpp"
#elif defined (__AVR_ATmega8U2__)
#  include "arch/avr/mach-m8u2.hpp"
#elif defined (__AVR_ATmega16M1__)
#  include "arch/avr/mach-m16m1.hpp"
#elif defined (__AVR_ATmega16U2__)
#  include "arch/avr/mach-m16u2.hpp"
#elif defined (__AVR_ATmega16U4__)
#  include "arch/avr/mach-m16u4.hpp"
#elif defined (__AVR_ATmega32C1__)
#  include "arch/avr/mach-m32c1.hpp"
#elif defined (__AVR_ATmega32M1__)
#  include "arch/avr/mach-m32m1.hpp"
#elif defined (__AVR_ATmega32U2__)
#  include "arch/avr/mach-m32u2.hpp"
#elif defined (__AVR_ATmega32U4__)
#  include "arch/avr/mach-m32u4.hpp"
#elif defined (__AVR_ATmega32U6__)
#  include "arch/avr/mach-m32u6.hpp"
#elif defined (__AVR_ATmega64C1__)
#  include "arch/avr/mach-m64c1.hpp"
#elif defined (__AVR_ATmega64M1__)
#  include "arch/avr/mach-m64m1.hpp"
#elif defined (__AVR_ATmega128__)
#  include "arch/avr/mach-m128.hpp"
#elif defined (__AVR_ATmega1280__)
#  include "arch/avr/mach-m1280.hpp"
#elif defined (__AVR_ATmega1281__)
#  include "arch/avr/mach-m1281.hpp"
#elif defined (__AVR_ATmega1284P__)
#  include "arch/avr/mach-m1284p.hpp"
#elif defined (__AVR_ATmega128RFA1__)
#  include "arch/avr/mach-m128rfa1.hpp"
#elif defined (__AVR_ATmega2560__)
#  include "arch/avr/mach-m2560.hpp"
#elif defined (__AVR_ATmega2561__)
#  include "arch/avr/mach-m2561.hpp"
#elif defined (__AVR_AT90CAN32__)
#  include "arch/avr/mach-can32.hpp"
#elif defined (__AVR_AT90CAN64__)
#  include "arch/avr/mach-can64.hpp"
#elif defined (__AVR_AT90CAN128__)
#  include "arch/avr/mach-can128.hpp"
#elif defined (__AVR_AT90USB82__)
#  include "arch/avr/mach-usb82.hpp"
#elif defined (__AVR_AT90USB162__)
#  include "arch/avr/mach-usb162.hpp"
#elif defined (__AVR_AT90USB646__)
#  include "arch/avr/mach-usb646.hpp"
#elif defined (__AVR_AT90USB647__)
#  include "arch/avr/mach-usb647.hpp"
#elif defined (__AVR_AT90USB1286__)
#  include "arch/avr/mach-usb1286.hpp"
#elif defined (__AVR_AT90USB1287__)
#  include "arch/avr/mach-usb1287.hpp"
#elif defined (__AVR_ATmega64__)
#  include "arch/avr/mach-m64.hpp"
#elif defined (__AVR_ATmega640__)
#  include "arch/avr/mach-m640.hpp"
#elif defined (__AVR_ATmega644__) || defined (__AVR_ATmega644A__)
#  include "arch/avr/mach-m644.hpp"
#elif defined (__AVR_ATmega644P__)
#  include "arch/avr/mach-m644p.hpp"
#elif defined (__AVR_ATmega644PA__)
#  include "arch/avr/mach-m644pa.hpp"
#elif defined (__AVR_ATmega645__) || defined (__AVR_ATmega645A__) || defined (__AVR_ATmega645P__)
#  include "arch/avr/mach-m645.hpp"
#elif defined (__AVR_ATmega6450__) || defined (__AVR_ATmega6450A__) || defined (__AVR_ATmega6450P__)
#  include "arch/avr/mach-m6450.hpp"
#elif defined (__AVR_ATmega649__) || defined (__AVR_ATmega649A__)
#  include "arch/avr/mach-m649.hpp"
#elif defined (__AVR_ATmega6490__) || defined (__AVR_ATmega6490A__) || defined (__AVR_ATmega6490P__)
#  include "arch/avr/mach-m6490.hpp"
#elif defined (__AVR_ATmega649P__)
#  include "arch/avr/mach-m649p.hpp"
#elif defined (__AVR_ATmega64HVE__)
#  include "arch/avr/mach-m64hve.hpp"
#elif defined (__AVR_ATmega103__)
#  include "arch/avr/mach-m103.hpp"
#elif defined (__AVR_ATmega32__)
#  include "arch/avr/mach-m32.hpp"
#elif defined (__AVR_ATmega323__)
#  include "arch/avr/mach-m323.hpp"
#elif defined (__AVR_ATmega324P__) || defined (__AVR_ATmega324A__)
#  include "arch/avr/mach-m324.hpp"
#elif defined (__AVR_ATmega324PA__)
#  include "arch/avr/mach-m324pa.hpp"
#elif defined (__AVR_ATmega325__) || defined (__AVR_ATmega325A__)
#  include "arch/avr/mach-m325.hpp"
#elif defined (__AVR_ATmega325P__)
#  include "arch/avr/mach-m325.hpp"
#elif defined (__AVR_ATmega3250__) || defined (__AVR_ATmega3250A__)
#  include "arch/avr/mach-m3250.hpp"
#elif defined (__AVR_ATmega3250P__)
#  include "arch/avr/mach-m3250.hpp"
#elif defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
#  include "arch/avr/mach-m328p.hpp"
#elif defined (__AVR_ATmega329__) || defined (__AVR_ATmega329A__)
#  include "arch/avr/mach-m329.hpp"
#elif defined (__AVR_ATmega329P__) || defined (__AVR_ATmega329PA__)
#  include "arch/avr/mach-m329.hpp"
#elif defined (__AVR_ATmega3290__) || defined (__AVR_ATmega3290A__)
#  include "arch/avr/mach-m3290.hpp"
#elif defined (__AVR_ATmega3290P__)
#  include "arch/avr/mach-m3290.hpp"
#elif defined (__AVR_ATmega32HVB__)
#  include "arch/avr/mach-m32hvb.hpp"
#elif defined (__AVR_ATmega32HVBREVB__)
#  include "arch/avr/mach-m32hvbrevb.hpp"
#elif defined (__AVR_ATmega406__)
#  include "arch/avr/mach-m406.hpp"
#elif defined (__AVR_ATmega16__)
#  include "arch/avr/mach-m16.hpp"
#elif defined (__AVR_ATmega16A__)
#  include "arch/avr/mach-m16a.hpp"
#elif defined (__AVR_ATmega161__)
#  include "arch/avr/mach-m161.hpp"
#elif defined (__AVR_ATmega162__)
#  include "arch/avr/mach-m162.hpp"
#elif defined (__AVR_ATmega163__)
#  include "arch/avr/mach-m163.hpp"
#elif defined (__AVR_ATmega164P__) || defined (__AVR_ATmega164A__)
#  include "arch/avr/mach-m164.hpp"
#elif defined (__AVR_ATmega165__) || defined (__AVR_ATmega165A__)
#  include "arch/avr/mach-m165.hpp"
#elif defined (__AVR_ATmega165P__)
#  include "arch/avr/mach-m165p.hpp"
#elif defined (__AVR_ATmega168__) || defined (__AVR_ATmega168A__)
#  include "arch/avr/mach-m168.hpp"
#elif defined (__AVR_ATmega168P__)
#  include "arch/avr/mach-m168p.hpp"
#elif defined (__AVR_ATmega169__) || defined (__AVR_ATmega169A__)
#  include "arch/avr/mach-m169.hpp"
#elif defined (__AVR_ATmega169P__)
#  include "arch/avr/mach-m169p.hpp"
#elif defined (__AVR_ATmega169PA__)
#  include "arch/avr/mach-m169pa.hpp"
#elif defined (__AVR_ATmega8HVA__)
#  include "arch/avr/mach-m8hva.hpp"
#elif defined (__AVR_ATmega16HVA__)
#  include "arch/avr/mach-m16hva.hpp"
#elif defined (__AVR_ATmega16HVA2__)
#  include "arch/avr/mach-m16hva2.hpp"
#elif defined (__AVR_ATmega16HVB__)
#  include "arch/avr/mach-m16hvb.hpp"
#elif defined (__AVR_ATmega16HVBREVB__)
#  include "arch/avr/mach-m16hvbrevb.hpp"
#elif defined (__AVR_ATmega8__)
#  include "arch/avr/mach-m8.hpp"
#elif defined (__AVR_ATmega48__) || defined (__AVR_ATmega48A__)
#  include "arch/avr/mach-m48.hpp"
#elif defined (__AVR_ATmega48P__)
#  include "arch/avr/mach-iom48p.hpp"
#elif defined (__AVR_ATmega88__) || defined (__AVR_ATmega88A__)
#  include "arch/avr/mach-m88.hpp"
#elif defined (__AVR_ATmega88P__)
#  include "arch/avr/mach-iom88p.hpp"
#elif defined (__AVR_ATmega88PA__)
#  include "arch/avr/mach-iom88pa.hpp"
#elif defined (__AVR_ATmega8515__)
#  include "arch/avr/mach-iom8515.hpp"
#elif defined (__AVR_ATmega8535__)
#  include "arch/avr/mach-iom8535.hpp"
#elif defined (__AVR_AT90S8535__)
#  include "arch/avr/mach-io8535.hpp"
#elif defined (__AVR_AT90C8534__)
#  include "arch/avr/mach-io8534.hpp"
#elif defined (__AVR_AT90S8515__)
#  include "arch/avr/mach-io8515.hpp"
#elif defined (__AVR_AT90S4434__)
#  include "arch/avr/mach-4434.hpp"
#elif defined (__AVR_AT90S4433__)
#  include "arch/avr/mach-4433.hpp"
#elif defined (__AVR_AT90S4414__)
#  include "arch/avr/mach-4414.hpp"
#elif defined (__AVR_ATtiny22__)
#  include "arch/avr/mach-tn22.hpp"
#elif defined (__AVR_ATtiny26__)
#  include "arch/avr/mach-tn26.hpp"
#elif defined (__AVR_AT90S2343__)
#  include "arch/avr/mach-2343.hpp"
#elif defined (__AVR_AT90S2333__)
#  include "arch/avr/mach-2333.hpp"
#elif defined (__AVR_AT90S2323__)
#  include "arch/avr/mach-2323.hpp"
#elif defined (__AVR_AT90S2313__)
#  include "arch/avr/mach-2313.hpp"
#elif defined (__AVR_ATtiny4__)
#  include "arch/avr/mach-tn4.hpp"
#elif defined (__AVR_ATtiny5__)
#  include "arch/avr/mach-tn5.hpp"
#elif defined (__AVR_ATtiny9__)
#  include "arch/avr/mach-tn9.hpp"
#elif defined (__AVR_ATtiny10__)
#  include "arch/avr/mach-tn10.hpp"
#elif defined (__AVR_ATtiny20__)
#  include "arch/avr/mach-tn20.hpp"
#elif defined (__AVR_ATtiny40__)
#  include "arch/avr/mach-tn40.hpp"
#elif defined (__AVR_ATtiny2313__)
#  include "arch/avr/mach-tn2313.hpp"
#elif defined (__AVR_ATtiny2313A__)
#  include "arch/avr/mach-tn2313a.hpp"
#elif defined (__AVR_ATtiny13__)
#  include "arch/avr/mach-tn13.hpp"
#elif defined (__AVR_ATtiny13A__)
#  include "arch/avr/mach-tn13a.hpp"
#elif defined (__AVR_ATtiny25__)
#  include "arch/avr/mach-tn25.hpp"
#elif defined (__AVR_ATtiny4313__)
#  include "arch/avr/mach-tn4313.hpp"
#elif defined (__AVR_ATtiny45__)
#  include "arch/avr/mach-tn45.hpp"
#elif defined (__AVR_ATtiny85__)
#  include "arch/avr/mach-tn85.hpp"
#elif defined (__AVR_ATtiny24__)
#  include "arch/avr/mach-tn24.hpp"
#elif defined (__AVR_ATtiny24A__)
#  include "arch/avr/mach-tn24a.hpp"
#elif defined (__AVR_ATtiny44__)
#  include "arch/avr/mach-tn44.hpp"
#elif defined (__AVR_ATtiny44A__)
#  include "arch/avr/mach-tn44a.hpp"
#elif defined (__AVR_ATtiny84__)
#  include "arch/avr/mach-tn84.hpp"
#elif defined (__AVR_ATtiny84A__)
#  include "arch/avr/mach-tn84a.hpp"  
#elif defined (__AVR_ATtiny261__)
#  include "arch/avr/mach-tn261.hpp"
#elif defined (__AVR_ATtiny261A__)
#  include "arch/avr/mach-tn261a.hpp"
#elif defined (__AVR_ATtiny461__)
#  include "arch/avr/mach-tn461.hpp"
#elif defined (__AVR_ATtiny461A__)
#  include "arch/avr/mach-tn461a.hpp"
#elif defined (__AVR_ATtiny861__)
#  include "arch/avr/mach-tn861.hpp"
#elif defined (__AVR_ATtiny861A__)
#  include "arch/avr/mach-tn861a.hpp"
#elif defined (__AVR_ATtiny43U__)
#  include "arch/avr/mach-tn43u.hpp"
#elif defined (__AVR_ATtiny48__)
#  include "arch/avr/mach-tn48.hpp"
#elif defined (__AVR_ATtiny88__)
#  include "arch/avr/mach-tn88.hpp"
#elif defined (__AVR_ATtiny87__)
#  include "arch/avr/mach-tn87.hpp"
#elif defined (__AVR_ATtiny167__)
#  include "arch/avr/mach-tn167.hpp"
#elif defined (__AVR_AT90SCR100__)
#  include "arch/avr/mach-90scr100.hpp"
#elif defined (__AVR_ATxmega16A4__)
#  include "arch/avr/mach-x16a4.hpp"
#elif defined (__AVR_ATxmega16D4__)
#  include "arch/avr/mach-x16d4.hpp"
#elif defined (__AVR_ATxmega32A4__)
#  include "arch/avr/mach-x32a4.hpp"
#elif defined (__AVR_ATxmega32D4__)
#  include "arch/avr/mach-x32d4.hpp"
#elif defined (__AVR_ATxmega64A1__)
#  include "arch/avr/mach-x64a1.hpp"
#elif defined (__AVR_ATxmega64A1U__)
#  include "arch/avr/mach-x64a1u.hpp"
#elif defined (__AVR_ATxmega64A3__)
#  include "arch/avr/mach-x64a3.hpp"
#elif defined (__AVR_ATxmega64D3__)
#  include "arch/avr/mach-x64d3.hpp"
#elif defined (__AVR_ATxmega128A1__)
#  include "arch/avr/mach-x128a1.hpp"
#elif defined (__AVR_ATxmega128A1U__)
#  include "arch/avr/mach-x128a1u.hpp"
#elif defined (__AVR_ATxmega128A3__)
#  include "arch/avr/mach-x128a3.hpp"
#elif defined (__AVR_ATxmega128D3__)
#  include "arch/avr/mach-x128d3.hpp"
#elif defined (__AVR_ATxmega192A3__)
#  include "arch/avr/mach-x192a3.hpp"
#elif defined (__AVR_ATxmega192D3__)
#  include "arch/avr/mach-x192d3.hpp"
#elif defined (__AVR_ATxmega256A3__)
#  include "arch/avr/mach-x256a3.hpp"
#elif defined (__AVR_ATxmega256A3B__)
#  include "arch/avr/mach-x256a3b.hpp"
#elif defined (__AVR_ATxmega256D3__)
#  include "arch/avr/mach-x256d3.hpp"
#elif defined (__AVR_ATA6289__)
#  include "arch/avr/mach-a6289.hpp"
/* avr1: the following only supported for assembler programs */
#elif defined (__AVR_ATtiny28__)
#  include "arch/avr/mach-tn28.hpp"
#elif defined (__AVR_AT90S1200__)
#  include "arch/avr/mach-1200.hpp"
#elif defined (__AVR_ATtiny15__)
#  include "arch/avr/mach-tn15.hpp"
#elif defined (__AVR_ATtiny12__)
#  include "arch/avr/mach-tn12.hpp"
#elif defined (__AVR_ATtiny11__)
#  include "arch/avr/mach-tn11.hpp"
#elif defined (__AVR_M3000__)
#  include "arch/avr/mach-m3000.hpp"
#else
#  if !defined(__COMPILING_AVR_LIBC__)
#    warning "device type not defined"
#  endif
#endif


#endif
