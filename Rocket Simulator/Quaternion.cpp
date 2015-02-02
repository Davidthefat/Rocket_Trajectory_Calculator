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
	temp[0] = (left.elements[0] * right.elements[0]) + (left.elements|right.elements);
	temp[1] = left.elements[2] * right.elements[3] - left.elements[3] * right.elements[2] + right.elements[1] * left.elements[0] + left.elements[1] * right.elements[0];
	temp[2] = (left.elements[1] * right.elements[3] - left.elements[3] * right.elements[1])*-1.0 + right.elements[2] * left.elements[0] + left.elements[2] * right.elements[0];
	temp[3] = left.elements[1] * right.elements[2] - left.elements[2] * right.elements[1] + right.elements[3] * left.elements[0] + left.elements[3] * right.elements[0];
	return temp;
}

double &Quaternion::operator[](const int& pos)
{
	return this->elements[pos];
}