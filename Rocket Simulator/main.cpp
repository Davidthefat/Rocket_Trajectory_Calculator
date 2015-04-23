#include <iostream>
#include "Calculator.h"
using namespace std;


int main(int argc, char **argv)
{
	Vehicle rocket(220.0, 34.0, 0.5, 2.0);
	Calculator calc(&rocket);
	for (int i = 0; rocket.getPosition()[Y] >= 0.0; i++)
	{
		calc.update(0.01);
		for (int p = 0; p < 3; p++)
			cout << rocket.getAcceleration()[p] << "\t";
		for (int p = 0; p < 3; p++)
			cout << rocket.getVelocity()[p] << "\t";
		for (int p = 0; p < 3; p++)
			cout << rocket.getPosition()[p] << "\t";
		cout << endl;
	}
	return 0;
}