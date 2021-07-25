/*
 * Author: Peter Goubarev
 * Purpose: Sd card logging for testing the wind sensor. Will be used to enable remote testing of the sensor and barometer.
 * 
*/


#ifndef sdlogging_h
#define sdlogging_h

#include <SPI.h>
#include <SD.h>

void setupSd();
void sdWriteLine(char logBuffer[100]);
void logData(char gpsString[], int altitudeValues[], int velocityValues[]);
void logDataNew(char gpsTime[7], double lat, double lon, int gpsAlt, double sensPressure, double sensTemp, int wind);


#endif sdlogging_h
