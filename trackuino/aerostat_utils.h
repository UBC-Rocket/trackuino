/*
 * Author: Peter Goubarev
 * Purpose: Random functions
 *
 * 

*/

#ifndef aerostat_utils_h
#define aerostat_utils_h

void charPadString(char str[], char replacer, char special, int mode);

char intToBase91(int num);
float metersToFeet(float num);
float kilomToKnots(float num);
float minToDd(float num);

void compressLat(double latitude, char compressedChars[4]);
void compressLong(double longitude, char compressedChars[4]);
void compressAlt(int altitude, char compressedChars[2]);
void compressWind(int windSpeed, char compressedChars[2]);

#endif aerostat_utils_h
