
#ifndef INC_TIMER_A1_H_
#define INC_TIMER_A1_H_

#include "msp.h"
#include <stdio.h>
#include <stdint.h>

uint16_t period_us;
uint16_t pulse_width_us;

void Timer_A1_Init(void);
void TA1_0_IRQHandler(void);
void TA1_N_IRQHandler(void);
void Update_Timer_A1_Period(uint16_t period_us);
void Update_Timer_A1_Pulse_Width(uint16_t pulse_width_us);

#endif /* INC_TIMER_A1_H_ */
