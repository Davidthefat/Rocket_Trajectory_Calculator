#include <iostream>
#include "Quaternion.h"
using namespace std;


int main(int argc, char **argv)
{
	Quaternion Pitch(45,0,0);
	Quaternion Test(0, 2, 0, 0);
	Test.rotate(&Pitch.toEuler());
	Vector<double, 3> Euler = Test.toEuler();
	for (int i = 0; i < 3; i++)
		cout << Euler[i] * 180.0/M_PI << "\t";
	cout << endl;
	for (int i = 0; i < 4; i++)
		cout << Test[i] << "\t";
	cout << endl;
	return 0;
}