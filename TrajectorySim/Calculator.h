#pragma once
#include "Vehicle.h"
#include "Environment.h"
#include "KalmanFilter.h"

const double RHO_SL = 0.074887;		// lbm/ft^3
const double G = 32.2;				// ft/s^2
const double GAM = 1.244;			// Unitless
const double TOLERANCE = 0.0001;		
const double CRITICAL_PRESSURE = 109.5;

#define GAM_E (GAM+1.0)/(GAM-1.0)
#define GAM_R (GAM-1.0)/GAM
#define GAM_L 2.0/(GAM+1.0)
#define GAM_C (GAM+1.0)/2.0
#define SQRT_PI 1.77245385090551602729816748

class Calculator
{
private:
	Vehicle *Target;
	Environment *Env;
	KalmanFilter *Filter;
	//Temporary Vehicle statistics
	Vec3D *PositionBuf;
	Vec3D *VelocityBuf;
	Vec3D *AccelerationBuf;
	Vec3D *AttitudeBuf;		//0 Pitch; 1 Yaw; 2 Roll; Radians

	double AirDensity;
	double ExhaustMach;
	double ExitPressure;
	double beta();
	double calcVelocityPotential(double);
	double vonKarman(double, double, double);
	double vonKarmanPrime(double, double, double);
	double cP(double);
	double cD();
	void calcLocalAirDensity();
	void calcCoefDrag();
	void calcDrag();
	void calcThrust(double, double, double);
	void calcWeightRate(double, double);
	void calcWeight(double);
	void calcExitPressure(double);
	void calcExhaustMach();
	void calcAcceleration(double, double, double, double);
	void calcVelocity(double);
	void calcPosition(double);
public:
	Calculator(Vehicle *);
	~Calculator();
	void update(double, double);
	double mach();
};