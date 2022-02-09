$fn=40;

// bevel parameters: TOP == BEVEL for 45 degree bevel
TOP    = 1.6;        // top part thickness
BEVEL  = 1.6;
HOOK   = 1.6;   

THICK  = 2;     // walls thickness
HEIGHT = 6.4;   // excluding upper part


include <outline_points.scad>

module hard_bounds() {
  translate([0,-300,0]) cube(300);
}

module body() {
  linear_extrude(height = HEIGHT) polygon(outline_points);
}

// "enlarged" body, ready to be further enlarged by minkowski
module outer_margin() {
  linear_extrude(height = HEIGHT) offset(r=THICK-BEVEL) polygon(outline_points);
}

// "shrinked" body
module inner_margin() {
  linear_extrude(height = HEIGHT + TOP) offset(r=-HOOK) polygon(outline_points);
}

// this is a base, that will be enlarged by minkowski to make beveled shape.
// total thickness after enlargement will be == THICK
module frame_base() {
  difference() {
    outer_margin();
    inner_margin();
  }
}


rotate(a=[0,180,0])
intersection() {
  hard_bounds();

  difference() {
    minkowski() {
      frame_base();
      cylinder(h=TOP, r1=BEVEL, r2=0,  $fn=10);
    };
    body();
    inner_margin();
  }
}


     



