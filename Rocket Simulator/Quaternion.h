#pragma once
#include "Vector.h"
class Quaternion :
	public Vector<double, 4>
{
private:
	Vector<double, 4> elements;
public:
	Quaternion();
};

