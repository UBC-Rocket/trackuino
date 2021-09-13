/*
* Much simpler implementation of a buzzer
*/
#include <Arduino.h>

#include "buzzer.h"
#include "config.h"

void aerostat_buzzer_beep()
{
    tone(BUZZER_PIN, BUZZER_FREQ, BUZZER_ON_TIME);
}
 
