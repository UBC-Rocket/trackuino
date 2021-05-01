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

void adaUlRecievePosition(unsigned long *timer, char gpsString[], int bufferLength, int *altitudeMeasurement);
void setupAdaUlGps(void);
void formatGpsDataAPRS(char gpsString[], int gpsBuffer, int *altitudeMeasurement);

#endif adaUlGps_h
