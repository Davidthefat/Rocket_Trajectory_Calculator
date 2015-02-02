#include <iostream>
#include "Quaternion.h"
using namespace std;


int main(int argc, char **argv)
{
	Quaternion test;
	Quaternion test2;
	test[W] = 49.0;
	test[VX] = -32.0;
	test[VY] = 8.0;
	test[VZ] = 1.0;
	test2[W] = 4.3;
	test2[VX] = 5.9;
	test2[VY] = 1.3;
	test2[VZ] = -3.7;
	test = test * test2;
	for (int i = 0; i < 4; i++)
		cout << test[i] << "\t";
	cout << endl;
	return 0;
}