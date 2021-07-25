/*
 * Random functions
*/

#include "aerostat_utils.h"
#include <string.h>
#include <Arduino.h>

/*
Pads a string with a desired character.

Param str: pointer to the string to be modified.
Param replacer: the character you want to pad with
Param special: has 2 uses depending on mode selected:
                Mode 0: every character will be replaced with the replacer until the first occurence of the special (special char will be ignored)
                Mode 1: every character will be replaced with the replacer until the first character that ISN'T the "special" is encountered
Parma mode: determines whether the "special" paremeter tells the function to stop or to continue. See description above.

*/
void charPadString(char str[], char replacer, char special, int mode)
{
  char c = str[0];
  int i = 0;

  if (mode == 0)
  {
    while (c != special && i < strlen(str))
      {
        str[i] = replacer;
        i++;
        c = str[i];
      }
  }
  else if (mode == 1)
  {
    while (c == special && i < strlen(str))
    {
      str[i] = replacer;
      i++;
      c = str[i];
    }
  }
}

/*
 * Converts a number between 0 and 91 to a number in base91
*/
char intToBase91(int num)
{
    return (char)(num + 33);
}

/*
 * Converts a distance in meters to a distance in feet.
*/
int metersToFeet(int num)
{
    return (int)((float)num*3.2808399);
}

/*
 * Converts a speed from km/h to knots (to abide by APRS Base91 conventions)
*/
float kilomToKnots(float num)
{

    return num*0.539956803;
}


/*
 * Takes a latitude or longitude value in [degrees][minutes].[decimal minutes] format and converts to [degrees].[decimal degrees]
*/
float minToDd(float num)
{
    int sign = 1;
    float x = abs(num);

    if (num < 0)
    {
      sign = -1;
    }

    x /= 100.0; // from 4910.82 to 49.1082
    float degreesPart = floor(x);
    float minutesPart = x - degreesPart;
    return sign*(degreesPart + minutesPart/0.60);
}


/*
 * Compresses a latitude value down to a 4-character number in base91
 * The latitude should have a sign (negative for south).
*/
void compressLat(double latitude, char compressedChars[5])
{
    long base91 = 380926.0*(90.0 - latitude);
                    
    for (int i = 0; i < 3; i++)                       // Divide base91 by 91^n repeatedly, starting from n=3 and ending at n=1.
    {

      compressedChars[i] = intToBase91((int)floor(base91/pow(91, 3-i)));
      base91 = base91 % (long)pow(91, 3-i);
    }
    
    compressedChars[3] = intToBase91(base91);                         //last value is the final remainder.
    compressedChars[4] = '\0'; 
    
}

/*
 * Compresses a longitude value down to a 4-character number in base91
*/
void compressLong(double longitude, char compressedChars[5])
{
    long base91 = 190463 * (180 + longitude);
                    
    for (int i = 0; i < 3; i++)                       // Divide base91 by 91^n repeatedly, starting from n=3 and ending at n=1.
    {
      compressedChars[i] = intToBase91((int)floor(base91/pow(91, 3-i)));
      base91 = base91 % (long)pow(91, 3-i);
    }
    
    compressedChars[3] = intToBase91(base91);                         //last value is the final remainder.
    compressedChars[4] = '\0';  
    
}

/*
 * Compresses an integer for altitude down to a 2-character number in base91
 * Altitude should be in feet
*/
void compressAlt(int altitude, char compressedChars[3])
{
    long base91 = (long)round((log(altitude)/log(1.002))); //1.002 logarithm of altitude; intentional.
    compressedChars[0] = intToBase91(base91 / 91);
    compressedChars[1] = intToBase91(base91 % 91);
    compressedChars[2] = '\0'; 
    
}

/*
 * Compresses an integer for wind speed dow nto a 1-character number in base91
*/
void compressWind(int windSpeed, char compressedChars[2])
{

    int base91 = (int)round((log(windSpeed + 1)/log(1.08))); //1.08 logarithm of (wind speed + 1)
    compressedChars[0] = intToBase91(base91 % 91);
    compressedChars[1] = '\0';
}
