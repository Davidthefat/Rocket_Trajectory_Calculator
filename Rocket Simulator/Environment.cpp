#include "Environment.h"


Environment::Environment()
{
	Pressure = 14.7;
	Temperature = 527.26;
	BaseAltitude = 0.0;
}

double Environment::getPressure(double alt) //Equations from NASA Glenn
{
	if (alt < 36152.0)
		Pressure = 2116.0 * pow((getTemperature(alt) - 459.7) / 518.6, 5.256);
	else if (alt >= 36152.0 && alt <= 82345)
		Pressure = 473.1*exp(1.73 - 0.000048*alt);
	else
		Pressure = 51.97*pow((getTemperature(alt) - 459.7) / 389.98, -11.388);
	return Pressure;
}

double Environment::getTemperature(double alt) //Equations from NASA Glenn
{
	if (alt < 36152.0)
		Temperature = 59.0 - 0.00356 * alt;
	else if (alt >= 36152.0 && alt <= 82345)
		Temperature = -70.0;
	else
		Temperature = -205.05 + 0.00164 * alt;
	return Temperature += 459.67;
}
double Environment::getDensity(double alt) //Equations from NASA Glenn
{
	return Density = getPressure(alt) / (1718 * (getTemperature(alt) + 459.7));
}
double Environment::getBaseAlt()
{
	return BaseAltitude;
}
double Environment::getLocalAirSpeed(double alt)
{
	return sqrt(1.4*((getTemperature(alt) - 459.7) / 1.8 + 273.15)*287.058);
}