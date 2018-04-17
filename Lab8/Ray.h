#ifndef Ray_H
#define Ray_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <cmath>
#include "Vector.h"
using namespace std;


class Ray {

public:
	float x, y, z;
	vec3 origin, direction;

	Ray(vec3 inOrigin, vec3 inDirection) : origin(inOrigin), direction(inDirection){



	}






};

#endif