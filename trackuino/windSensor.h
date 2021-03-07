/*
* Original Author: Paul Badger, Modern Device
* Modified by: Peter Goubarev, UBC Rocket - Whistler-Blackcomb - Aerostat Subteam, 2020
* Code in the public domain
* 
* Date: Dec 18 2020
* 
* Collection of functions for using the Modern Device Rev. P wind sensor 
* 
* 

*/

#ifndef windSensor_h
#define windSensor_h

#include <Arduino.h>


float measureRevpWind();
void formatWindDataString(char windDP[], double measurement);
float measureRevpTemp();
void measureRevpTempString(char tempDP[]);

#endif windSensor_h
