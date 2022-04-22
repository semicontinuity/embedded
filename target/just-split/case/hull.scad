$fn=200;
HEIGHT = 6;
EXTENSION = 3;
THICK  = 2;
OP_BEVEL = 1;
CUTOUT_H = 2.5;

outline_points = concat(
// LINE (205.73576, -153.29278)->(190.49576, -138.05278); flip=False
[ [205.73576, -153.29278] ],
// LINE (174.59576, -128.85278)->(190.49576, -138.05278); flip=True
[ [190.49576, -138.05278] ],
// LINE (174.59576, -64.25278)->(174.59576, -128.85278); flip=True
[ [174.59576, -128.85278] ],
// LINE (205.68576, -64.25278)->(174.59576, -64.25278); flip=True
[ [174.59576, -64.25278] ],
// ARC (205.68576, -64.25278)->(206.80576, -65.37278); 90.0->0.0 flip=False
[ for(a = [90.0:-5:0.0]) [205.68576 + 1.1200000000000045 * cos(a), -65.37278 + 1.1200000000000045 * sin(a)] ],
// LINE (206.80576, -65.37278)->(206.80576, -153.29278); flip=False
[ [206.80576, -65.37278] ],
// LINE (206.80576, -153.29278)->(205.73576, -153.29278); flip=False
[ [206.80576, -153.29278] ]
);

opening_points = concat(
// LINE (195.68576, -129.57278)->(195.68576, -88.47278); flip=False
[ [195.68576, -129.57278] ],
// LINE (195.68576, -88.47278)->(203.48576, -88.47278); flip=False
[ [195.68576, -88.47278] ],
// LINE (203.48576, -88.47278)->(203.48576, -129.57278); flip=False
[ [203.48576, -88.47278] ],
// LINE (203.48576, -129.57278)->(195.68576, -129.57278); flip=False
[ [203.48576, -129.57278] ]
);

// this is a base, that will be enlarged by minkowski to make beveled shape.
module hull_base() {
  linear_extrude(height = HEIGHT - THICK) offset(r=-THICK) polygon(outline_points);
}

module beveled_solid_hull() {
  minkowski() {
      hull_base();
      cylinder(h=THICK, r1=THICK, r2=0);
  };
}

module beveled_hull() {
  difference() {
    beveled_solid_hull();
    hull_base();
  };
}

module stand1() {
  translate([190.90286, -85.9, -EXTENSION])
  difference() {
    cylinder(HEIGHT + EXTENSION, r=2.5); 
    cylinder(6, r=1.5); 
  }  
}

module stand2() {
  translate([190.90286, -132.37278, -EXTENSION])
  difference() {
    cylinder(HEIGHT + EXTENSION, r=2.5); 
    cylinder(6, r=1.5); 
  }  
}

module opening() {
  linear_extrude(height = HEIGHT) polygon(opening_points);
}

module opening_bevel() {
  translate([0, 0, HEIGHT - OP_BEVEL])
  minkowski() {
    linear_extrude(height = OP_BEVEL) polygon(opening_points);
    cylinder(h=OP_BEVEL, r1=0, r2=OP_BEVEL,  $fn=40);
  };
}


module cutout_usart_l() {
  translate([178.7, -64.27278 - 2, 0]) {
    color("red") cube([184.8-178.7, 3, CUTOUT_H]);
  }
} 

module cutout_i2c_l() {
  translate([198.7, -64.27278 - 2, 0]) {
    color("red") cube([204.8-198.7, 3, CUTOUT_H]);
  }
} 


module cutout_usart_r() {
  translate([176.9, -64.27278 - 2, 0]) {
    color("red") cube([184.8-178.7, 3, CUTOUT_H]);
  }
} 

module cutout_i2c_r() {
  translate([196.9, -64.27278 - 2, 0]) {
    color("red") cube([204.8-198.7, 3, CUTOUT_H]);
  }
} 


module part() {
  union() {
    difference() {
      beveled_hull();
      opening();
      opening_bevel();
      
      cutout_usart_r();
      cutout_i2c_r();
    }
    stand1();
    stand2();
  }  
}

mirror([1,0,0])
rotate(a=[0,180,0])
translate([-200, 100, 0])
part();
//opening_bevel();