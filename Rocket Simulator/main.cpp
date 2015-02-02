#include <iostream>
#include "Quaternion.h"
using namespace std;


int main(int argc, char **argv)
{
	Quaternion test;
	Quaternion test2;
	test[0] = -16.0;
	test[1] = 3.0;
	test[2] = 4.0;
	test[3] = 3.0;
	test2[0] = 4.0;
	test2[1] = 3.9;
	test2[2] = -1.0;
	test2[3] = -3.0;
	test = test * test2;
	for (int i = 0; i < 4; i++)
		cout << test[i] << "\t";
	cout << endl;
	return 0;
}