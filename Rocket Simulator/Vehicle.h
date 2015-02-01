#pragma once
#include "Vector.h"
#include "Vector.cpp"

#define WEIGHT getAttribute(Weight)
#define WEIGHT_RATE getAttribute(WeightRate)
#define WEIGHT_EMPTY getAttribute(WeightEmpty)
#define CROSS_SECTION getAttribute(CrossSection)
#define AREA_THROAT getAttribute(AreaThroat)
#define AREA_RATIO getAttribute(NozzleAreaRatio)
#define THRUST getAttribute(Thrust)
#define DRAG getAttribute(Drag)
#define CD getAttribute(Cd)

enum value_t{
	Weight,			// lbf
	WeightRate,		// lbf/s
	WeightEmpty,	// lbf
	CrossSection,	// in^2
	AreaThroat,		// in^2
	NozzleAreaRatio,// Unitless
	Drag,			// lbf
	Thrust,			// lbf
	Cd,				// Unitless
	Cg,				// ft; from nose
	Cp				// ft; from nose
};

class Vehicle
{
private:
	Vector<double, 3> *Position;
	Vector<double, 3> *Velocity;
	Vector<double, 3> *Acceleration;
	Vector<double, 3> *Attitude;		//0 Pitch; 1 Yaw; 2 Roll; Radians
	double Attributes[10];
public:
	Vehicle();
	Vehicle(double, double, double, double);
	~Vehicle();
	Vector<double, 3> getPosition();
	Vector<double, 3> getVelocity();
	Vector<double, 3> getAcceleration();
	Vector<double, 3> getAttitude();
	double getPosition(int);
	double getVelocity(int);
	double getAcceleration(int);
	double getAttitude(int);
	double getAttribute(int);
	void setAttribute(int, double);
	void setPosition(Vector<double, 3>);
	void setVelocity(Vector<double, 3>);
	void setAcceleration(Vector<double, 3>);
};

