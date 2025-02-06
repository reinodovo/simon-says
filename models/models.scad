include <../../ktane-3d-models/variables.scad>;
use <../../ktane-3d-models/bomb_base.scad>;

$fn = $preview ? 50 : 100;

tolerance = 0.3;

button_size = 25;
button_distance = 19.09;

module top() {
    difference() {
        bomb_module_top(height_above_pcb = 14, module_type = 1);
        for (i = [-1:2:1]) {
            translate([size / 2 + i * button_distance, size / 2, 0])
                rotate([0, 0, 45]) cube([button_size, button_size, 10], center = true);
        }
        for (i = [-1:2:1]) {
            translate([size / 2, size / 2 + i * button_distance, 0])
                rotate([0, 0, 45]) cube([button_size, button_size, 10], center = true);
        }
    }
}

module bottom() {
    bomb_module_bottom(height_above_pcb = 14);
}

color("darkgray") top();
!color("darkgray") bottom();
