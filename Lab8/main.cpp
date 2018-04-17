#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include "bitmap_image.hpp"

#include <cmath>

#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"

using namespace std;

ofstream myfile;


float vpX = 1, vpY = 1;

std::vector<Sphere> world = {
	Sphere(vec3(0, 0, 1), .33, vec3(1,1,0)),
	Sphere(vec3(.33, .33, 4), .66, vec3(0,1,1)),
	Sphere(vec3(.66, .66, 6), 1, vec3(1,0,1)),
};

int findIntersection(vec3 d, vec3 e) {
	int currentMin = -1;
	float minT = 100000.0f;
	for (int i = 0; i < 3; i++) {
		float a = vec3::dot(d, d);
		float b = vec3::dot(d.scale(2), vec3::subtract(e, world[i].getOrigin()));
		float c = (vec3::dot(vec3::subtract(e, world[i].getOrigin()), vec3::subtract(e, world[i].getOrigin())) - (world[i].getRadius() * world[i].getRadius()));
		float discriminant = (b*b) - (4 * a * c);
		//myfile << "a = " << a << " b = " << b << " c = " << c  << " discriminant = " << discriminant << "\n";
		float sign;
		if (b > 0) { sign = 1; }
		else { sign = -1; }

		if (discriminant >= 0) {
			float q = -(b + sign * sqrt(discriminant));
			float t1 = q / (2 * a);
			float t2 = (2 * c) / q;
			if (t1 >= 0 && t1 < minT) {
				currentMin = i;
				minT = t1;
			}
			if (t2 >= 0 && t2 < minT) {
				currentMin = i;
				minT = t2;
			}
		}
	}
	
	return currentMin;
}


int main(int argc, char** argv) {
	
	myfile.open("output.txt");
	

	bitmap_image image(800, 800);
		
	if (!image)
	{
		printf("Error - Failed to open: pretty.bmp\n");
		return 1;
	}

	//set background color
	for (int i = 0; i < 800; i++) {//x coordinate
		for (int j = 0; j < 800; j++) {//y coordinate
			float u = -1 + (1 - (-1))*(i + .5) / 800;
			float v = 1 - (1 - (-1))*(j + .5) / 800;
			//vec3 d(0, 0, 1);
			//vec3 e(u, v, 0);
			
			vec3 e(0,0,-5);
			vec3 d = vec3::subtract(vec3(u,v,0), e);
			int circle = findIntersection(d, e);
			
			//cout << circle << endl;
			if (circle >= 0) {
				vec3 color = world[circle].getColor();
				int red = color.x * 255;
				int green = color.y * 255;
				int blue = color.z * 255;

				
				image.set_pixel(i, j, red, green, blue);

			}
			else {
				image.set_pixel(i, j, 75, (156), (211));
			}
			if (i == 400 || j == 400) { image.set_pixel(i, j, 0, (0), (0)); }
		}
	}
	//intitialize 3 spheres


	
	myfile.close();

	image.save_image("output.bmp");

	return 0;
}
