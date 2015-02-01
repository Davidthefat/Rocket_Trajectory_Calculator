/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** KalmanFilter.cpp
** Implementation for a single variable Kalman Filter using only one input for 
** each prediction and measurement. Assumes process noise variance and
** measurement noise variance are constant to simplify algorithm. 
**
** Author: David Yoon
** -------------------------------------------------------------------------*/
#include "KalmanFilter.h"
KalmanFilter::KalmanFilter(float iE, float eE, float pN, float mN)
{
	initEstimate = iE;
	estimateErr = eE;
	processNoise = pN;
	measurementNoise = mN;
}
void KalmanFilter::processEstimate(float in)
{
	initEstimate = in;
	estimateErr += processNoise;
}
float KalmanFilter::processCorrection(float in)
{
	KalmanGain = estimateErr/(estimateErr + measurementNoise);
	state = initEstimate + KalmanGain*(in - initEstimate);
	estimateErr *= (1 - KalmanGain);
	return state;
}
float KalmanFilter::error()
{
	return estimateErr;
}
