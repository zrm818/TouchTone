
#ifndef SPEAKER_H_
#define SPEAKER_H_

#include <stdint.h>
#include "msp.h"            // MSP432P401R library
#include "inc/Clock.h"      // Clock_Delay1ms()
#include "inc/Timer_A1.h"   // Update_Timer_A1_Period()
#include "inc/Ultrasonic_Sensor.h"

uint8_t speaker_is_on;

uint16_t Map_Distance_To_Tone(float distance);
void Update_Speakers(void);
void Play_Tone(uint16_t note_period_us);
void Turn_Off_Speaker(void);

#endif
