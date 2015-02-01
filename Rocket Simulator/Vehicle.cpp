#include "Vehicle.h"


Vehicle::Vehicle()
{
	Position = new Vector<double, 3>();
	Velocity = new Vector<double, 3>();
	Acceleration = new Vector<double, 3>();
	Attitude = new Vector<double, 3>();
	Attributes[Weight] = 100.0;
	Attributes[WeightEmpty] = 13.0;
	Attributes[AreaThroat] = 0.25;
	Attributes[NozzleAreaRatio] = 6.0;
	Attributes[WeightRate] = Attributes[Thrust] = Attributes[Drag] = 0.0;
}

Vehicle::Vehicle(double wght, double wghtEmpty, double areaThroat, double areaRatio)
{
	Position = new Vector<double, 3>();
	Velocity = new Vector<double, 3>();
	Acceleration = new Vector<double, 3>();
	Attitude = new Vector<double, 3>();
	Attributes[Weight] = wght;
	Attributes[WeightEmpty] = wghtEmpty;
	Attributes[AreaThroat] = areaThroat;
	Attributes[NozzleAreaRatio] = areaRatio;
	Attributes[WeightRate] = Attributes[Thrust] = Attributes[Drag] = 0.0;
}


Vehicle::~Vehicle()
{
	delete Position;
	delete Velocity;
	delete Acceleration;
	delete Attitude;
}
Vector<double, 3> Vehicle::getAcceleration()
{
	return *Acceleration;
}
void Vehicle::setAcceleration(Vector<double, 3> in)
{
	*Acceleration = in;
}
Vector<double, 3> Vehicle::getVelocity()
{
	return *Velocity;
}
double Vehicle::getPosition(int pos)
{
	return (*Position)[pos];
}
double Vehicle::getVelocity(int pos)
{
	return (*Velocity)[pos];
}
double Vehicle::getAcceleration(int pos)
{
	return (*Acceleration)[pos];
}
double Vehicle::getAttitude(int pos)
{
	return (*Attitude)[pos]*M_PI/180.0;
}
void Vehicle::setVelocity(Vector<double, 3> in)
{
	*Velocity = in;
}
Vector<double, 3> Vehicle::getPosition()
{
	return *Position;
}
void Vehicle::setPosition(Vector<double, 3> in)
{
	*Position = in;
}
double Vehicle::getAttribute(int pos)
{
	return Attributes[pos];
}

void Vehicle::setAttribute(int pos, double val)
{
	Attributes[pos] = val;
}