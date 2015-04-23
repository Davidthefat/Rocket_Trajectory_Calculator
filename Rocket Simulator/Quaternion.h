#pragma once
#include "Vec3D.h"
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
	Vec3D vector();
	void rotate(Vec3D*);
	double &operator[](const int&);
	friend Quaternion operator+(Quaternion, Quaternion);
	friend Quaternion operator*(Quaternion, Quaternion);
};

