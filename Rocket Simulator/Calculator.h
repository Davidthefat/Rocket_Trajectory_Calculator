#pragma once
#include "Vehicle.h"
#include "Environment.h"

const double RHO_SL = 0.074887;		// lbm/ft^3
const double G = 32.2;				// ft/s^2
const double GAM = 1.244;			// Unitless
const double TOLERANCE = 0.0001;
const double R = 68.0;				
const double CRITICAL_PRESSURE = 109.5;

#define GAM_E (GAM+1.0)/(GAM-1.0)
#define GAM_R (GAM-1.0)/GAM
#define GAM_L 2.0/(GAM+1.0)
#define GAM_C (GAM+1.0)/2.0

class Calculator
{
private:
	Vehicle *Target;
	Environment *Env;
	double AirDensity;
	double ExhaustMach;
	double ExitPressure;
	double PressureAltitude;
	double BaseAltitude;
	void calcLocalAirDensity();
	void calcDrag();
	void calcThrust(double, double, double);
	void calcWeightRate(double, double);
	void calcWeight(double);
	void calcExitPressure(double);
	void calcExhaustMach();
	void calcPressureAltitude(double);
public:
	Calculator(Vehicle *);
	~Calculator();
	void calcAcceleration(double, double, double, double);
	void calcVelocity(double);
	void calcPosition(double);
};