// See Kailh Choc dimensions at https://keycapsss.com/media/image/12/7a/49/kailh-choc-switch-low-profile-dimensions.png

$fn         = 72;

WIDTH       = 114-2;
MOUNT_WIDTH = 90;
SPACING     = 80;

HEIGHT      = 18;
THICK       = 4;
PLATE       = 1.8;
DIG         = THICK - PLATE;

SW_M_S      = 13.9; // Switch mount size is 13.8x13.8 mm
SW_M_SPC    = 14.6; // Space, occupied by switch legs (14.5mm + 0.1mm leeway)

SS          = 16.8; // (Horizontal) Area occupied by the switch - compact placement, for keycaps 17.7 x 16.7
SH          = 8;  // (Vertical)   Area occupied by the switch and keycap

EPS         = 0.00001;
// =======================================================================================================
SW_CO_LEN         = 2.2;    // body is sinked 2.3 mm deep (2.2 mm on drawing)
SW_CO_REST_LEN    = THICK - SW_CO_LEN;

SW_CO_CENT_STEM_R = 3.4/2;  // central stem is 3.2 mm diam.
SW_CO_SIDE_STEM_R = 2.0/2;  // side stem is 3.2 mm diam.
SW_CO_SIDE_OFS    = 5;      // side stem is 5 off center.

SW_CO_LOCK_CAVITY_W  = 3.4;
SW_CO_LOCK_CAVITY_H  = 1.2;
SW_CO_LOCK_CAVITY_D  = 1.2;    // 0.9 mm on drawing
SW_CO_LOCK_CAVITY_DX = 7;
SW_CO_LOCK_CAVITY_DY = SW_M_S + SW_CO_LOCK_CAVITY_H;
SW_CO_LOCK_CAVITY_OFS_Z = -SW_CO_LEN + SW_CO_LOCK_CAVITY_D/2; 

SW_CO_CENT_PIN_DX    = 5.9;  // central pin is 5.9 mm off center.
SW_CO_CENT_PIN_DY    = 0;
SW_CO_SIDE_PIN_DX    = 3.8;  // side pin is 3.8 mm off center.
SW_CO_SIDE_PIN_DY    = 5;  // side pin is 5 mm down center.
SW_CO_PIN_HOLE_R     = 3/2;  // appx R of hot-swap pin housing

// =======================================================================================================
PAD_THICK   = 0;    // test values: 0, 2, 4, 6 
//PAD_WIDTH   = 19;
PAD_WIDTH   = 25;

PAD_OFFSET  = (WIDTH - PAD_WIDTH)/2;
// =======================================================================================================
MOUNT_D = THICK + PAD_THICK;
//MOUNT_H = 13.1;        // rounded rect; height
MOUNT_H = HEIGHT;

MOUNT_W = PAD_WIDTH;   // rounded rect; width
MOUNT_R = 3;           // rounded rect; radius
MOUNT_BASE_W = MOUNT_W/2 - MOUNT_R;
MOUNT_BASE_H = MOUNT_H/2 - MOUNT_R;
// =======================================================================================================
MOUNT_CUT_H = 3.1;  // rounded rect; height
MOUNT_CUT_R = 1.5;  // rounded rect; radius

MOUNT_CUT_D = THICK + PAD_THICK;
//MOUNT_CUT_W = 13;                      // rounded rect; width
MOUNT_CUT_W = MOUNT_W - 3*MOUNT_CUT_R;   // rounded rect; width

MOUNT_CUT_BASE_W = MOUNT_CUT_W/2 - MOUNT_CUT_R;
MOUNT_CUT_BASE_H = MOUNT_CUT_H/2 - MOUNT_CUT_R;

MOUNT_CUT_HOLES = 6;
MOUNT_CUT_PITCH = (MOUNT_CUT_W - MOUNT_CUT_HOLES*2*MOUNT_CUT_R) / (MOUNT_CUT_HOLES - 1);
MOUNT_CUT_DX = (MOUNT_CUT_PITCH + 2*MOUNT_CUT_R)/2;

// =======================================================================================================
MX = 3*MOUNT_W/4;  // mount margin


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
TOP_Y       = 24;
TOP_CENT_Y  = TOP_Y - THICK/2;

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

