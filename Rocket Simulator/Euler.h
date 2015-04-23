#pragma once
#include "Vec3D.h"

enum angle{ Pitch, Yaw, Roll };

class Euler
{
private:
	Vec3D Angles;
public:
	Euler();
	Euler(double, double, double);
	~Euler();
	/*void rotate(Vec3D*);*/
	double &operator[](const int&);
};

