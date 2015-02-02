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