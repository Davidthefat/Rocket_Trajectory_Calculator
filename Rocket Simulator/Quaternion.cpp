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

Quaternion Quaternion::conj()
{
	Quaternion result((*this)[X], -(*this)[VX], -(*this)[VY], -(*this)[VZ]);
	return result;
}

Vector<double, 3> Quaternion::toEuler()
{
	Quaternion norm = this->norm();
	Vector<double, 3> result;
	result[X] = M_PI / 2.0;
	result[Y] = 2 * atan2(norm[VX], norm[VY]);
	result[Z] = 0.0;
	double temp = norm[VX] * norm[VY] + norm[VZ] * norm[W];
	if (temp > 0.499)
		return result;
	if (temp < -0.499)
		return result * -1.0;
	result[X] = asin(2 * temp);
	result[Y] = atan2(2 * norm[VY] * norm[W] - 2 * norm[VX] * norm[VZ],
		1 - 2 * norm[VY] * norm[VY] - 2 * norm[VZ] * norm[VZ]);
	result[Z] = atan2(2 * norm[VX] * norm[W] - 2 * norm[VY] * norm[VZ],
		1 - 2 * norm[VX] * norm[VX] - 2 * norm[VZ] * norm[VZ]);
	return result;
}

Quaternion operator+(Quaternion left, Quaternion right)
{
	return Quaternion(&(left.elements + right.elements));
}

Quaternion operator*(Quaternion left, Quaternion right)
{
	Quaternion temp;
	temp[W] = (left[W] * right[W]) - ((left[VX] * right[VX]) + (left[VY] * right[VY]) + (left[VZ] * right[VZ]));
	temp[VX] = (left[VY] * right[VZ] - left[VZ] * right[VY]) + right[VX] * left[W] + left[VX] * right[W];
	temp[VY] = (left[VZ] * right[VX] - left[VX] * right[VZ]) + right[VY] * left[W] + left[VY] * right[W];
	temp[VZ] = (left[VX] * right[VY] - left[VY] * right[VX]) + right[VZ] * left[W] + left[VZ] * right[W];
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

void Quaternion::rotate(Quaternion* in)
{
	*this = (*in) * (*this) * (*in).conj();
}

void Quaternion::rotate(Vector<double, 3>* in)
{
	Quaternion pitch(cos((*in)[X] / 2.0), sin((*in)[X] / 2.0),0,0);
	Quaternion yaw(cos((*in)[X] / 2.0), 0, sin((*in)[X] / 2.0), 0);
	Quaternion roll(cos((*in)[X] / 2.0), 0, 0, sin((*in)[X] / 2.0));
	Quaternion temp = pitch*yaw*roll;
	this->rotate(&temp);
}

double &Quaternion::operator[](const int& pos)
{
	return this->elements[pos];
}