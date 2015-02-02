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
	Quaternion(Vector<double, 4>*);
	double &operator[](const int&);
	friend Quaternion operator+(Quaternion, Quaternion);
	friend Quaternion operator*(Quaternion, Quaternion);
};

