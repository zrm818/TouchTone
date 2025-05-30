
#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include <stdint.h>
#include "msp.h"
#include "inc/Clock.h"
#include "inc/GPIO.h"
#include "inc/EUSCI_A0_UART.h"

#define SPEED_OF_SOUND 344
#define SPEAKER_UPPER_BOUND_CM 100
#define SPEAKER_LOWER_BOUND_CM 10

volatile uint8_t US_sensors_trig_ready; // "Can pulse triggers" flag
volatile uint8_t US_sensors_echo_ready; // "Can calculate distance" flag

volatile uint8_t  US1_active;           // "Is waiting for response" flag
volatile uint32_t US1_trig_end_us;      // Falling edge of US1 trigger time
volatile uint32_t US1_echo_start_us;    // Rising edge of US1 echo time
volatile float    US1_distance_cm;      // Calculated US1 distance reading

volatile uint8_t  US2_active;           // "Is waiting for response" flag
volatile uint32_t US2_trig_end_us;      // Falling edge of US2 trigger time
volatile uint32_t US2_echo_start_us;    // Rising edge of US2 echo time
volatile float    US2_distance_cm;      // Calculated US2 distance reading

void Trigger_US_Sensors(void);
void Calculate_US_Distances(void);

#endif /* ULTRASONIC_SENSOR_H_ */
