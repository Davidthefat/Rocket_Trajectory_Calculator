#pragma once
#include "Vector.h"
#include "Vector.cpp"

enum angle{ P, Y, R };

class Euler
{
private:
	Vector<double, 3> Angles;
public:
	Euler();
	Euler(double, double, double);
	~Euler();
	/*void rotate(Vector<double, 3>*);*/
	double &operator[](const int&);
};

