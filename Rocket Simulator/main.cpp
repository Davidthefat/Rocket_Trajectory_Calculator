#include <iostream>
#include "Calculator.h"
using namespace std;


int main(int argc, char **argv)
{
	Vehicle rocket(44.0, 28.0, 0.5, 25.0);
	Calculator calc(&rocket);
	double Pc = 485.75;
	cout << "Time\tWeight\tWeight Rate\tChamber Pressure\tThrust\tDrag\tu'\tv'\tw'\tu\tv\tw\tx\ty\tz\tMach" << endl;
	for (int i = 0; rocket.getPosition()[Y] >= 0.0; i++)
	{
		if ((rocket.WEIGHT - rocket.WEIGHT_EMPTY) < rocket.WEIGHT_RATE*4.0)
			Pc = Pc > 0.0 ? Pc -(rocket.WEIGHT - rocket.WEIGHT_EMPTY)/25.0: 0.0;
		
		calc.update(Pc, 0.01);

		cout << i*0.01 << "\t";
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
	return 0;
}