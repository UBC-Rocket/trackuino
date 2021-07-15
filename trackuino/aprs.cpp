/* trackuino copyright (C) 2010  EA5HAV Javi
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "config.h"
#include "ax25.h"
#include "aprs.h"
#include "aerostat_utils.h"
#include "windSensor.h"
#include "adaUlGps.h"
#include <stdio.h>
#include <stdlib.h>
#if (ARDUINO + 1) >= 100
#  include <Arduino.h>
#else
#  include <WProgram.h>
#endif

// Module functions
float meters_to_feet(float m)
{
  // 10000 ft = 3048 m
  return m / 0.3048;
}

// Exported functions
void aprs_send(double latitudeValues[], double longitudeValues[], int altitudeValues[], double velocityValues[], char gpsTimeString[7])
{
  char latString[5];
  char longString[5];
  char altString[3];
  char velocityString[3];
  const struct s_address addresses[] = { 
    {D_CALLSIGN, D_CALLSIGN_ID},  // Destination callsign
    {S_CALLSIGN, S_CALLSIGN_ID},  // Source callsign (-11 = balloon, -9 = car)
#ifdef DIGI_PATH1
    {DIGI_PATH1, DIGI_PATH1_TTL}, // Digi1 (first digi in the chain)
#endif
#ifdef DIGI_PATH2
    {DIGI_PATH2, DIGI_PATH2_TTL}, // Digi2 (second digi in the chain)
#endif
  };

  ax25_send_header(addresses, sizeof(addresses)/sizeof(s_address));
  ax25_send_byte('/');                // Symbol table to seperate different strings while printed
  Serial.print('/');

  //dtostrf(gpsTime, 6, 0, gpsTimeString);
  charPadString(gpsTimeString, '0', ' ', 1);
  
  ax25_send_string(gpsTimeString);
  ax25_send_byte('h');
  Serial.print(gpsTimeString);
  Serial.print('h');
  
  ax25_send_byte('/'); //Change this?
  Serial.print('/');

  compressLat(minToDd(latitudeValues[GPS_MEASUREMENTS_PER_PERIOD - 1]), latString);
  compressLong(minToDd(longitudeValues[GPS_MEASUREMENTS_PER_PERIOD - 1]), longString);
  ax25_send_string(latString);
  ax25_send_string(longString);
  Serial.print(latString);
  Serial.print(longString);

  ax25_send_byte('b');                // balloon type identifier is 'O', 'b' for bicycle
  compressAlt(metersToFeet(altitudeValues[SENS_MEASUREMENTS_PER_PERIOD - 1]), altString); //Convert latest alt. to feet, then compress.
  ax25_send_string(altString);
  Serial.print(altString);
  Serial.print('b');                  //'O' for balloon, 'b' for bicycle

  
  ax25_send_byte('S'); //Tells APRS-IS about the source of compression, of gps data, etc. 
  Serial.print('S');
  // Important because two of the binary digits that make up the S tell APRS-IS that the preceding two characters are for altitude. 
  
  for (int i = 0; i < (GPS_MEASUREMENTS_PER_PERIOD - 1); i++) //minus two because the latest GPS position has already been transmitted.
  {
      compressLat(minToDd(latitudeValues[i]), latString);
      compressLong(minToDd(longitudeValues[i]), longString);
      ax25_send_string(latString);
      ax25_send_string(longString);
      Serial.print(latString);
      Serial.print(longString);
  }
  
  for (int i = 0; i < (SENS_MEASUREMENTS_PER_PERIOD - 1); i++)
  {
      compressAlt(metersToFeet(altitudeValues[i]), altString); //Convert latest alt. to feet, then compress.
      compressWind(kilomToKnots(velocityValues[i]), velocityString);
      ax25_send_string(altString);
      ax25_send_string(velocityString);
      Serial.print(altString);
      Serial.print(velocityString);
  }
  
  //The last wind speed datapoint, which hasnt been transmitted yet.
  compressWind(kilomToKnots(velocityValues[SENS_MEASUREMENTS_PER_PERIOD - 1]), velocityString);
  ax25_send_string(velocityString);
  
  ax25_send_string(APRS_COMMENT);     // Comment    
  ax25_send_footer();
  ax25_flush_frame();                 // Tell the modem to go

  Serial.println("");
}
