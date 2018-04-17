#ifndef Sphere_H
#define Sphere_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


#include "Vector.h"

using namespace std;

class Sphere {

public:
	float radius;
	vec3 origin, color;

	Sphere(vec3 inOrigin, float inRadius, vec3 inColor) : origin(inOrigin), radius(inRadius), color(inColor) {



	}

	vec3 getOrigin() {
		return origin;
	}
	vec3 getColor() {
		return color;
	}
	float getRadius() {
		return radius;
	}



};




#endif