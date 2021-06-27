#include "sdlogging.h"
#include "config.h"
#include "aerostat_utils.h"
#include "windSensor.h"

void setupSd()
{
  if (!SD.begin(SD_SELECT_PIN)){

      Serial.println("Error! Could not start up SD card.");
      while(1);
    }
    File logFile = SD.open("aeroLog.csv", FILE_WRITE);
    if (logFile)
    {
      if(logFile.position() == 0)  // if the file is totally blank
      {
        Serial.println("File opened successfully.");
        logFile.println(F("Time,Latitude,Longitude,Data_string"));
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
  
