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

double &Quaternion::operator[](const int& pos)
{
	return this->elements[pos];
}