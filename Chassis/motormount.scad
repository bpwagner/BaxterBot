//Baxterbot motor mount
//bpw 10/10/13

 $fn=50;  //resolution


module MotorMount() {

difference(){
union(){
cube([65, 40, 24], center = false);

//top box/plate
translate([-20,-19,23]){
cube([85, 78,25], center = false);}

//back cube
translate([-20,10,0]){
cube([21, 20,24], center = false);}
//roller
translate([-10,20,0]){
sphere(r=10, center = true);}

}

//botom screw hole
translate([7,-1,2.5]){
	rotate([-90,0,0]){
		cylinder(h=42, r=1.5);}}

//top screw hole
translate([7,-1,20.5]){
	rotate([-90,0,0]){
		cylinder(h=42, r=1.5);}}

hull(){
//hold for other side of axil
translate([27,-1,23/2]){
	rotate([-90,0,0]){
		cylinder(h=42, r=6);}}
//hold for little nub
translate([15,-1,23/2]){
	rotate([-90,0,0]){
		cylinder(h=42, r=3);}}
}

//top circuit enclosure hole 1 left right
translate([-22,-17,25]){
cube([90, 74,21], center = false);}

//top circuit enclosure hole 2 forward backward
translate([-10,-22, 25]){
cube([60, 90, 21], center = false);}

//top circuit enclosure hole 3  back hole
translate([-10,50,30]){
cube([60, 10,25], center = false);}

//top circuit enclosure hole 4 front hole
translate([-10,-22,30]){
cube([60, 10,25], center = false);}

//top circuit enclosure hole 6 ultrasonic hole
translate([40,0,30]){
cube([25, 40,25], center = false);}


//cut off the slant
translate([65,-30,0]){
	rotate([0,-10,0]){
		cube([20, 100,100], center = false);}}
}






}



MotorMount();