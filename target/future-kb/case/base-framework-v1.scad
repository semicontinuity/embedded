SS=19;
OUT_WIDTH=64;
OUT_DEPTH=95;

BASE_HEIGHT=25;
HEIGHT=5*SS;

WALL_THICK = 3;
PLATE_THICK=1.6;
STAND_WIDTH=20;
STAND_DEPTH=20;

CAVITY_WIDTH = OUT_WIDTH - STAND_WIDTH - 2*WALL_THICK;
CAVITY_DEPTH = (OUT_DEPTH - 3*WALL_THICK)/2;

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

module raw_part() {
  union() {
    sandboxes(); 
  }
}


module part() {
  difference() {
    raw_part();
  }
}

part();
