/* trackuino copyright (C) 2010  EA5HAV Javi
 * Modifications by Peter Goubarev (VE7BVU) and Anqi Xu () for UBC Rocket, Aerostat subteam; 2021
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

// IMPORTANT!

// CHANGES THAT HAVE BEEN MADE TO MAKE TRACKUINO COMPATIBLE WITH A MEGA (and must be undone to go back): 
// - We no longer use sleep mode (for other reasons); on a mega, we must remove BOD disabling during sleep (uncomment the disable_bod_and_sleep() function)
// - We use HardwareSerial with the Adafruit Ultimate GPS (and pins 19/18 on Mega)
// - AUDIO_PIN is now 9 instead of 3 (corresponding to Timer2)

 

// Mpide 22 fails to compile Arduino code because it stupidly defines ARDUINO 
// as an empty macro (hence the +0 hack). UNO32 builds are fine. Just use the
// real Arduino IDE for Arduino builds. Optionally complain to the Mpide
// authors to fix the broken macro.
#if (ARDUINO + 0) == 0
#error "Oops! We need the real Arduino IDE (version 22 or 23) for Arduino builds."
#error "See trackuino.pde for details on this"

// Refuse to compile on arduino version 21 or lower. 22 includes an 
// optimization of the USART code that is critical for real-time operation
// of the AVR code.
#elif (ARDUINO + 0) < 22
#error "Oops! We need Arduino 22 or 23"
#error "See trackuino.pde for details on this"

#endif


// Trackuino custom libs
#include "config.h"
#include "afsk_avr.h"
#include "afsk_pic32.h"
#include "aprs.h"
#include "gps.h"
#include "pin.h"
#include "power.h"
#include "adaUlGps.h"

// Arduino/AVR libs
#if (ARDUINO + 1) >= 100
#  include <Arduino.h>
#else
#  include <WProgram.h>
#endif

// Module constants
static const uint32_t VALID_POS_TIMEOUT = 2000;  // ms

// Module variables
static int32_t next_aprs = 0;


void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pin_write(LED_PIN, LOW);

  Serial.begin(115200);
  delay(2000);
#ifdef DEBUG_RESET
  Serial.println("RESET");
#endif

  //buzzer_setup();
  afsk_setup();
  //gps_setup();
  //sensors_setup();
  setupAdaUlGps();
  

  // Do not start until we get a valid time reference
  // for slotted transmissions.
//  if (APRS_SLOT >= 0) {
//    do {
//      while (! Serial.available())
//        power_save();
//    } while (! gps_decode(Serial.read()));
//    
//    next_aprs = millis() + 1000 *
//      (APRS_PERIOD - (gps_seconds + APRS_PERIOD - APRS_SLOT) % APRS_PERIOD);
//  }
//  else {
//    next_aprs = millis();
//  }  

  next_aprs = millis();
  
  // TODO: beep while we get a fix, maybe indicating the number of
  // visible satellites by a series of short beeps?
  Serial.println(F("S"));
}


void loop()
{
<<<<<<< Updated upstream
  // Receive GPS data 
  char gpsString[30];
  int altMeasurement;
  adaUlRecievePosition(0, gpsString, 29, &altMeasurement); //&timer

  
  // Time for another APRS frame
  if ((int32_t) (millis() - next_aprs) >= 0) {
    //get_pos();
    aprs_send();
    next_aprs += APRS_PERIOD * 1000L;
    while (afsk_flush()) {
<<<<<<< HEAD
      /*
      WARNING: IF ENABLING POWER_SAVE, MAKE SURE TO UNCOMMENT BROWN-OUT DETECTION IN power_avr.cpp, i.e. uncomment disable_bod_and_sleep()
      */
=======
   char gpsString[50];
   int altMeasurement;
   adaUlRecievePosition(&measure_timer, gpsString, 49, &altMeasurement);

  // Time for another measurement
  if ((millis() - measure_timer) >= (APRS_PERIOD/MEASUREMENTS_PER_PERIOD))
  {
    //add another wind speed measurement to velocityValues, and altitude measurement to velocityValues
    velocityValues[measurementIndex] = (int)measureRevpWind();
    altitudeValues[measurementIndex] = altMeasurement;
   
    measurementIndex++; 

    measure_timer = millis();
    Serial.println("Measured");
  }

  
  // Time for another APRS frame
  if ((millis() - aprs_timer) >= APRS_PERIOD) {
    //Serial.println(millis() - aprs_timer);
    aprs_send(gpsString, altitudeValues, velocityValues);
    measurementIndex = 0;


    aprs_timer = millis();
    while (afsk_flush()) {
>>>>>>> Stashed changes
=======
>>>>>>> parent of 31f9a20 (Transition to Mega)
      //power_save();
    }

#ifdef DEBUG_MODEM
    // Show modem ISR stats from the previous transmission
    afsk_debug();
#endif

  } 

  //power_save(); // Incoming GPS data or interrupts will wake us up
}
