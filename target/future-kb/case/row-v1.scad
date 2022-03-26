$fn       =200;

HEIGHT    = 19;
THICK     = 3;
SS        = 17; // (Horizontal) Area occupied by the switch - compact placement, for keycaps 17.7 x 16.7
SH        = 9;  // (Vertical)   Area occupied by the switch and keycap

// P: point
// A: angle
//
//
//    PS                          P2                                      P3                                        PF
//    *-------------------------*                                            *-------------------------------------*
//                               \                                         _/
//                                \                                   P31_*
//    *--------------------\       * P20                    A1         _/         *--------------------------------*
//    PBS             PB2   \       \                            P13 _*         _/|  PB3                           PBF
//                         | \       \         A0                  _/         _/  |
//                         |  \       \                       ____* P1      _/ A31|
//                         |   \       * P02             ____*            _/ A13  |
//                         |A20 \       \       *   ____/   P10          *  PB13 ------------
//                         |     \       \     __*/             ____*         
//                         |      \       \_/    P01       ____/    |  PB10
//                                 \       *          ____/      A10|
//                              A02 \     P0    _____/     A01      |
//                         __________*       *_____________________ 
//
//                                  PB02       PB01
//

A20         = 30;
A02         = 90 - A20;
A01         = 20;
A10         = 90 - A01;
A13         = 40;

A0          = 180 - A02 - A01;
A1          = 180 - (A13 - A01);

D_P0        = SH / tan(A0/2);       // distance from P0 to any switch cutout
D_P1        = SH / tan(A1/2);       // distance from P0 to any switch cutout

P0_X        = 0;
P0_Y        = 0;

P02_X       = P0_X - D_P0*sin(A20);
P02_Y       = P0_Y + D_P0*cos(A20);

PB02_X      = P0_X - THICK*cos(A20);
PB02_Y      = P0_Y - THICK*sin(A20);

outline_points = concat(
[ [P0_X,    P0_Y    ] ],
[ [P02_X,   P02_Y   ] ],
[ [PB02_X,  PB02_Y  ] ]
);

module raw_part() {
  linear_extrude(height = HEIGHT) polygon(outline_points);
}

raw_part();
