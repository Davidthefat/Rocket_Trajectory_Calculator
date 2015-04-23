#include "Euler.h"


Euler::Euler()
{
	for (int i = 0; i < 3; i++)
		Angles[i] = 0.0;
}
Euler::Euler(double p, double y, double r)
{
	Angles[P] = p;
	Angles[Y] = y;
	Angles[R] = r;
}

Euler::~Euler()
{
}

double &Euler::operator[](const int& pos)
{
	return this->Angles[pos];
}

//void Euler::rotate(Vector<double, 3>* in)
//{
//	Quaternion pitch(cos(Angles[P] / 2.0), 0.0, sin(Angles[P] / 2.0), 0.0);
//	Quaternion yaw(cos(Angles[Y] / 2.0), 0.0, 0.0, sin(Angles[Y] / 2.0));
//	Quaternion roll(cos(Angles[R] / 2.0), sin(Angles[R] / 2.0), 0.0, 0.0);
//	Quaternion result = yaw*pitch*roll;
//	result.rotate(in);
//}