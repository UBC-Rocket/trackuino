/*
 * Author: Peter Goubarev
 * Purpose: Recieves data from Honeywell barometer, model SSCSANN001BAAA3
 *
 * 

*/

#ifndef barometer_h
#define barometer_h


#include <Arduino.h>

void setupBarometer();
double measurePressure();
void measurePressureString(char pressureDP[5]);
double calculateAltitudeSimple(double p);

#endif barometer_h
