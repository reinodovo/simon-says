include <../../ktane-3d-models/variables.scad>;
use <../../ktane-3d-models/bomb_base.scad>;

$fn = $preview ? 50 : 100;

tolerance = 0.3;

button_size = 25;
button_distance = 19.09;

button_height_above = 6.5;
button_height_below = 7.6;
button_lip = 1.5;
button_detail_height = 4;
button_detail_thickness = 4;
button_detail_corner_radius = 2;

led_distance = 20;
led_height = 4.5;
led_radius = 2.6;

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

module button() {
    button_height = button_height_above + button_height_below;
    button_thick_height = button_height - button_detail_height;
    button_height_below_module_wall = button_height_below - wall_thickness - tolerance;
    led_distance_size = sqrt(led_distance * led_distance / 2);
    difference() {
        union() {
            translate([0, 0, button_thick_height / 2]) minkowski() {
                cube([button_size - 2 * tolerance - 2 * button_detail_corner_radius, button_size - 2 * tolerance - 2 * button_detail_corner_radius, button_thick_height - button_detail_corner_radius], center = true);
                cylinder(button_detail_corner_radius, button_detail_corner_radius, button_detail_corner_radius, center = true);
            }
            translate([0, 0, button_height / 2]) cube([button_size - button_detail_thickness * 2 - tolerance, button_size - button_detail_thickness * 2 - tolerance, button_height], center = true);
            translate([0, button_lip / 2 + 2 * tolerance / 2, button_height_below_module_wall / 2]) cube([button_size + 2 * button_lip, button_size + button_lip, button_height_below_module_wall], center = true);
        }
        for (i = [-1:2:1]) {
            for (j = [-1:2:1]) {
                translate([i * led_distance_size / 2, j * led_distance_size / 2]) cylinder(led_height, led_radius, led_radius);
            }
        }
    }
}

module button_detail() {
    difference() {
        minkowski() {
            translate([0, 0, (button_detail_height - tolerance - button_detail_corner_radius) / 2]) cube([button_size - 2 * tolerance - 2 * button_detail_corner_radius, button_size - 2 * tolerance - 2 * button_detail_corner_radius, button_detail_height - tolerance - button_detail_corner_radius], center = true);
            difference() {
                sphere(button_detail_corner_radius);
                translate([0, 0, - 2 * button_detail_corner_radius]) cube([4 * button_detail_corner_radius, 4 * button_detail_corner_radius, 4 * button_detail_corner_radius], center = true);
            }
        }
        cube([button_size - 2 * button_detail_thickness, button_size - 2 * button_detail_thickness, 4 * button_detail_height], center = true);
    }
}

color("darkgray") top();
color("darkgray") bottom();
!button();
button_detail();