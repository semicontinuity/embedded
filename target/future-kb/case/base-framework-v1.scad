$fn             = 72;

SS              = 19;
OUT_WIDTH       = 64;
OUT_DEPTH       = 95;

BASE_HEIGHT     = 25;
HEIGHT=5*SS;

STAND_WIDTH     = 20;
STAND_DEPTH     = 20;

WALL_THICK      = 3;

TOP_PLATE_THICK = 1.0;
TOP_PLATE_WIDTH = OUT_WIDTH - STAND_WIDTH - 2*WALL_THICK;
TOP_PLATE_DEPTH = OUT_DEPTH - 2*WALL_THICK;

PLATE_THICK     = 1.6;

CAVITY_WIDTH    = OUT_WIDTH - STAND_WIDTH - 2*WALL_THICK;
CAVITY_DEPTH    = (OUT_DEPTH - 3*WALL_THICK)/2;

MOUNT_SIZE      = 6;

SCREW_CAP_H     = 2.0;
SCREW_CAP_D     = 5.6;
MELT_HOLE_D     = 4.0;

X_MELT_HOLE_X     = OUT_WIDTH - STAND_WIDTH + 5;
Y_MELT_HOLE_X     = OUT_WIDTH - WALL_THICK/2;
Y_MELT_HOLE_Y_OFS = OUT_DEPTH/2 - STAND_DEPTH + 5;


module top_plate_cutout() {
  color("red")
  translate([WALL_THICK, -TOP_PLATE_DEPTH/2, BASE_HEIGHT-TOP_PLATE_THICK])
  cube([TOP_PLATE_WIDTH, TOP_PLATE_DEPTH, TOP_PLATE_THICK]);
}

module base_plate() {
  translate([0, -OUT_DEPTH/2, -PLATE_THICK]) cube([OUT_WIDTH, OUT_DEPTH, PLATE_THICK]);
}

module bulk() {
  translate([OUT_WIDTH/2, 0, BASE_HEIGHT/2])
  cube([OUT_WIDTH, OUT_DEPTH, BASE_HEIGHT], center=true);
}

module cavity() {
  translate([CAVITY_WIDTH/2, 0, BASE_HEIGHT/2])
  cube([CAVITY_WIDTH, CAVITY_DEPTH, BASE_HEIGHT], center=true);
}

module work_cavity() {
  translate([OUT_WIDTH - STAND_WIDTH, -(OUT_DEPTH - 2*WALL_THICK)/2, 0])
  cube([STAND_WIDTH, OUT_DEPTH - 2*WALL_THICK, BASE_HEIGHT]);
}

module sandboxes() {
  difference() {
    bulk();
    
    translate([WALL_THICK, (OUT_DEPTH/2-CAVITY_DEPTH/2) - WALL_THICK, 0]) cavity();
    translate([WALL_THICK, -(OUT_DEPTH/2-CAVITY_DEPTH/2) + WALL_THICK, 0]) cavity();
    work_cavity();
  }
}

module stand() {
  translate([0, 0, BASE_HEIGHT/2])
  difference() {    
    cube([MOUNT_SIZE, MOUNT_SIZE, BASE_HEIGHT], center = true);
    cylinder(h = BASE_HEIGHT, r = 1.5, center= true);
  }
}


module x_plate() {
  translate([OUT_WIDTH - STAND_WIDTH/2, 0, HEIGHT/2])
  cube([STAND_WIDTH, WALL_THICK, HEIGHT], center=true);
}


module x_plate() {
  translate([OUT_WIDTH - STAND_WIDTH/2, 0, HEIGHT/2])
  cube([STAND_WIDTH, WALL_THICK, HEIGHT], center=true);
}

module x_melt_hole() {
  rotate([90, 0, 0])
  cylinder(h = WALL_THICK, r = MELT_HOLE_D/2, center=true);
}

module y_plate() {
  translate([OUT_WIDTH - WALL_THICK/2, 0, HEIGHT/2])
  cube([WALL_THICK, STAND_WIDTH, HEIGHT], center=true);
}

module y_melt_hole() {
  rotate([0, 90, 0])
  cylinder(h = WALL_THICK, r = MELT_HOLE_D/2, center=true);
}


module raw_part() {
  union() {  
    sandboxes();
    base_plate();
    
    translate([MOUNT_SIZE/2 + WALL_THICK, -OUT_DEPTH/2 + 2*WALL_THICK, 0]) stand();
    translate([MOUNT_SIZE/2 + WALL_THICK, -WALL_THICK/2 - MOUNT_SIZE/2, 0]) stand();
    translate([CAVITY_WIDTH, -OUT_DEPTH/2 + 2*WALL_THICK, 0]) stand();
    translate([CAVITY_WIDTH, -WALL_THICK/2 - MOUNT_SIZE/2, 0]) stand();
    