CENTER_X    = (PS_X + PF_X)/2;
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


PCA_X       = (P02_X + P20_X)/2; // center of switch A cutout on top surface
PCA_Y       = (P02_Y + P20_Y)/2; // center of switch A cutout on top surface
PCB_X       = (P01_X + P10_X)/2; // center of switch B cutout on top surface
PCB_Y       = (P01_Y + P10_Y)/2; // center of switch B cutout on top surface
PCC_X       = (P13_X + P31_X)/2; // center of switch C cutout on top surface
PCC_Y       = (P13_Y + P31_Y)/2; // center of switch C cutout on top surface


outline_points = concat(
[ [PB3_X,      PB3_Y   ] ],
[ [PBF_X - MX, PBF_Y   ] ],
[ [PF_X  - MX, PF_Y    ] ],
[ [P3_X,       P3_Y    ] ],
[ [P1_X,       P1_Y    ] ],
[ [P0_X,       P0_Y    ] ],
[ [P2_X,       P2_Y    ] ],
[ [PS_X  + MX, PS_Y    ] ],
[ [PBS_X + MX, PBS_Y   ] ],
[ [PB2_X,      PB2_Y   ] ],
[ [PB02_X,     PB02_Y  ] ],
[ [PB00_X,     PB00_Y  ] ],
[ [PB01_X,     PB01_Y  ] ],
[ [PB10_X,     PB10_Y  ] ],
[ [PB13_X,     PB13_Y  ] ]
);

module pad() {
  translate([0, TOP_Y - THICK - PAD_THICK/2, 0])
  color("blue") cube([PAD_WIDTH, PAD_THICK, HEIGHT], center=true);
}

module pad_left() {
  translate([CENTER_X - PAD_OFFSET, 0, 0]) pad();
}

module pad_right() {
  translate([CENTER_X + PAD_OFFSET, 0, 0]) pad();
}


module mount() { 
  color("orange")
  rotate([90, 0, 0])
  linear_extrude(height = MOUNT_D) offset(r=MOUNT_R)
  polygon([
    [-MOUNT_BASE_W, -MOUNT_BASE_H],
    [-MOUNT_BASE_W, +MOUNT_BASE_H],
    [+MOUNT_BASE_W, +MOUNT_BASE_H],
    [+MOUNT_BASE_W, -MOUNT_BASE_H]
  ]);
}

module mount_left() {
  translate([CENTER_X - PAD_OFFSET, TOP_Y, 0]) mount();
}

module mount_right() {
  translate([CENTER_X + PAD_OFFSET, TOP_Y, 0]) mount();
}


module raw_part() {
  union() {
    translate([0, 0, -HEIGHT/2]) linear_extrude(height = HEIGHT) polygon(outline_points);
    mount_left();
    mount_right();
    
   /*
    color("cyan") translate([PCA_X, PCA_Y, 0]) rotate([0, 0, -A02]) switch_cutout();
    color("cyan") translate([PCB_X, PCB_Y, 0]) rotate([0, 0, +A01]) switch_cutout();
    color("cyan") translate([PCC_X, PCC_Y, 0]) rotate([0, 0, +A13]) switch_cutout();
   */ 
  }
}


module switch_co_bottom() {
  translate([0, -SW_CO_LEN/2, 0])
  cube([SW_M_S, SW_CO_LEN + EPS, SW_M_S], center=true);
}

module switch_co_center_stem() {
  rotate([-90, 0, 0])
  translate([0, 0, -THICK + SW_CO_REST_LEN/2])
  cylinder(h=SW_CO_REST_LEN+EPS, r1=SW_CO_CENT_STEM_R, r2=SW_CO_CENT_STEM_R, center=true);
}

module switch_co_side_stem() {
  rotate([-90, 0, 0])
  translate([0, 0, -THICK + SW_CO_REST_LEN/2])
  cylinder(h=SW_CO_REST_LEN+EPS, r1=SW_CO_SIDE_STEM_R, r2=SW_CO_SIDE_STEM_R, center=true);
}


