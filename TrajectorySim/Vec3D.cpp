#include "Vec3D.h"

Vec3D::Vec3D()
{
	elements = new Vector<double, 3>;
	(*elements)[X] = 0.0;
	(*elements)[Y] = 0.0;
	(*elements)[Z] = 0.0;
}

Vec3D::Vec3D(Vector<double, 3>* in)
{
	*elements = *in;
}
Vec3D::Vec3D(double x, double y, double z)
{
	elements = new Vector<double, 3>;
	(*elements)[X] = x;
	(*elements)[Y] = y;
	(*elements)[Z] = z;
}

double Vec3D::abs()
{
	double temp = 0.0;
	for (int i = 0; i < 3; i++)
		temp += (*elements)[i] * (*elements)[i];
	return sqrt(temp);
}
Vec3D &Vec3D::operator=(const Vec3D& in)
{
	*this->elements = *in.elements;
	return *this;
}
double &Vec3D::operator[](const int& pos)
{
	return (*this->elements)[pos];
}
Vec3D &Vec3D::operator+=(const Vec3D& right)
{
	for (int i = 0; i < 3; i++)
		(*this->elements)[i] += (*right.elements)[i];
	return *this;
}
Vec3D &Vec3D::operator*=(const Vec3D& right)
{
	for (int i = 0; i < 3; i++)
		(*this->elements)[i] *= (*right.elements)[i];
	return *this;
}
Vec3D &Vec3D::operator+=(double right)
{
	for (int i = 0; i < 3; i++)
		(*this->elements)[i] += right;
	return *this;
}
Vec3D &Vec3D::operator*=(double right)
{
	for (int i = 0; i < 3; i++)
		(*this->elements)[i] *= right;
	return *this;
}

Vec3D operator+(const Vec3D& left, const Vec3D& right)
{
    Vec3D temp = left;
	return temp += right;
}
Vec3D operator+(const Vec3D& left, double right)
{
    Vec3D temp = left;
	return temp += right;
}
Vec3D operator*(const Vec3D& left, const Vec3D& right)
{
    Vec3D temp = left;
	return temp *= right;
}
Vec3D operator*(const Vec3D& left, double right)
{
    Vec3D temp = left;
	return temp *= right;
}