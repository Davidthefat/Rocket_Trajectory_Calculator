#pragma once
#include "Vec3D.h"

const double PRESSURE_ATM = 14.7;	// psi
const double R = 68.0;

class Environment
{
private:
	Vec3D Wind;
	double Pressure;	// psi; Barometric Pressure
	double Temperature; // R; Barometric Temperature
	double BaseAltitude;
	double Density;
public:
	Environment();
	double getPressure(double);
	double getTemperature(double);
	double getDensity(double);
	double getBaseAlt();
	double getLocalAirSpeed(double);
};

