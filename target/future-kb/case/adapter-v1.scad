$fn             = 72;

WIDTH           = 64 - 20;
THICK           = 3;

HEIGHT          = 80;
DEPTH           = (114 - 3 - 3 - 3)/2 + THICK;

B_MOUNT_SIZE      = 6;
B_MOUNT_WIDTH     = WIDTH - 3 - 3 - B_MOUNT_SIZE;
B_MOUNT_DEPTH     = DEPTH - B_MOUNT_SIZE - THICK;

module base_plate() {
  translate([-WIDTH/2, 0, -THICK]) cube([WIDTH, DEPTH, THICK]);
}

module x_plate() {
  translate([0, DEPTH - THICK/2, HEIGHT/2])
  cube([WIDTH, THICK, HEIGHT], center=true);
}

module raw_part() {
  union() {      
    base_plate();
    x_plate();
  }
}

module x_melt_hole() {
  rotate([90, 0, 0])
  cylinder(h = THICK, r = 1.5, center=true);
}

module base_mount_hole() {
  translate([0, 0, -THICK/2])
  cylinder(h = THICK, r = 1.5, center= true);
}


module part() {
  difference() {
    raw_part();
    translate([-B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2, 0]) base_mount_hole();
    translate([+B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2, 0]) base_mount_hole();
    translate([-B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2 + B_MOUNT_DEPTH, 0]) base_mount_hole();
    translate([+B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2 + B_MOUNT_DEPTH, 0]) base_mount_hole();
    
    translate([1-B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2, 0]) base_mount_hole();
    translate([1+B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2, 0]) base_mount_hole();
    translate([1-B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2 + B_MOUNT_DEPTH, 0]) base_mount_hole();
    translate([1+B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2 + B_MOUNT_DEPTH, 0]) base_mount_hole();
    
    translate([-1-B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2, 0]) base_mount_hole();
    translate([-1+B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2, 0]) base_mount_hole();
    translate([-1-B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2 + B_MOUNT_DEPTH, 0]) base_mount_hole();
    translate([-1+B_MOUNT_WIDTH/2, B_MOUNT_SIZE/2 + B_MOUNT_DEPTH, 0]) base_mount_hole();
    
    
    translate([-B_MOUNT_WIDTH/2, DEPTH - THICK/2, 50]) x_melt_hole();
    translate([+B_MOUNT_WIDTH/2, DEPTH - THICK/2, 50]) x_melt_hole();
    translate([-B_MOUNT_WIDTH/2, DEPTH - THICK/2, 70]) x_melt_hole();
    translate([+B_MOUNT_WIDTH/2, DEPTH - THICK/2, 70]) x_melt_hole();
    
  }
}

part();
