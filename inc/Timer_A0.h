
#ifndef TIMER_A0_H_
#define TIMER_A0_H_

#include <stdint.h>
#include "msp.h"        // MSP432P401R library

#define SAMPLE_PERIOD_MS 25
#define CUTOFF_TIME_MS 10

extern volatile uint8_t US_sensors_trig_ready;
extern volatile uint8_t US_sensors_echo_ready;
extern volatile uint8_t US1_active;
extern volatile uint8_t US2_active;

void Timer_A0_Init(void);
void TA0_0_IRQHandler(void);
void TA0_N_IRQHandler(void);

#endif /* TIMER_A0_H_ */
