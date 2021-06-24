/*
 * Project: UBC Rocket - Whistler Blackcomb - Aerostat Subteam
 *          Weather Balloon Test Launch 1
 *          Functions to make Trackuino compatible with the Adafruit Ultimate GPS
 * Authors: Peter Goubarev
 * 
 *  
 * 
 */

#include <Adafruit_GPS.h>

#include "adaUlGps.h"
#include "config.h"
#include "aerostat_utils.h"

// you can change the pin numbers to match your wiring:
#define GPSSerial Serial1
Adafruit_GPS GPS(&GPSSerial);


void setupAdaUlGps(void)
{
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);
  // Ask for firmware version
  GPSSerial.println(PMTK_Q_RELEASE);
}


void adaUlRecievePosition(unsigned long *timer, char gpsString[], int bufferLength, int *altitudeMeasurement)
{
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  /*if ((c) && (GPSECHO))
    Serial.write(c);*/

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  formatGpsDataAPRS(gpsString, bufferLength, altitudeMeasurement);
}


void formatGpsDataAPRS(char gpsString[], int bufferLength, int *altitudeMeasurement) {

    const char formatString[] = "%02d%02d%02dh%07s%c/%08s%c";
    //hhmmss[h][latitude][N][longitude][S]
    
    char gpsLatitude[8] = "0000.00";
    char gpsLatDir = 'N';
    char gpsLongitude[9] = "00000.00";
    char gpsLongDir = 'E';
    
    if (GPS.fix)
    {      
      dtostrf(GPS.latitude, 7, 2, gpsLatitude); //0000.00
      charPadString(gpsLatitude, '0', ' ', 1);
      
      dtostrf(GPS.longitude, 8, 2, gpsLongitude); //00000.00
      charPadString(gpsLongitude, '0', ' ', 1);

      if (GPS.altitude < 0)
      {
        *altitudeMeasurement = 0;
      }
      else
      {
        *altitudeMeasurement = (int)GPS.altitude;
      }
  
      gpsLatDir = GPS.lat;
      gpsLongDir = GPS.lon;
    }

    snprintf(gpsString, bufferLength, formatString, GPS.hour, GPS.minute, GPS.seconds, gpsLatitude, gpsLatDir, gpsLongitude, gpsLongDir);

}
