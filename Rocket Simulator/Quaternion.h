#pragma once
#include "Vector.h"
#include "Vector.cpp"

enum comp{W, VX, VY, VZ};

class Quaternion :
	public Vector<double, 4>
{
private:
	Vector<double, 4> elements;
public:
	Quaternion();
	Quaternion(double, double, double, double);
	Quaternion(double, double, double);//From Euler Angles; Pitch, Yaw, Roll
	Quaternion(Vector<double, 4>*);
	Quaternion(Vector<double, 3>*); // From Euler Angles
	double &operator[](const int&);
	friend Quaternion operator+(Quaternion, Quaternion);
	friend Quaternion operator*(Quaternion, Quaternion);
};

