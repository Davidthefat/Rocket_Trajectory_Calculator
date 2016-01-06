#include "Vehicle.h"


Vehicle::Vehicle()
{
	Attitude[Y] = 1.0;
	Attributes[Weight] = 100.0;
	Attributes[BodyLength] = 114.0;
	Attributes[NoseLength] = 32.0;
	Attributes[WeightEmpty] = 13.0;
	Attributes[AreaThroat] = 0.25;
	Attributes[NozzleAreaRatio] = 6.0;
	Attributes[CrossSection] = (4.0/12.0)*M_PI;
	Attributes[WeightRate] = Attributes[Thrust] = Attributes[Drag] = Attributes[Burnout] = 0.0;
}

Vehicle::Vehicle(double wght, double wghtEmpty, double areaThroat, double areaRatio)
{
	Attitude[Y] = 1.0;
	Attributes[Weight] = wght;
	Attributes[WeightEmpty] = wghtEmpty;
	Attributes[BodyLength] = 114.0;
	Attributes[NoseLength] = 32.0;
	Attributes[AreaThroat] = areaThroat;
	Attributes[NozzleAreaRatio] = areaRatio;
	Attributes[CrossSection] = (4.0/12.0)*M_PI;
	Attributes[WeightRate] = Attributes[Thrust] = Attributes[Drag] = Attributes[Burnout] = 0.0;
}


Vehicle::~Vehicle()
{
    
}
Vec3D Vehicle::getAcceleration()
{
	return Acceleration;
}
void Vehicle::setAcceleration(Vec3D *in)
{
	Acceleration = *in;
}
Vec3D Vehicle::getVelocity()
{
	return Velocity;
}
Vec3D Vehicle::getAttitude()
{
	return Attitude;
}
double Vehicle::getPosition(int pos)
{
	return Position[pos];
}
double Vehicle::getVelocity(int pos)
{
	return Velocity[pos];
}
double Vehicle::getAcceleration(int pos)
{
	return Acceleration[pos];
}
double Vehicle::getAttitude(int pos)
{
	return Attitude[pos]*M_PI/180.0;
}
void Vehicle::setVelocity(Vec3D *in)
{
	Velocity = *in;
}
Vec3D Vehicle::getPosition()
{
	return Position;
}
void Vehicle::setPosition(Vec3D *in)
{
	Position = *in;
}
double Vehicle::getAttribute(int pos)
{
	return Attributes[pos];
}

void Vehicle::setAttribute(int pos, double val)
{
	Attributes[pos] = val;
}