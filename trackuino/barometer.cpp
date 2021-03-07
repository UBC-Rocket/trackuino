#include "barometer.h"
#include "aerostat_config.h"
#include "aerostat_utils.h"


void setupBarometer()
{
  pinMode(BAROMETER_PIN, INPUT);
}

double measurePressure()
{
  double reading = analogRead(BAROMETER_PIN);
  double barometerVoltage = reading/1024.0 * BAROMETER_V_REFERNECE;
  // AnalogRead returns value between 0 and 1024, which is a fraction of the V_SUPPLY

  double pressure = (barometerVoltage - BAROMETER_TRANS_FUN_MIN * BAROMETER_V_SUPPLY) * (BAROMETER_P_MAX - BAROMETER_P_MIN)/(0.8*BAROMETER_V_SUPPLY) + BAROMETER_P_MIN;
  //I put 0.8 here because the data sheet said to. Try to use TRANSFER_FUNCTION_MAX instead and see if it changes anything.

  return pressure;
}


void measurePressureString(char pressureDP[5])
{
  dtostrf(measurePressure(), 4, 2, pressureDP);
  charPadString(pressureDP, '0', ' ', 1);
}
