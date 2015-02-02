#include <iostream>
#include "Vector.h"
#include "Vector.cpp"
using namespace std;


int main(int argc, char **argv)
{
	Vector<double, 3> test;
	Vector<double, 3> test2;
	test.setValue(0, 1.0);
	test.setValue(1, 1.0);
	test.setValue(2, 1.0);
	test2.setValue(0, 7.0);
	test2.setValue(1, 3.0);
	test2.setValue(2, 5.0);
	cout << test[X] << "\t" << test[Y] << "\t" << test[Z] << endl;
	//test = test2 * 2.0;
	cout << test[X] << "\t" << test[Y] << "\t" << test[Z] << endl;
	cout << (test & test2) << endl;
	return 0;
}