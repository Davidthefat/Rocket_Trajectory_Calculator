#include <iostream>
#include "Quaternion.h"
using namespace std;


int main(int argc, char **argv)
{
	Quaternion test(M_PI/2.0, 0.0, 0.0);
	for (int i = 0; i < 4; i++)
		cout << test[i] << "\t";
	cout << endl;
	return 0;
}