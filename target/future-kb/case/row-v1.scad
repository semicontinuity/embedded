$fn       =200;

HEIGHT    = 19;
THICK     = 3;
PLATE     = 1.8;
DIG       = THICK - PLATE;

SW_M_S    = 14; // Switch mount size is 14x14 mm
SW_M_SPC  = 15; // Switch mount size is 14x14 mm + 0.5 mm space

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
//                         |  \  PCA  \                       ____* P1      _/ A31|
//                         |   \       * P02             ____*            _/ A13  |
//                         |A20 \       \       *   ____/   P10          *  PB13 ------------
//                         |     \       \     __*/             ____*         
//                         |      \       \_/    P01       ____/    |  PB10
//                                 \       *          ____/      A10|
//                              A02 \     P0    _____/     A01      |
//                         __________*   *   *_____________________ 
//                                        
//                                  PB02 PB00  PB01
//

WIDTH       = 114;
MOUNT_WIDTH = 90;
TOP_Y       = 24;

A20         = 30;
A02         = 90 - A20;
A01         = 20;
A10         = 90 - A01;
A13         = 40;
A31         = 90 - A13;

A0          = 180 - A02 - A01;
A1          = 180 - (A13 - A01);
A2          = 180 - A02;
A3          = 180 - A13;

D_P0        = SH / tan(A0/2);       // distance from P0 to any switch cutout
D_P1        = SH / tan(A1/2);       // distance from P1 to any switch cutout

P0_X        = 0;
P0_Y        = 0;

P02_X       = P0_X - D_P0*sin(A20);
P02_Y       = P0_Y + D_P0*cos(A20);
P20_X       = P02_X - SS*sin(A20);
P20_Y       = P02_Y + SS*cos(A20);
P2_Y        = TOP_Y;
P2_X        = P20_X - (P2_Y-P20_Y)*tan(A20);

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
P3_Y        = TOP_Y;
P3_X        = P31_X + (P3_Y-P31_Y)*tan(A31);
// =========================================================================
D_P2_P3     = P3_X - P2_X;
EXTRA_X     = (WIDTH - D_P2_P3) / 2;

PS_X        = P2_X - EXTRA_X;
PS_Y        = TOP_Y; 

PBS_X       = PS_X;
PBS_Y       = PS_Y - THICK; 

PB2_X       = P2_X - THICK/tan(A2/2);
PB2_Y       = PBS_Y;

PF_X        = P3_X + EXTRA_X;
PF_Y        = TOP_Y;
PBF_X       = PF_X;
PBF_Y       = PF_Y - THICK;

PB3_X       = P3_X + THICK/tan(A3/2);
PB3_Y       = PBF_Y;

TOP_X       = (PS_X + PF_X)/2;
// =========================================================================

PB02_X      = P0_X - THICK*cos(A20);
PB02_Y      = P0_Y - THICK*sin(A20);

PB01_X      = P0_X + THICK*sin(A01);
PB01_Y      = P0_Y - THICK*cos(A01);

PB00_X      = 0.66*(PB02_X + PB01_X) - P0_X;
PB00_Y      = 0.66*(PB02_Y + PB01_Y) - P0_Y;

PB10_X      = P1_X + THICK*sin(A01);
PB10_Y      = P1_Y - THICK*cos(A01);

PB13_X      = P1_X + THICK*sin(A13);
PB13_Y      = P1_Y - THICK*cos(A13);


PCA_X       = (P02_X + P20_X)/2; // center of switch A cutout
PCA_Y       = (P02_Y + P20_Y)/2; // center of switch A cutout
PCB_X       = (P01_X + P10_X)/2; // center of switch B cutout
PCB_Y       = (P01_Y + P10_Y)/2; // center of switch B cutout
PCC_X       = (P13_X + P31_X)/2; // center of switch C cutout
PCC_Y       = (P13_Y + P31_Y)/2; // center of switch C cutout


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
[ [PB00_X,  PB00_Y  ] ],
[ [PB01_X,  PB01_Y  ] ],
[ [PB10_X,  PB10_Y  ] ],
[ [PB13_X,  PB13_Y  ] ]
);

module raw_part() {
  translate([0, 0, -HEIGHT/2])
  linear_extrude(height = HEIGHT) polygon(outline_points);
}


module switch_cutout() {
  union() {  
    rotate([90, 0, 0])
    color("red")
    cube([SW_M_S, SW_M_S, THICK*3], center=true);

    rotate([-90, 0, 0])
    color("red")
    translate([0, 0, -DIG/2 - PLATE]) 
    cube([SW_M_SPC, SW_M_SPC, DIG], center=true);
  }
}

module mounting_cutout() { 
  color("red")
  rotate([90, 0, 0])
  linear_extrude(height = THICK*2) offset(r=1.5) polygon([ [-5, -0.1], [-5, 0.1], [5, 0.1], [5, -0.1] ]);
}


module part() {
  difference() {
    raw_part();   
    
    translate([PCA_X, PCA_Y, 0]) rotate([0, 0, -A02]) switch_cutout();
    translate([PCB_X, PCB_Y, 0]) rotate([0, 0, +A01]) switch_cutout();
    translate([PCC_X, PCC_Y, 0]) rotate([0, 0, +A13]) switch_cutout();
    
    translate([TOP_X - MOUNT_WIDTH/2, TOP_Y, 0]) mounting_cutout();
    translate([TOP_X + MOUNT_WIDTH/2, TOP_Y, 0]) mounting_cutout();
  }
}

part();
