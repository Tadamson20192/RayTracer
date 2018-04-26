#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include "bitmap_image.hpp"

#include <cmath>

#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"
#include "triangle.h"

using namespace std;

ofstream myfile;


float vpX = 1, vpY = 1;
vec3 light(0, 0, .75);

std::vector<Sphere> world = {
	Sphere(vec3(0, 0, 1), .33, vec3(1,1,0)),
	Sphere(vec3(.33, .33, 4), .66, vec3(0,1,1)),
	Sphere(vec3(.66, .66, 6), 1, vec3(1,0,1)),
};

std::vector<Triangle> triangles = {
	Triangle(vec3(0,.5,1), vec3(-.25,-.5,1), vec3(.25,-.5,1), vec3(1,1,0))
};



float determineIntersection(Sphere sphere, vec3 d, vec3 e) {
	
	float a = vec3::dot(d, d);
	float b = vec3::dot(d.scale(2), vec3::subtract(e, sphere.getOrigin()));
	float c = (vec3::dot(vec3::subtract(e, sphere.getOrigin()), vec3::subtract(e, sphere.getOrigin())) - (sphere.getRadius() * sphere.getRadius()));
	float discriminant = (b*b) - (4 * a * c);
	//myfile << "a = " << a << " b = " << b << " c = " << c  << " discriminant = " << discriminant << "\n";
	float sign;
	if (b > 0) { sign = 1; }
	else { sign = -1; }

	if (discriminant >= 0) {
		float q = -(b + sign * sqrt(discriminant));
		float t1 = q / (2 * a);
		float t2 = (2 * c) / q;
		if (t1 >= 0 && t1 < t2) {
			return t1;
		}
		else if (t2 >= 0) {
			return t2;
		}
		else { return -1; }
	}

}





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

float determinant(vec3 a, vec3 b, vec3 c) {
	float one = a.getX() * ((b.getY() * c.getZ()) - (b.getZ() * c.getY()));
	float two = b.getX() * ((a.getY() * c.getZ()) - (a.getZ() * c.getY()));
	float three = c.getX() * ((a.getY() * b.getZ()) - (a.getZ() * b.getY()));
	return one - two + three;
}


float triangleInter(vec3 p0, vec3 p1, vec3 p2, vec3 d, vec3 e) {
	float determ = determinant(vec3::subtract(p1, p0), vec3::subtract(p2,p0), d.scale(-1));
	float u = determinant(vec3::subtract(e, p0), vec3::subtract(p2, p0), d.scale(-1));
	float v = determinant(vec3::subtract(p1, p0), vec3::subtract(e, p0), d.scale(-1));
	float t = determinant(vec3::subtract(p1, p0), vec3::subtract(p2, p0), vec3::subtract(e, p0));

	u = u / determ;
	v = v / determ;
	t = t / determ;

	if ((1 - u - v) > 0) {
		return t;
	}
	else { return -1; }

	//vec3 edge1 = vec3::subtract(p0, p1);
	//vec3 edge2 = vec3::subtract(p2, p1);
	//vec3 n = vec3::cross(edge1, edge2);
	//n.normalize();

	//float upper = vec3::dot(vec3::subtract(d, n), e);
	//float lower = vec3::dot(n, d);
	//if (lower <.000001 && lower > -.000001) {
	//	cout << "here1" << endl;
	//	return - 1; }

	//float t = upper / lower;
	//vec3 q = vec3::add(e, d.scale(t));

	//float alpha = vec3::dot(vec3::cross(edge2, vec3::subtract(q, p1)), n);
	//float beta = vec3::dot(vec3::cross(vec3::subtract(p0,p2), vec3::subtract(q, p2)), n);
	//float omega = vec3::dot(vec3::cross(vec3::subtract(p1, p0), vec3::subtract(q, p0)), n);
	////myfile << "alpha = " << alpha << " beta = " << beta<< " omega = " << omega << "\n";
	//if (alpha >= 0 && beta >= 0 && omega >= 0) { 
	//	cout << "draw" << endl;
	//	return t; }
	//else { 
	//	//cout << "here2" << endl;
	//	return -1; 
	//}



	//vec3 h = vec3::cross(d, edge2);
	//float a = vec3::dot(edge1, h);
	//myfile << "1.x = " << edge1.getX() << " 1.y = " << edge1.getY() << " 1.z = " << edge1.getZ() << "\n";
	//myfile << "h.x = " << h.getX() << " h.y = " << h.getY() << " h.z = " << h.getZ() << "\n";
	//myfile << "d.x = " << d.getX() << " d.y = " << d.getY() << " d.z = " << d.getZ() << "\n";
	//myfile << "a = " << a << "\n";
	//if (a < .0000001 && a > -.0000001) {
	//	//cout << "a: " << a << endl;
	//	return -1;
	//}
	//float f = 1 / a;
	//vec3 s = vec3::subtract(e, p0);
	//float u = f * (vec3::dot(s,h));
	//if (u < 0.0 || u > 1.0){ return -1; }
	//vec3 q = vec3::cross(s, edge1);
	//float v = f * vec3::dot(d, q);
	//if (v < 0.0 || u + v > 1.0) {return -1;}
	//	
	//float t = f * vec3::dot(edge1, q);
	//return t;
	

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
			
			//orthogonal
			vec3 d(0, 0, 1);
			vec3 e(u, v, 0);

			//perspective
			//vec3 e(0, 0, -5);
			//vec3 d = vec3::subtract(vec3(u, v, 0), e);


			int circle = -1;
			float minT = 999999;
			for (int i = 0; i < 1; i++) {
				float t = triangleInter(triangles[i].getP1(), triangles[i].getP2(), triangles[i].getP3(), d, e);
				//cout << t << endl;
				if (t < minT && t > 0) {
					minT = t;
					circle = i;
				}
			}
			vec3 ld = vec3::subtract(light, vec3::add(d.scale(minT), e));
			int shadeCount = 1;

			if (circle > 0) {
				for (int i = 0; i < 1; i++) {
					if (i != circle) {
						float t = triangleInter(triangles[i].getP1(), triangles[i].getP2(), triangles[i].getP3(), d, e);
						if (t > 0) {
							shadeCount++;
							cout << "intersect!" << endl;
						}
					}
				}
			}
			
			//int circle = findIntersection(d, e);
			
			//cout << circle << endl;
			if (circle >= 0) {
				vec3 color = triangles[circle].getColor();
				int red = color.x * 255 * (1/shadeCount);
				int green = color.y * 255 * (1 / shadeCount);
				int blue = color.z * 255 * (1 / shadeCount);

				myfile << "red = " << red << " blue = " << blue << " green = " << green << "\n";
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