module switch_co_pin() {
  rotate([-90, 0, 0])
  translate([0, 0, -THICK + SW_CO_REST_LEN/2])
  cylinder(h=SW_CO_REST_LEN+EPS, r1=SW_CO_PIN_HOLE_R, r2=SW_CO_PIN_HOLE_R, center=true);
}

module switch_co_leg_cavity() {
  translate([0, SW_CO_LOCK_CAVITY_OFS_Z, 0])
  color("blue") cube([SW_CO_LOCK_CAVITY_W, SW_CO_LOCK_CAVITY_D, SW_CO_LOCK_CAVITY_H], center=true);
}



module switch_cutout() {
  union() {  
    switch_co_bottom();

    switch_co_center_stem();
    translate([0, 0, +SW_CO_SIDE_OFS]) switch_co_side_stem();
    translate([0, 0, -SW_CO_SIDE_OFS]) switch_co_side_stem();

    translate([+SW_CO_SIDE_PIN_DX, 0, +SW_CO_SIDE_PIN_DY]) switch_co_pin();

    translate([-SW_CO_LOCK_CAVITY_DX/2, 0, -SW_CO_LOCK_CAVITY_DY/2]) switch_co_leg_cavity();
    translate([-SW_CO_LOCK_CAVITY_DX/2, 0, +SW_CO_LOCK_CAVITY_DY/2]) switch_co_leg_cavity();
    translate([+SW_CO_LOCK_CAVITY_DX/2, 0, -SW_CO_LOCK_CAVITY_DY/2]) switch_co_leg_cavity();
    translate([+SW_CO_LOCK_CAVITY_DX/2, 0, +SW_CO_LOCK_CAVITY_DY/2]) switch_co_leg_cavity();
  }
}

/*
module mounting_cutout() { 
  color("red")
  rotate([90, 0, 0])
  linear_extrude(height = MOUNT_CUT_D) offset(r=MOUNT_CUT_R)
  polygon([
    [-MOUNT_CUT_BASE_W, -MOUNT_CUT_BASE_H],
    [-MOUNT_CUT_BASE_W, MOUNT_CUT_BASE_H],
    [MOUNT_CUT_BASE_W, MOUNT_CUT_BASE_H],
    [MOUNT_CUT_BASE_W, -MOUNT_CUT_BASE_H]
  ]);
}
*/

module mounting_cutout() { 
  color("red")
  rotate([-90, 0, 0])
  union() {
    translate([-1*MOUNT_CUT_DX, 0, -THICK/2]) cylinder(h=THICK+EPS, r1=MOUNT_CUT_R, r2=MOUNT_CUT_R, center=true);
    translate([+1*MOUNT_CUT_DX, 0, -THICK/2]) cylinder(h=THICK+EPS, r1=MOUNT_CUT_R, r2=MOUNT_CUT_R, center=true);
  
    translate([-3*MOUNT_CUT_DX, 0, -THICK/2]) cylinder(h=THICK+EPS, r1=MOUNT_CUT_R, r2=MOUNT_CUT_R, center=true);
    translate([+3*MOUNT_CUT_DX, 0, -THICK/2]) cylinder(h=THICK+EPS, r1=MOUNT_CUT_R, r2=MOUNT_CUT_R, center=true);
    
    translate([-5*MOUNT_CUT_DX, 0, -THICK/2]) cylinder(h=THICK+EPS, r1=MOUNT_CUT_R, r2=MOUNT_CUT_R, center=true);
    translate([+5*MOUNT_CUT_DX, 0, -THICK/2]) cylinder(h=THICK+EPS, r1=MOUNT_CUT_R, r2=MOUNT_CUT_R, center=true);
  }
}


module part() {
  difference() {
    raw_part();

    translate([PCA_X, PCA_Y, 0]) rotate([0, 0, -A02]) switch_cutout();
    translate([PCB_X, PCB_Y, 0]) rotate([0, 0, +A01]) switch_cutout();
    translate([PCC_X, PCC_Y, 0]) rotate([0, 0, +A13]) switch_cutout();

    translate([CENTER_X - PAD_OFFSET, TOP_Y, 0]) mounting_cutout();
    translate([CENTER_X + PAD_OFFSET, TOP_Y, 0]) mounting_cutout();
  }
}

part();
