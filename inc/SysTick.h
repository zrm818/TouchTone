/*
 * SysTick.h
 *
 *  Created on: Apr 28, 2025
 *      Author: Zach Martin
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>
#include "msp.h"        // MSP432P401R library


volatile uint64_t SysTick_us_elapsed;   // Max. value: 584,555 years
volatile uint32_t SysTick_ms_elapsed;   // Max. value: 49.7 days

void SysTick_Init(void);

void SysTick_Handler(void);


#endif /* SYSTICK_H_ */
