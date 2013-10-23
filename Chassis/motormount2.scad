//Baxterbot motor mount
//bpw 10/10/13

 $fn=50;  //resolution


module MotorMount() {

difference(){

cube([60, 40, 23], center = false);


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

//cut off the slant
translate([60,-30,0]){
	rotate([0,-20,0]){
		cube([20, 100,40], center = false);}}
}






}



MotorMount();