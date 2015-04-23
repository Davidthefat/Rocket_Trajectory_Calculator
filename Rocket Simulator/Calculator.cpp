#include "Calculator.h"


Calculator::Calculator(Vehicle *in)
{
	Target = in;
	Filter = new KalmanFilter(1.0, 1.0, 1.0, 1.0);
	Env = new Environment();
	PositionBuf = new Vector<double, 3>();
	VelocityBuf = new Vector<double, 3>();
	AccelerationBuf = new Vector<double, 3>();
	AttitudeBuf = new Vector<double, 3>();
}

Calculator::~Calculator()
{
	Target = nullptr; //Original Vehicle object is preserved; must be freed independently.
	delete Filter;
	delete Env;
	delete PositionBuf;
	delete VelocityBuf;
	delete AccelerationBuf;
	delete AttitudeBuf;
}

void Calculator::calcWeight(double dT)
{
	if (Target->WEIGHT - Target->WEIGHT_RATE > Target->WEIGHT_EMPTY)
		Target->setAttribute(Weight, Target->WEIGHT - Target->WEIGHT_RATE);
}

void Calculator::calcCoefDrag()
{

}

void Calculator::calcDrag()
{
	double V = Target->getVelocity()[Z];
	calcCoefDrag();
	double drag = 0.5*Target->CROSS_SECTION*Target->CD*RHO_SL*V*V;
	Target->setAttribute(Drag, drag);
}

void Calculator::calcExhaustMach()
{
	double AR = Target->AREA_RATIO;
	auto AreaRatio = [](double mach){
		return pow(GAM_C, -0.5*(GAM_E)*pow((1.0 + ((GAM - 1.0)*mach*mach) / 2.0), 0.5*GAM_E))/mach; 
	};
	double E = AreaRatio(ExhaustMach) - AR;
	while (E > TOLERANCE || E < -TOLERANCE)
		if (E > TOLERANCE)
			E = AreaRatio(ExhaustMach -= ExhaustMach / 2.0) - AR;
		else if (E < -TOLERANCE)
			E = AreaRatio(ExhaustMach += ExhaustMach / 2.0) - AR;
}

void Calculator::calcExitPressure(double Pc)
{
	double AR = Target->AREA_RATIO;
	auto AreaRatio = [Pc](double ePressure){
		return pow(GAM_L, 1.0 / (GAM - 1.0))*pow(Pc / ePressure, 1.0 / GAM) / sqrt(GAM_E * (1.0 - pow(ePressure / Pc, (GAM - 1.0) / GAM))); 
	};
	double E = AreaRatio(ExitPressure) - AR;
	while (E > TOLERANCE || E < -TOLERANCE)
		if (E > TOLERANCE)
			E = AreaRatio(ExitPressure += ExitPressure / 2.0) - AR;
		else if (E < -TOLERANCE)
			E = AreaRatio(ExitPressure -= ExitPressure / 2.0) - AR;
}

void Calculator::calcPressureAltitude(double Pa)
{
	PressureAltitude = (1 - pow((Env->getPressure()*68.95 / 1013.25), 0.190284))*145366.45 - BaseAltitude;
}

void Calculator::calcWeightRate(double Pc, double Tc)
{
	Target->setAttribute(WeightRate, Target->AREA_THROAT*Pc*sqrt((G*GAM*pow(GAM_L, GAM_E)) / (R*Tc)));
}

void Calculator::calcThrust(double Pc, double Pa, double Tc)
{
	double AR = Target->AREA_RATIO;
	calcExitPressure(Pc);
	double Pe = ExitPressure;
	double At = Target->AREA_THROAT;
	double C = sqrt(G*GAM*R*Tc) / (GAM*sqrt(pow(GAM_L, GAM_E)));
	double Cf = (sqrt(2.0*GAM*GAM / (GAM - 1.0)*pow(2 / (GAM + 1.0), GAM_E)*(1.0 - pow(Pe / Pc, (GAM - 1.0) / GAM))) + AR*((Pe - Pa) / Pc));
	if (Pc <= CRITICAL_PRESSURE)//Thrust calculations break down if the Pc dips under this point. 
		Cf = 0.0;
	Target->setAttribute(Thrust, Pc*At*Cf);
}

void Calculator::calcAcceleration(double Pc, double Pa, double Tc, double dT)
{
	calcExhaustMach();
	calcExitPressure(Pc);
	calcWeightRate(Pc, Tc);
	calcWeight(dT);
	calcDrag();
	double TempAcc = Target->THRUST - Target->DRAG - Target->WEIGHT;
	
}

void Calculator::calcVelocity(double dT)
{
	*VelocityBuf = Target->getVelocity() + (Target->getAcceleration()*dT);
}

void Calculator::calcPosition(double dT)
{
	*PositionBuf = Target->getPosition() + (Target->getVelocity()*dT);
}

