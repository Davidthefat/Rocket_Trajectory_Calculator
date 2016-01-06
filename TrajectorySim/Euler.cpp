#include "Euler.h"


Euler::Euler()
{
	for (int i = 0; i < 3; i++)
		Angles[i] = 0.0;
}
Euler::Euler(double p, double y, double r)
{
	Angles[Pitch] = p;
	Angles[Yaw] = y;
	Angles[Roll] = r;
}

Euler::~Euler()
{
}

double &Euler::operator[](const int& pos)
{
	return this->Angles[pos];
}
