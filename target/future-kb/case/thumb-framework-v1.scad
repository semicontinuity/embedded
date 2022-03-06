THICK = 2;

FINGER_AREA_WIDTH = 26;
FINGER_AREA_DEPTH = 18;
FINGER_AREA_HEIGHT = 19;

SWITCH_AREA_SIZE = 9;

INN_WIDTH = SWITCH_AREA_SIZE + FINGER_AREA_WIDTH + SWITCH_AREA_SIZE;
INN_DEPTH = SWITCH_AREA_SIZE + FINGER_AREA_DEPTH + SWITCH_AREA_SIZE;
INN_HEIGHT = 19;

OUT_WIDTH = THICK + INN_WIDTH + THICK;
OUT_DEPTH = THICK + INN_DEPTH + THICK;
OUT_HEIGHT = THICK + INN_HEIGHT;


module body() {
  translate([0, 0, OUT_HEIGHT/2 - THICK])
  cube([OUT_WIDTH, OUT_DEPTH, OUT_HEIGHT], center = true);
}

module cavity() {
  translate([0, 0, INN_HEIGHT/2])
  cube([INN_WIDTH, INN_DEPTH, INN_HEIGHT], center = true);
}

module part() {
    difference() {
      body();
      cavity();
    }
}

//mirror([1,0,0])
//rotate(a=[0,180,0])
//translate([-200, 100, 0])
part();
//body();
//cavity();
//opening_bevel();