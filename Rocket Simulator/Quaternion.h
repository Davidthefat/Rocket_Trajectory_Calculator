#pragma once
#include "Vector.h"
#include "Vector.cpp"
#include "Euler.h"

enum comp{ W, VX, VY, VZ };

class Quaternion
{
private:
	Vector<double, 4> elements;
public:
	Quaternion();
	Quaternion(double, double, double, double);
	Quaternion(double, double, double);//From Euler Angles; Pitch, Yaw, Roll
	Quaternion(Vector<double, 4>*);
	Quaternion(Euler*); // From Euler Angles
	Quaternion conj();
	Euler toEuler();
	Quaternion norm();
	Vector<double, 3> vector();
	void rotate(Vector<double, 3>*);
	double &operator[](const int&);
	friend Quaternion operator+(Quaternion, Quaternion);
	friend Quaternion operator*(Quaternion, Quaternion);
};

