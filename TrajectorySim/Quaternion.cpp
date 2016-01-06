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


Quaternion::Quaternion(Euler* in)
{
	double c1 = cos((*in)[Roll] / 2.0);
	double s1 = sin((*in)[Roll] / 2.0);
	double c2 = cos((*in)[Pitch] / 2.0);
	double s2 = sin((*in)[Pitch] / 2.0);
	double c3 = cos((*in)[Yaw] / 2.0);
	double s3 = sin((*in)[Yaw] / 2.0);
	elements[W] = c1*c2*c3 + s1*s2*s3;
	elements[VX] = s1*c2*c3 - c1*s2*s3;
	elements[VY] = c1*s2*c3 + s1*c2*s3;
	elements[VZ] = c1*c2*s3 - s1*s2*c3;
}


Quaternion Quaternion::conj()
{
	Quaternion result((*this)[W], -(*this)[VX], -(*this)[VY], -(*this)[VZ]);
	return result;
}

Euler Quaternion::toEuler()
{
	Euler result;
	result[Pitch] = asin(2 * (elements[W] * elements[VY] - elements[VZ] * elements[VX]));
	result[Yaw] = atan2(2 * (elements[W] * elements[VZ] + elements[VX] * elements[VY]), 1 - 2 * (elements[VY] * elements[VY] + elements[VZ] * elements[VZ]));
	result[Roll] = atan2(2 * (elements[W] * elements[VX] + elements[VY] * elements[VZ]), 1 - 2 * (elements[VX] * elements[VX] + elements[VY] * elements[VY]));
	return result;
}
Quaternion operator+(Quaternion left, Quaternion right)
{
    Vector<double, 4> temp = left.elements + right.elements;
	return Quaternion(&temp);
}

Quaternion operator*(Quaternion left, Quaternion right)
{
	Quaternion temp;
	temp[W] = left[W] * right[W] - left[VX] * right[VX] - left[VY] * right[VY] - left[VZ] * right[VZ];
	temp[VX] = left[W] * right[VX] + left[VX] * right[W] + left[VY] * right[VZ] - left[VZ] * right[VY];
	temp[VY] = left[W] * right[VY] - left[VX] * right[VZ] + left[VY] * right[W] + left[VZ] * right[VX];
	temp[VZ] = left[W] * right[VX] + left[VX] * right[VY] - left[VY] * right[VX] + left[VZ] * right[W];
	return temp;
}
Quaternion Quaternion::norm()
{
	Quaternion result;
	double temp = 0.0;
	for (int i = 0; i < 4; i++)
		temp += (*this)[i] * (*this)[i];
	temp = sqrt(temp);
	for (int i = 0; i < 4; i++)
		result[i] = (*this)[i] / temp;
	return result;
}
Vec3D Quaternion::vector()
{
	Vec3D temp;
	temp[X] = elements[VX];
	temp[Y] = elements[VY];
	temp[Z] = elements[VZ];
	return temp;
}
void Quaternion::rotate(Vec3D* in)
{
	Quaternion result(0.0, (*in)[0], (*in)[1], (*in)[2]);
	result = (*this) * result * (this->conj());
	*in = result.vector();
}


double &Quaternion::operator[](const int& pos)
{
	return this->elements[pos];
}