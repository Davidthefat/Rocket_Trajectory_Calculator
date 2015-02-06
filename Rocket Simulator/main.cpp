#include <iostream>
#include "Quaternion.h"
using namespace std;


int main(int argc, char **argv)
{
	Quaternion test(0.0, 0.0, M_PI/4.0);
	Quaternion test2(M_PI/2.0, 0.0, 0.0);
	Vector<double, 3> Euler = test.toEuler();
	for (int i = 0; i < 3; i++)
		cout << Euler[i] * 180.0 / M_PI << ", ";
	cout << endl;
	test.rotate(&test2);
	Euler = test.toEuler();
	for (int i = 0; i < 3; i++)
		cout << Euler[i]*180.0/M_PI << ", ";
	cout << endl;
	return 0;
}