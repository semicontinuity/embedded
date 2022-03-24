$fn = 72;
SS = 13.8;
KEYCAP_SIZE=19;
THICK = 1.8;
TOP_THICK=2.5;

FINGER_AREA_WIDTH = 20;
FINGER_AREA_DEPTH = 18;

SWITCH_AREA_SIZE = 9;

INN_WIDTH = SWITCH_AREA_SIZE + FINGER_AREA_WIDTH + SWITCH_AREA_SIZE;
INN_DEPTH = SWITCH_AREA_SIZE + FINGER_AREA_DEPTH + SWITCH_AREA_SIZE;
INN_HEIGHT = SWITCH_AREA_SIZE + KEYCAP_SIZE;

OUT_WIDTH = THICK + INN_WIDTH + THICK;
OUT_DEPTH = THICK + INN_DEPTH + THICK;
OUT_HEIGHT = THICK + INN_HEIGHT;

MID_X = (INN_WIDTH + THICK)/2;
MID_Y = (INN_DEPTH + THICK)/2;
MID_Z = INN_HEIGHT/2;
MID_PLATE = -THICK/2;

MOUNT_SIZE = 6;
MOUNT_X = OUT_WIDTH/2 - MOUNT_SIZE/2;
MOUNT_Y = OUT_DEPTH/2 - MOUNT_SIZE/2;


module bulk() {
  translate([0, 0, OUT_HEIGHT/2 - THICK])
  cube([OUT_WIDTH, OUT_DEPTH, OUT_HEIGHT], center = true);
}

module cavity() {
  translate([0, 0, INN_HEIGHT/2])
  cube([INN_WIDTH, INN_DEPTH, INN_HEIGHT], center = true);
}

module stand() {
  translate([0, 0, OUT_HEIGHT/2 - THICK])
  difference() {    
    cube([MOUNT_SIZE, MOUNT_SIZE, OUT_HEIGHT], center = true);
    cylinder(h = OUT_HEIGHT + 1, r = 2, center= true);
  }
}
module stand1() {
  translate([MOUNT_X, MOUNT_Y, 0]) stand();
}
module stand2() {
  translate([MOUNT_X, -MOUNT_Y, 0]) stand();
}
module stand3() {
  translate([-MOUNT_X, MOUNT_Y, 0]) stand();
}
module stand4() {
  translate([-MOUNT_X, -MOUNT_Y, 0]) stand();
}

module box() {
  difference() {
    bulk();      
    cavity();
  }
}


module base() {
  union() {
    box();  
    
    stand1();
    stand2();
    stand3();
    stand4();
  }
}


module switch_cutout_z() {  
  cube([SS, SS, THICK], center = true);
}

module switch_cutout_x() {
  translate([0, 0, SWITCH_AREA_SIZE + KEYCAP_SIZE/2])
  color("red") cube([SS, THICK, SS], center = true);
}

module switch_cutout_y() {
  translate([0, 0, SWITCH_AREA_SIZE + KEYCAP_SIZE/2])
  color("red") cube([THICK, SS, SS], center = true);
}


module mount_hole() {
  translate([0, 0, OUT_HEIGHT/2 - THICK])
  cylinder(h = OUT_HEIGHT, r = 2, center= true);
}


module part() {
  difference() {
    base();
    
    translate([0, MID_Y, 0]) switch_cutout_x();
    translate([0, -MID_Y, 0]) switch_cutout_x();
    translate([MID_X, 0, 0]) switch_cutout_y();
    translate([-MID_X, 0, 0]) switch_cutout_y();
    translate([0, 0, MID_PLATE]) switch_cutout_z();
    
    translate([MOUNT_X, MOUNT_Y, 0]) mount_hole();
    translate([MOUNT_X, -MOUNT_Y, 0]) mount_hole();
    translate([-MOUNT_X, MOUNT_Y, 0]) mount_hole();
    translate([-MOUNT_X, -MOUNT_Y, 0]) mount_hole();
  }
}

part();