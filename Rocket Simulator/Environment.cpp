#include "Environment.h"


Environment::Environment()
{
	Pressure = 14.7;
	Temperature = 527.26;
	BaseAltitude = 0.0;
}

double Environment::getPressure()
{
	return Pressure;
}

double Environment::getTemperature()
{
	return Temperature;
}
double Environment::getBaseAlt()
{
	return BaseAltitude;
}