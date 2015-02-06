#include "Quaternion.h"


Quaternion::Quaternion()
{
	for (int i = 0; i < 4; i++)
		elements[i] = 0.0;
}

Quaternion::Quaternion(Vector<double, 4>* in)
{
	elements = *in;
}

Quaternion::Quaternion(double w, double x, double y, double z)
{
	elements[W] = w;
	elements[VX] = x;
	elements[VY] = y;
	elements[VZ] = z;
}
Quaternion::Quaternion(double p, double y, double r)
{
	double c1 = cos(y / 2.0);
	double s1 = sin(y / 2.0);
	double c2 = cos(p / 2.0);
	double s2 = sin(p / 2.0);
	double c3 = cos(r / 2.0);
	double s3 = sin(r / 2.0);
	double c1c2 = c1*c2;
	double s1s2 = s1*s2;
	elements[W] = c1c2*c3 - s1s2*s3;
	elements[VX] = c1c2*s3 + s1s2*c3;
	elements[VY] = s1*c2*c3 + c1*s2*s3;
	elements[VZ] = c1*s2*c3 - s1*c2*s3;
}

Quaternion::Quaternion(Vector<double, 3>* in)
{
	double c1 = cos((*in)[1] / 2.0);
	double s1 = sin((*in)[1] / 2.0);
	double c2 = cos((*in)[0] / 2.0);
	double s2 = sin((*in)[0] / 2.0);
	double c3 = cos((*in)[2] / 2.0);
	double s3 = sin((*in)[2] / 2.0);
	double c1c2 = c1*c2;
	double s1s2 = s1*s2;
	elements[W] = c1c2*c3 - s1s2*s3;
	elements[VX] = c1c2*s3 + s1s2*c3;
	elements[VY] = s1*c2*c3 + c1*s2*s3;
	elements[VZ] = c1*s2*c3 - s1*c2*s3;
}

Quaternion operator+(Quaternion left, Quaternion right)
{
	return Quaternion(&(left.elements+right.elements));
}

Quaternion operator*(Quaternion left, Quaternion right)
{
	Quaternion temp;
	temp[W] = (left[W] * right[W]) - (left[VX] * right[VX]) - (left[VY] * right[VY]) - (left[VZ] * right[VZ]);
	temp[VX] = left[VY] * right[VZ] - left[VZ] * right[VY] + right[VX] * left[W] + left[VX] * right[W];
	temp[VY] = (left[VX] * right[VZ] - left[VZ] * right[VX])*-1.0 + right[VY] * left[W] + left[VY] * right[W];
	temp[VZ] = left[VX] * right[VY] - left[VY] * right[VX] + right[VZ] * left[W] + left[VZ] * right[W];
	return temp;
}

double &Quaternion::operator[](const int& pos)
{
	return this->elements[pos];
}