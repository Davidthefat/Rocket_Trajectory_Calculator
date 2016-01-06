#pragma once
#include "Quaternion.h"

#define LENGTH getAttribute(BodyLength)
#define DIAMETER getAttribute(Diameter)
#define NOSE_LENGTH getAttribute(NoseLength)
#define WEIGHT getAttribute(Weight)
#define WEIGHT_RATE getAttribute(WeightRate)
#define WEIGHT_EMPTY getAttribute(WeightEmpty)
#define CROSS_SECTION getAttribute(CrossSection)
#define AREA_THROAT getAttribute(AreaThroat)
#define AREA_RATIO getAttribute(NozzleAreaRatio)
#define THRUST getAttribute(Thrust)
#define BURNOUT getAttribute(Burnout)
#define DRAG getAttribute(Drag)
#define CD getAttribute(Cd)

enum value_t{
	BodyLength,		// in
	NoseLength,		// in
	Diameter,		// in
	Weight,			// lbf
	WeightRate,		// lbf/s
	WeightEmpty,	// lbf
	CrossSection,	// in^2
	AreaThroat,		// in^2
	NozzleAreaRatio,// Unitless
	Drag,			// lbf
	Thrust,			// lbf
	Burnout,
	Cd,				// Unitless
	Cg,				// ft; from nose
	Cp				// ft; from nose
};

class Vehicle
{
private:
	Vec3D *Position;
	Vec3D *Velocity;
	Vec3D *Acceleration;
	Vec3D *Attitude;		//0 X; 1 Y; 2 Z
	double Attributes[14];
public:
	Vehicle();
	Vehicle(double, double, double, double);
	~Vehicle();
	Vec3D getPosition();
	Vec3D getVelocity();
	Vec3D getAcceleration();
	Vec3D getAttitude();
	double getPosition(int);
	double getVelocity(int);
	double getAcceleration(int);
	double getAttitude(int);
	double getAttribute(int);
	void setAttribute(int, double);
	void setPosition(Vec3D);
	void setVelocity(Vec3D);
	void setAcceleration(Vec3D);
};

