#include <iostream>
#include "Quaternion.h"
using namespace std;


int main(int argc, char **argv)
{
	Quaternion Pitch(toRad(0.0), toRad(0.0), toRad(45.0));
	Vector<double, 3> Test;
	Test[0] = 0.0;
	Test[1] = 1.0;
	Test[2] = 0.0;
	for (int i = 0; i < 3; i++)
		cout << Test[i] << "\t";
	cout << endl;
	Pitch.rotate(&Test);
	for (int i = 0; i < 3; i++)
		cout << Test[i] << "\t";
	cout << endl;
	return 0;
}