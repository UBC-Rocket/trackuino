#include "sdlogging.h"
#include "config.h"
#include "aerostat_utils.h"
#include "windSensor.h"
#include "barometer.h"

void setupSd()
{
  if (!SD.begin(SD_SELECT_PIN)){

      Serial.println("Error! Could not start up SD card.");
      while(1);
    }
    File logFile = SD.open("log.csv", FILE_WRITE);
    if (logFile)
    {
      if(logFile.position() == 0)  // if the file is totally blank
      {
        Serial.println("File opened successfully.");
        logFile.println(F("Time,Latitude,Longitude,GPS Alt,Sens Alt,Sens Temp, Windspeed"));
      }
    }
    logFile.println("Arduino restarted");
    logFile.close(); 
}



void sdWriteLine(char logBuffer[100])
{
  File logFile = SD.open("aeroLog.csv", FILE_WRITE);
    if (logFile)
    {
        Serial.println("File opened successfully.");
        logFile.println(logBuffer);
    }
    logFile.close();
}

/*
* Old function, deprecated.
*/
void logData(char gpsString[], int altitudeValues[], int velocityValues[])
{
  File logFile = SD.open("aeroLog.csv", FILE_WRITE);
  if (logFile)
  {
      //logFile.seek(EOF);
      Serial.println("File opened successfully.");
      logFile.print(gpsString);
      logFile.print(',');

      for (int i = 0; i < SENS_MEASUREMENTS_PER_PERIOD; i++)
      {

          char altDP[6] = "00000";
          dtostrf(altitudeValues[i], 5, 0, altDP); //00000
          charPadString(altDP, '0', ' ', 1);
          
          char windDP[4] = "000";
          formatWindDataString(windDP, velocityValues[i]);
          charPadString(windDP, '0', ' ', 1);
    
          //logFile.print('a');
          logFile.print(altDP);
          logFile.print(',');
          //logFile.print('v');
          logFile.print(windDP);
          logFile.print(',');
      }
      logFile.print('\n');
  }
  logFile.close();
}

/*
* Logs GPS and sensor data once for every SENSOR measurement (so if measuring sensors more times than GPS, the GPS
* position might not match that which will be transmitted).
*/
void logDataNew(char gpsTime[7], double lat, double lon, int gpsAlt, double sensPressure, double sensTemp, int wind)
{
    File logFile = SD.open("log.csv", FILE_WRITE);
    if (logFile)
    {
      Serial.println(F("File opened successfully for logging"));
      
      logFile.print(gpsTime);
      logFile.print(',');
      logFile.print(minToDd(lat), 4); // In dd
      logFile.print(',');
      logFile.print(minToDd(lon), 4); // In dd
      logFile.print(',');
      logFile.print(metersToFeet(gpsAlt)); // In feet
      logFile.print(',');
      logFile.print(metersToFeet(calculateAltitudeSimple(sensPressure))); // In feet
      logFile.print(',');
      logFile.print(sensPressure, 4); // in Pa
      logFile.print(',');
      logFile.print(sensTemp, 4); // in C
      logFile.print(',');
      logFile.print(kilomToKnots(wind)); // in knots
      logFile.print('\n');
    }

    logFile.close();
}

  
