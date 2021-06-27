/*
 * Project: UBC Rocket - Whistler Blackcomb - Aerostat Subteam
 *          Weather Balloon Test Launch 1
 *          Functions to make Trackuino compatible with the Adafruit Ultimate GPS
 * Authors: Peter Goubarev
 * Date: Feb 16 2021
 *  
 * 
 */
#ifndef adaUlGps_h
#define adaUlGps_h

void adaUlRecievePosition(double *latMeasurement, double *longMeasurement, int *altitudeMeasurement, int *gpsTime);
void setupAdaUlGps(void);
void formatGpsDataAPRS(char [], int gpsBuffer, int *altitudeMeasurement);

#endif adaUlGps_h
