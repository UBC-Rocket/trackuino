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
int metersToFeet(int num);
float kilomToKnots(float num);
float minToDd(float num);

void compressLat(double latitude, char compressedChars[5]);
void compressLong(double longitude, char compressedChars[5]);
void compressAlt(int altitude, char compressedChars[3]);
void compressWind(int windSpeed, char compressedChars[3]);

void setup_testing_mode();
bool check_testing_mode();


#endif aerostat_utils_h