    translate([MOUNT_SIZE/2 + WALL_THICK, OUT_DEPTH/2 - 2*WALL_THICK, 0]) stand();
    translate([MOUNT_SIZE/2 + WALL_THICK, +WALL_THICK/2 + MOUNT_SIZE/2, 0]) stand();
    translate([CAVITY_WIDTH, OUT_DEPTH/2 - 2*WALL_THICK, 0]) stand();
    translate([CAVITY_WIDTH, WALL_THICK/2 + MOUNT_SIZE/2, 0]) stand();
    
    translate([0, -OUT_DEPTH/2 + WALL_THICK/2, 0]) x_plate();
    translate([0, +OUT_DEPTH/2 - WALL_THICK/2, 0]) x_plate();
    
    translate([0, -OUT_DEPTH/2 + STAND_DEPTH/2, 0]) y_plate();
    translate([0, +OUT_DEPTH/2 - STAND_DEPTH/2, 0]) y_plate();
  }
}


module screw_cap_cavity() {
  translate([0, 0, SCREW_CAP_H/2-PLATE_THICK]) 
  cylinder(h = SCREW_CAP_H, r = SCREW_CAP_D/2, center=true);
}

module part() {
  difference() {
    raw_part();
    top_plate_cutout();
    
    translate([MOUNT_SIZE/2 + WALL_THICK, -OUT_DEPTH/2 + 2*WALL_THICK, 0])  screw_cap_cavity();
    translate([MOUNT_SIZE/2 + WALL_THICK, -WALL_THICK/2 - MOUNT_SIZE/2, 0]) screw_cap_cavity();
    translate([CAVITY_WIDTH, -OUT_DEPTH/2 + 2*WALL_THICK, 0])               screw_cap_cavity();
    translate([CAVITY_WIDTH, -WALL_THICK/2 - MOUNT_SIZE/2, 0])              screw_cap_cavity();
    
    translate([MOUNT_SIZE/2 + WALL_THICK, OUT_DEPTH/2 - 2*WALL_THICK, 0])   screw_cap_cavity();
    translate([MOUNT_SIZE/2 + WALL_THICK, +WALL_THICK/2 + MOUNT_SIZE/2, 0]) screw_cap_cavity();
    translate([CAVITY_WIDTH, OUT_DEPTH/2 - 2*WALL_THICK, 0])                screw_cap_cavity();
    translate([CAVITY_WIDTH, WALL_THICK/2 + MOUNT_SIZE/2, 0])               screw_cap_cavity();

    
    translate([X_MELT_HOLE_X, -OUT_DEPTH/2 + WALL_THICK/2, SS/2 + 0*SS]) x_melt_hole();
    translate([X_MELT_HOLE_X, -OUT_DEPTH/2 + WALL_THICK/2, SS/2 + 2*SS]) x_melt_hole();
    translate([X_MELT_HOLE_X, -OUT_DEPTH/2 + WALL_THICK/2, SS/2 + 4*SS]) x_melt_hole();
    
    translate([X_MELT_HOLE_X, OUT_DEPTH/2 - WALL_THICK/2, SS/2 + 0*SS]) x_melt_hole();
    translate([X_MELT_HOLE_X, OUT_DEPTH/2 - WALL_THICK/2, SS/2 + 2*SS]) x_melt_hole();
    translate([X_MELT_HOLE_X, OUT_DEPTH/2 - WALL_THICK/2, SS/2 + 4*SS]) x_melt_hole();

    
    translate([Y_MELT_HOLE_X, Y_MELT_HOLE_Y_OFS, SS/2 + 0*SS]) y_melt_hole();
    translate([Y_MELT_HOLE_X, Y_MELT_HOLE_Y_OFS, SS/2 + 1*SS]) y_melt_hole();
    translate([Y_MELT_HOLE_X, Y_MELT_HOLE_Y_OFS, SS/2 + 2*SS]) y_melt_hole();
    translate([Y_MELT_HOLE_X, Y_MELT_HOLE_Y_OFS, SS/2 + 3*SS]) y_melt_hole();
    translate([Y_MELT_HOLE_X, Y_MELT_HOLE_Y_OFS, SS/2 + 4*SS]) y_melt_hole();

    translate([Y_MELT_HOLE_X, -Y_MELT_HOLE_Y_OFS, SS/2 + 0*SS]) y_melt_hole();
    translate([Y_MELT_HOLE_X, -Y_MELT_HOLE_Y_OFS, SS/2 + 1*SS]) y_melt_hole();
    translate([Y_MELT_HOLE_X, -Y_MELT_HOLE_Y_OFS, SS/2 + 2*SS]) y_melt_hole();
    translate([Y_MELT_HOLE_X, -Y_MELT_HOLE_Y_OFS, SS/2 + 3*SS]) y_melt_hole();
    translate([Y_MELT_HOLE_X, -Y_MELT_HOLE_Y_OFS, SS/2 + 4*SS]) y_melt_hole();

  }
}

part();
