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
void aprs_send(char gpsString[], int altitudeValues[], int velocityValues[])
{
  char temp[12];                   // Temperature (int/ext)
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
  ax25_send_string(gpsString);        // contains GPS time, longitude, long dir, latitude, lat dir
  ax25_send_byte('O');                // balloon type identifier is 'O'

  Serial.print(gpsString);
  Serial.print('O');

  for (int i = 0; i < MEASUREMENTS_PER_PERIOD; i++)
      {

        char altDP[6] = "00000";
        dtostrf(altitudeValues[i], 5, 0, altDP); //00000
        charPadString(altDP, '0', ' ', 1);
        
        char windDP[6] = "000.0";
        formatWindDataString(windDP, velocityValues[i]);
        charPadString(windDP, '0', ' ', 1);

        ax25_send_byte('a');
        ax25_send_string(altDP);
        ax25_send_byte('v');
        ax25_send_string(windDP);

        Serial.print('a');
        Serial.print(altDP);
        Serial.print('v');
        Serial.print(windDP);
      }
  
  ax25_send_string(APRS_COMMENT);     // Comment    
  ax25_send_footer();
  ax25_flush_frame();                 // Tell the modem to go

  Serial.println("");
}
