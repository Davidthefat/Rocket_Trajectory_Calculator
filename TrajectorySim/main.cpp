#include <iostream>
#include "Calculator.h"
using namespace std;


int main(int argc, char **argv)
{
	Vehicle rocket(44.0, 25.0, 0.5, 25.0);
	Calculator calc(&rocket);
	double Pc = 485.75;
    double dT = 0.001;
	cout << "Time\tWeight\tWeight Rate\tChamber Pressure\tThrust\tDrag\tu'\tv'\tw'\tu\tv\tw\tx\ty\tz\tMach" << endl;
	for (int i = 0; rocket.getPosition()[Y] >= 0.0; i++)
	{
		if ((rocket.WEIGHT - rocket.WEIGHT_EMPTY) < rocket.WEIGHT_RATE)
			Pc = Pc > 0.0 ? Pc -(rocket.WEIGHT - rocket.WEIGHT_EMPTY)/250.0: 0.0;
		
		calc.update(Pc, dT);
        if(!(i%(int)(1.0/dT)))
        {
		cout << i*dT << "\t";
		cout << rocket.WEIGHT << "\t";
		cout << rocket.WEIGHT_RATE << "\t";
		cout << Pc << "\t";
		cout << rocket.THRUST << "\t";
		cout << rocket.DRAG << "\t";
		for (int p = 0; p < 3; p++)
			cout << rocket.getAcceleration()[p] << "\t";
		for (int p = 0; p < 3; p++)
			cout << rocket.getVelocity()[p] << "\t";
		for (int p = 0; p < 3; p++)
			cout << rocket.getPosition()[p] << "\t";
		cout << calc.mach() << "\t";
		cout << endl;
        }
	}
	return 0;
}