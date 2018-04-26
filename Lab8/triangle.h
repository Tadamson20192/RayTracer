#ifndef triangle_H
#define tirnagle_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


#include "Vector.h"

using namespace std;

class Triangle {

public:
	
	vec3 p1, p2, p3, color;

	Triangle(vec3 inP1, vec3 inP2, vec3 inP3, vec3 inColor) : p1(inP1), p2(inP2), p3(inP3), color(inColor) {



	}

	vec3 getP1() {
		return p1;
	}
	vec3 getP2() {
		return p2;
	}
	vec3 getP3() {
		return p3;
	}
	vec3 getColor() {
		return color;
	}




};




#endif
