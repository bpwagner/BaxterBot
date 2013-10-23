/*   	Parametric airless tire
		by Travis Howse <tjhowse@gmail.com>
		2012.   License, GPL v2 or later
**************************************************/

dia_in = 5.75;
dia_out = 50;
spoke_count = 4;
spoke_thickness = 0.5;
tread_thickness = 1;
hub_thickness = 3;
height = 10;
$fn = 30;
spoke_dia = (dia_in/2) + hub_thickness + (dia_out/2) - tread_thickness+spoke_thickness;
grip_density = 0; // Set to 0 for no grip.
grip_height = 0.5;
grip_depth = 1;
pi = 3.14159;
zff = 0.001;

hub_extra_height = 3;
flat_hub_width = 4; // Use a value > dia_in to get a round hub

//Set to 1 for a double spiral.
// Note: single-wall spokes probably won't work with double spirals, as the
// first layer of the upper spiral would bridge in a straight line, rather
// than a curve. Successive layers probably wouldn't recover.
double_spiral = 1;

module wheel()
{
     difference(){
	cylinder(r=dia_out/2,h=height);
      translate([0,0,6]){cylinder(r=dia_out/2-tread_thickness,h=height-4);}
cylinder(r=(dia_in/2)+hub_thickness,h=height+hub_extra_height);
}


	difference()
	{
		cylinder(r=(dia_in/2)+hub_thickness,h=height+hub_extra_height);
		intersection()
		{
			cylinder(r=dia_in/2,h=height+hub_extra_height);	
			translate([0,0,(height+hub_extra_height)/2])
				cube([flat_hub_width,2*(flat_hub_width),height+hub_extra_height], center=true);
		}
	}
	


}



wheel();
