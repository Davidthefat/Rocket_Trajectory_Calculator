#pragma once
#include "Vector.h"

const double PRESSURE_ATM = 14.7;	// psi

class Environment
{
private:
	Vector<double, 3> Wind;
	double Pressure;	// psi; Barometric Pressure
	double Temperature; // R; Barometric Temperature
public:
	Environment();
	double getPressure();
	double getTemperature();
};

