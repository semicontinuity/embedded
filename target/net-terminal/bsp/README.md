// Ports
//
// PA - mt12864 data bus
// PB - keyboard
// PC
//   PC0  A0				OUT
//   PC1  RES				OUT
//   PC2  BT1				IN, int. pull up
//   PC3  BT2				IN, int. pull up
//   PC4  BT3				IN, int. pull up
//   PC5  BT4				IN, int. pull up
//   PC6  E1(was switched) = CS1	OUT
//   PC7  E2(was switched) = CS2	OUT
// PD
//   PD0  txd				OUT (future)
//   PD1  rxd				IN  (future)  int. pull up
//   PD2  STATE_CHANGE			OUT
//   PD3  (INT1) ALARM_STATE		IN  
//   PD4  LED				OUT
//   PD5  RD/WR				OUT
//   PD6  E				OUT
//   PD7  BACKLIGHT			OUT


//                                       +--------+
//                                   PD7 |21    20| PD6
//                                   PC0 |22    19| PD5
//                                   PC1 |23    18| PD4    x-[]--x  armed LED, out
//                                   PC2 |24    17| PD3    x-[]--x  alarm state, in
//                                   PC3 |25    16| PD2    x--##-x  state change, out
//                                   PC4 |26    15| PD1      -##
//                                   PC5 |27    14| PD0
//                                   PC6 |28    13| xtal1
//                                   PC7 |29    12| xtal2
//                                  AVCC |30    11| GND
//                                   GND |31    10| VCC
//                                  AREF |32     9| RESET
//                                   PA7 |33     8| PB7
//                                       |34     7|
//                                       |35     6|
//                                       |36     5|
//                                       |37     4|
//                                       |38     3|
//                                       |39     2|
//                                   PA0 |40  O  1| PB0
//                                       +--------+
//                                         +----+
//                                         |    |
//                                         +----+
//                                         AVR ISP
