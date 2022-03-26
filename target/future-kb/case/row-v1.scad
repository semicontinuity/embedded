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
//                            A2 \                                         _/ A3
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
A2          = 180 - A02;

D_P0        = SH / tan(A0/2);       // distance from P0 to any switch cutout
D_P1        = SH / tan(A1/2);       // distance from P1 to any switch cutout

P0_X        = 0;
P0_Y        = 0;

P02_X       = P0_X - D_P0*sin(A20);
P02_Y       = P0_Y + D_P0*cos(A20);
P20_X       = P02_X - SS*sin(A20);
P20_Y       = P02_Y + SS*cos(A20);
P2_X        = P20_X - 3*sin(A20); // temp
P2_Y        = P20_Y + 3*cos(A20); // temp

PS_X        = P2_X - 15; // temp
PS_Y        = P2_Y; 

PBS_X       = PS_X;
PBS_Y       = PS_Y - THICK; 

PB2_X       = P2_X - THICK/tan(A2/2);
PB2_Y       = PBS_Y;

PB02_X      = P0_X - THICK*cos(A20);
PB02_Y      = P0_Y - THICK*sin(A20);

PB01_X      = P0_X + THICK*sin(A01);
PB01_Y      = P0_Y - THICK*cos(A01);

P01_X       = P0_X + D_P0*cos(A01);
P01_Y       = P0_Y + D_P0*sin(A01);

P10_X       = P01_X + SS*cos(A01);
P10_Y       = P01_Y + SS*sin(A01);

P1_X        = P10_X + D_P1*cos(A01);
P1_Y        = P10_Y + D_P1*sin(A01);

P13_X       = P1_X + D_P1*cos(A13);
P13_Y       = P1_Y + D_P1*sin(A13);
P31_X       = P13_X + SS*cos(A13);
P31_Y       = P13_Y + SS*sin(A13);
P3_X        = P31_X + 4*cos(A13);
P3_Y        = P31_Y + 4*sin(A13);

PF_X        = P3_X + 15;
PF_Y        = P3_Y;
PBF_X       = PF_X;
PBF_Y       = PF_Y - THICK;

PB3_X       = P3_X;
//PB3_X       = P3_X + THICK/tan(A3/2);
PB3_Y       = PBF_Y;

PB10_X      = P1_X + THICK*sin(A01);
PB10_Y      = P1_Y - THICK*cos(A01);

PB13_X      = P1_X + THICK*sin(A13);
PB13_Y      = P1_Y - THICK*cos(A13);

outline_points = concat(
[ [PB3_X,   PB3_Y   ] ],
[ [PBF_X,   PBF_Y   ] ],
[ [PF_X,    PF_Y    ] ],
[ [P3_X,    P3_Y    ] ],
[ [P1_X,    P1_Y    ] ],
[ [P0_X,    P0_Y    ] ],
[ [P2_X,    P2_Y    ] ],
[ [PS_X,    PS_Y    ] ],
[ [PBS_X,   PBS_Y   ] ],
[ [PB2_X,   PB2_Y   ] ],
[ [PB02_X,  PB02_Y  ] ],
[ [PB01_X,  PB01_Y  ] ],
[ [PB10_X,  PB10_Y  ] ],
[ [PB13_X,  PB13_Y  ] ]
);

module raw_part() {
  linear_extrude(height = HEIGHT) polygon(outline_points);
}

raw_part();
