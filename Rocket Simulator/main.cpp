#include <iostream>
#include "Quaternion.h"
using namespace std;


int main(int argc, char **argv)
{
	Quaternion test(0.0, 0.0, 0.0,0.0);
	Quaternion test2(0.0, M_PI / 4.0, 0.0);
	
	for (int i = 0; i < 4; i++)
		cout << test[i] << ", ";
	cout << endl;
	test.rotate(&test2);
	for (int i = 0; i < 4; i++)
		cout << test[i] << ", ";
	cout << endl;
	return 0;
}