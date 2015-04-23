#pragma once
#include "Vec3D.h"

const double PRESSURE_ATM = 14.7;	// psi

class Environment
{
private:
	Vec3D Wind;
	double Pressure;	// psi; Barometric Pressure
	double Temperature; // R; Barometric Temperature
	double BaseAltitude;
public:
	Environment();
	double getPressure();
	double getTemperature();
	double getBaseAlt();
};

