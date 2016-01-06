#include "Calculator.h"


Calculator::Calculator(Vehicle *in)
{
	Target = in;
	Filter = new KalmanFilter(1.0, 1.0, 1.0, 1.0);
	Env = new Environment();
	PositionBuf = new Vec3D();
	VelocityBuf = new Vec3D();
	AccelerationBuf = new Vec3D();
	AttitudeBuf = new Vec3D();
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
		Target->setAttribute(Weight, Target->WEIGHT - (Target->WEIGHT_RATE*dT));
	else
		Target->setAttribute(Burnout, 1.0);
}

void Calculator::calcCoefDrag()
{
    /*
	if (mach()>0.7)
		Target->setAttribute(Cd, cD());
    else
     */
        Target->setAttribute(Cd, 0.010);
}

void Calculator::calcDrag()
{
	double V = Target->getVelocity().abs();
	calcCoefDrag();
	double drag = 0.5*Target->CROSS_SECTION*Target->CD*RHO_SL*V*V;
	if (Target->getVelocity()[Y] < 0.0)
		drag *= -1.0;
	Target->setAttribute(Drag, drag);
}

void Calculator::calcExhaustMach()
{
	ExhaustMach = 1.0;
	double AR = Target->AREA_RATIO;
	auto AreaRatio = [](double mach){
		return pow(GAM_C, -0.5*(GAM_E)*pow((1.0 + ((GAM - 1.0)*mach*mach) / 2.0), 0.5*GAM_E))/mach; 
	};
	double E = AreaRatio(ExhaustMach) - AR;
	while (E > TOLERANCE || E < -TOLERANCE)
		if (E > TOLERANCE)
			E = AreaRatio(ExhaustMach += ExhaustMach / 2.0) - AR;
		else if (E < -TOLERANCE)
			E = AreaRatio(ExhaustMach -= ExhaustMach / 2.0) - AR;
}

void Calculator::calcExitPressure(double Pc)
{
	ExitPressure = Env->getPressure(Target->getPosition()[Y]);
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
	calcThrust(Pc, Pa, Tc);
	calcDrag();
	Vec3D TempAcc(0 ,Target->THRUST - Target->DRAG - Target->WEIGHT, 0);
	*AccelerationBuf = TempAcc;
}

void Calculator::calcVelocity(double dT)
{
	*VelocityBuf = Target->getVelocity() + ((Target->getAcceleration()*dT)+((*AccelerationBuf)*dT))*0.5;
}

void Calculator::calcPosition(double dT)
{
	*PositionBuf = Target->getPosition() + ((Target->getVelocity()*dT)+((*VelocityBuf)*dT))*0.5;
}

void Calculator::update(double Pc, double dT)
{
	if (Target->BURNOUT != 0.0)
		Pc = 0.0;
	calcAcceleration(Pc, Env->getPressure(Target->getPosition()[Y]), 1000.0, dT);
	calcVelocity(dT);
	calcPosition(dT);
	Target->setAcceleration(AccelerationBuf);
	Target->setVelocity(VelocityBuf);
	Target->setPosition(PositionBuf);
}
double Calculator::beta()
{
	return pow(Target->getVelocity().abs() / Env->getLocalAirSpeed(Target->getPosition()[Y]), 2) - 1.0;
}
double Calculator::vonKarman(double x, double L, double rMax)
{
	double theta = acos(1.0 - (2.0 * x) / L);
	return (rMax / SQRT_PI) * sqrt(theta - sin(2.0*theta)/2.0);
}
double Calculator::vonKarmanPrime(double x, double L, double rMax)
{
	double pos = 1.0 - 2.0 * x / L;
	double ac = acos(pos);
	return (rMax / SQRT_PI) * ((2 - 2 * cos(2 * ac)) / (L*sqrt(1 - ac*ac))*sqrt(ac - 0.5*sin(2 * ac)));
}
double Calculator::calcVelocityPotential(double x)
{
	double velPot = 0.0;
	double r = vonKarman(x, Target->NOSE_LENGTH, Target->DIAMETER);
	double b = beta();
	double temp = (M_PI*vonKarman(0.0, Target->NOSE_LENGTH, Target->DIAMETER)*vonKarmanPrime(0.0, Target->NOSE_LENGTH, Target->DIAMETER)*2.0) / sqrt(x*x + b*r*r);
	double curr = 0.0;
	for (int i = 1; i < 1000; i++)
	{
		curr = (M_PI*vonKarman(i*(Target->NOSE_LENGTH / 1000.0), Target->NOSE_LENGTH, Target->DIAMETER)*vonKarmanPrime(i*(Target->NOSE_LENGTH / 1000.0), Target->NOSE_LENGTH, Target->DIAMETER)*2.0) / sqrt(x*x + b*r*r);
		velPot += (temp + curr) / 2.0;
		temp = curr;
	}
	return velPot/(-4.0*M_PI);
}
double Calculator::cP(double x)
{
	double dX = 0.000001;
	double vK = vonKarman(x, Target->NOSE_LENGTH, Target->DIAMETER);
	double velPot = calcVelocityPotential(x) - calcVelocityPotential(x + dX);
	double velPotX = (velPot) / dX;
	double velPotR = (velPot) / (vK - vonKarman(x + dX, Target->NOSE_LENGTH, Target->DIAMETER));
	return -2.0 * velPotX - velPotR*velPotR;
}
double Calculator::cD()
{
	double cD = 0.0;
	double slope = 0.0;
	double rh = Env->getDensity(Target->getPosition()[Y]);
	double p = Env->getPressure(Target->getPosition()[Y]);
	double V = Target->getVelocity().abs();
	double area = 0.0;
	for (int i = 0; i < 1000; i++)
	{
		slope = vonKarmanPrime(i*(Target->NOSE_LENGTH / 1000.0), Target->NOSE_LENGTH, Target->DIAMETER);
		area = pow(vonKarman(i*(Target->NOSE_LENGTH / 1000.0), Target->NOSE_LENGTH, Target->DIAMETER), 2) * M_PI;
		cD += (1.0 / sqrt(slope*slope + 1.0)*(cP(i*(Target->NOSE_LENGTH / 1000.0))*2.0*rh*V*V + p))/2.0*rh*V*V;
	}
	return cD;
}
double Calculator::mach()
{
	return Target->getVelocity().abs() / Env->getLocalAirSpeed(Target->getPosition()[Y]);
}