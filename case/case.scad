/*
 * case.scad -- case for the guiderport hardware
 *
 * (c) 2015 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */

l = 57.15 + 0.3;
w = 24.13 + 0.2;
h = 22;
wall = 2.5;
L = l + 2 * wall;
W = w + 2 * wall;
H = 5;
s = 4.5;
board = 1.8;

module	bottom() {
	difference() {
		union() {
			translate([0, 0, 0.5])
				cube([L, W, 1], center = true);
			translate([0, 0, (s + 1) / 2])
				cube([L - wall, W - wall, s + 1], center = true);
		}
		union() { 
			translate([0, 0, (s + 1) / 2 + 1 + s - board])
				cube([l, w, s + 1], center = true);
			translate([0, 0, (s + 1) / 2 + 1])
				cube([l - 2, w - 4, s + 1], center = true);
			translate([0, 0, (s + 1) / 2 + 1])
				cube([l - 4, w - 2, s + 1], center = true);

			translate([-l / 4, -(w + wall)/2, 2])
				cube([10, 0.8, 1.5], center = true); 
			translate([+l / 4, -(w + wall)/2, 2])
				cube([10, 0.8, 1.5], center = true); 
			translate([-l / 4, (w + wall)/2, 2])
				cube([10, 0.8, 1.5], center = true); 
			translate([+l / 4, (w + wall)/2, 2])
				cube([10, 0.8, 1.5], center = true);
		}
	}
    // for USB
	translate([-l / 2 - wall / 2, -3, (s + 1) / 2])
		cube([wall, 13, s + 1], center = true);
   // for autoguide jack
	translate([l / 2 + wall / 2, 0, (s + 1) / 2])
		cube([wall, 13, s + 1], center = true);
}

module	top() {
	difference() {
		union() {
			translate([0, 0, h / 2])
				cube([L, W, h], center = true);
		}
		union() {
			translate([0, 0, h / 2 - 1])
				cube([l, w - 4, h], center = true);
			translate([0, 0, h / 2 - 1])
				cube([l - 4, w, h], center = true);

			translate([0, 0, -5 + s])
				cube([L - wall + 0.2, W - wall + 0.2, 10], center = true);
			// opening for USB
			translate([-L / 2, -3, 5])
				cube([10, 13.4, 18 + 4], center = true);
			// opening for autoguide jack
			translate([L / 2, 0, 7])
				cube([10, 13.4, 20 + 4], center = true);
		}
	}
	translate([-l / 4, -(w + wall)/2, 0.75])
		cube([8, 0.8, 1], center = true); 
	translate([+l / 4, -(w + wall)/2, 0.75])
		cube([8, 0.8, 1], center = true); 
	translate([-l / 4, (w + wall)/2, 0.75])
		cube([8, 0.8, 1], center = true); 
	translate([+l / 4, (w + wall)/2, 0.75])
		cube([8, 0.8, 1], center = true);

	// reinforcement bars in ceiling
	translate([-10, 0, h - 5.5])
		cube([2, W, 11], center = true);	
	translate([15, 0, h - 6.5])
		cube([2, W, 13], center = true);
}

translate([0, 30, h])
	rotate([180, 0, 0])
		top();

bottom();
