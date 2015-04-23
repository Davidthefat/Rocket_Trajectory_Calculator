#include <iostream>
#include "Quaternion.h"
using namespace std;


int main(int argc, char **argv)
{
	Quaternion Pitch(toRad(45.0), toRad(0.0), toRad(0.0));
	Vector<double, 3> Test;
	Test[0] = 0.0;
	Test[1] = 0.0;
	Test[2] = 1.0;

	Euler PitchEuler = Pitch.toEuler();
	for (int i = 0; i < 3; i++)
		cout << toDeg(PitchEuler[i]) << "\t";
	cout << endl;
	for (int i = 0; i < 4; i++)
		cout << Pitch[i] << "\t";
	cout << endl;
	for (int i = 0; i < 3; i++)
		cout << Test[i] << "\t";
	cout << endl;
	Pitch.rotate(&Test);
	for (int i = 0; i < 3; i++)
		cout << Test[i] << "\t";
	cout << endl;
	return 0;
}