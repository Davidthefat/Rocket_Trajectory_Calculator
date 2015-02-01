/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** KalmanFilter.h
** Implementation for a single variable Kalman Filter using only one input for 
** each prediction and measurement. Assumes process noise variance and
** measurement noise variance are constant to simplify algorithm. 
**
** Author: David Yoon
** -------------------------------------------------------------------------*/
#ifndef _KALMANFILTER_H
#define _KALMANFILTER_H
class KalmanFilter
{
private:
	float initEstimate;
	float estimateErr;
	float processNoise;
	float measurementNoise;
	float KalmanGain;
	float state;
public:
	//iE: Initial Estimate, eE: Estimate Error, pN: Process Noise, mN: Measurement Noise
	KalmanFilter(float iE, float eE, float pN, float mN);
	//in: Prediction estimate 
	void processEstimate(float in);
	//in: Measurement, returns latest estimate.
	float processCorrection(float in);
	//returns the Estimate Error, used to determine the "exactness" of the estimate.
	float error();
};
#endif
