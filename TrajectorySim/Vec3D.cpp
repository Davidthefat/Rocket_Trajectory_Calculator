#include "Vec3D.h"

Vec3D::Vec3D()
{
	elements[X] = 0.0;
	elements[Y] = 0.0;
	elements[Z] = 0.0;
}

Vec3D::Vec3D(Vector<double, 3>* in)
{
	elements = *in;
}
Vec3D::Vec3D(double x, double y, double z)
{
	elements[X] = x;
	elements[Y] = y;
	elements[Z] = z;
}

double Vec3D::abs()
{
	double temp = 0.0;
	for (int i = 0; i < 3; i++)
		temp += elements[i] * elements[i];
	return sqrt(temp);
}
Vec3D &Vec3D::operator=(const Vec3D& in)
{
    double temp;
    for(int i = 0; i < 3; i ++)
    {
        temp = in[i];
        elements[i] = temp;
    }
	return *this;
}

double &Vec3D::operator[](const int& pos)
{
	return elements[pos];
}
double &Vec3D::operator[](const int& pos)const
{
    return elements[pos];
}
Vec3D &Vec3D::operator+=(const Vec3D& right)
{
	for (int i = 0; i < 3; i++)
		(*this)[i] += right[i];
	return *this;
}
Vec3D &Vec3D::operator*=(const Vec3D& right)
{
	for (int i = 0; i < 3; i++)
		(*this)[i] *= right[i];
	return *this;
}
Vec3D &Vec3D::operator+=(double right)
{
	for (int i = 0; i < 3; i++)
		(*this)[i] += right;
	return *this;
}
Vec3D &Vec3D::operator*=(double right)
{
	for (int i = 0; i < 3; i++)
		(*this)[i] *= right;
	return *this;
}

Vec3D Vec3D::operator+(const Vec3D& right)const
{
    Vec3D temp;
    temp = *this;
	return temp += right;
}
Vec3D Vec3D::operator+(double right)const
{
    Vec3D temp;
    temp = *this;
	return temp += right;
}
Vec3D Vec3D::operator*(const Vec3D& right)const
{
    Vec3D temp;
    temp = *this;
	return temp *= right;
}
Vec3D Vec3D::operator*(double right)const
{
    Vec3D temp;
    temp = *this;
	return temp *= right;
}