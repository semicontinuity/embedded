SS=19;
OUT_WIDTH=64;
OUT_DEPTH=95;

BASE_HEIGHT=25;
HEIGHT=5*SS;

WALL_THICK = 3;
PLATE_THICK=1.6;

module bulk() {
  translate([OUT_WIDTH/2, 0, BASE_HEIGHT/2])
  cube([OUT_WIDTH, OUT_DEPTH, BASE_HEIGHT], center = true);
}

module sandboxes() {
  difference() {
    bulk();
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
