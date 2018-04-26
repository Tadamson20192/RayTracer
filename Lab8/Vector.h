#ifndef vector_H
#define vector_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <cmath>

using namespace std;

class vec3 {

public:
	float x, y, z;

	vec3(float in_x, float in_y, float in_z) : x(in_x), y(in_y), z(in_z) {
	
	
	
	}
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }

	vec3 scale(float scalar) {
		return vec3(x*scalar, y*scalar, z *scalar);
		
	}
	
	static vec3 cross(vec3 vec1, vec3 vec2) {
		float outX = (vec1.y * vec2.z) - (vec1.z * vec2.y);
		float outY = (vec1.x * vec2.z) - (vec1.z * vec2.x);
		float outZ = (vec1.x * vec2.y) - (vec1.y * vec2.x);
		return vec3(outX, outY, outZ);
	}

	static vec3 subtract(vec3 vec1, vec3 vec2) {
		float outX = vec1.x - vec2.x;
		float outY = vec1.y - vec2.y;
		float outZ = vec1.z - vec2.z;
		return vec3(outX, outY, outZ);
	}


	static vec3 add(vec3 vec1, vec3 vec2) {
		float outX = vec1.x + vec2.x;
		float outY = vec1.y + vec2.y;
		float outZ = vec1.z + vec2.z;
		return vec3(outX, outY, outZ);
	}

	static float dot(vec3 vec1, vec3 vec2) {
		return ((vec1.x * vec2.x) +
			(vec1.y * vec2.y) +
			(vec1.z * vec2.z));
	
	}

	void normalize() {
		float distance = sqrt((x*x) + (y*y) + (z*z));
		x = x / distance;
		y = y / distance;
		z = z / distance;
	}

	void printVector() {
		ofstream myfile;
		myfile.open("output.txt");
		myfile << "X: " << x ;
		myfile << "\nY: " << y;
		myfile << "\nZ: " << z;
		myfile.close();
	}





};




#endif