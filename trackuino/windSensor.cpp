#include "windSensor.h"
#include "config.h"
#include "aerostat_utils.h"
#include <math.h>

/*Returns wind measurement in KPH from Modern Device Rev P Wind Sensor.*/
float measureRevpWind()
{
  // read wind
  int windADunits = analogRead(WIND_OUTPUT_PIN);
  // Serial.print("RW ");   // print raw A/D for debug
  // Serial.print(windADunits);
  // Serial.print("\t");
  
  
  // wind formula derived from a wind tunnel data, annemometer and some fancy Excel regressions
  // this scalin doesn't have any temperature correction in it yet
  float windMPH =  pow((((float)windADunits - 264.0) / 85.6814), 3.36814);
  //Serial.println(windMPH*1.60934);
  return windMPH * 1.60934; //that's KPH
    
}


void formatWindDataString(char windDP[], double measurement)
{
  if (isnan(measurement))
  {
    //don't change the blank value of windDP.
  }
  else
  {
    dtostrf(measurement, 3, 0, windDP);
    charPadString(windDP, '0', ' ', 1);
  } 
}


/*Returns temperature measurement in deg. Celsius from Rev P wind Sensor.*/
float measureRevpTemp()
{
  // temperature routine and print raw and temp C
  int tempRawAD = analogRead(WIND_TEMP_PIN);  
  // Serial.print("RT ");    // print raw A/D for debug
  // Serial.print(tempRawAD);
  // Serial.print("\t");
  
  // convert to volts then use formula from datatsheet 
  // Vout = ( TempC * .0195 ) + .400
  // tempC = (Vout - V0c) / TC   see the MCP9701 datasheet for V0c and TC
  
  float tempC = ((((float)tempRawAD * 5.0) / 1024.0) - 0.400) / .0195; 
  return tempC;
}


void measureRevpTempString(char tempDP[])
{
  double measurement = measureRevpTemp();
  dtostrf(measurement, 6, 2, tempDP);
  charPadString(tempDP, '0', ' ', 1);
}
