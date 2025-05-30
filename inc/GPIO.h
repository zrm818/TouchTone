
#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <stdio.h>
#include "msp.h"        // MSP432P401R library
#include "Clock.h"

#define RG_LED1_RED      0x02
#define RG_LED1_GREEN    0x01
#define RG_LED1_OFF     ~0x03
#define RG_LED2_RED      0x08
#define RG_LED2_GREEN    0x04
#define RG_LED2_OFF     ~0x0C

extern volatile uint8_t US1_active;
extern volatile uint8_t US2_active;
extern volatile uint32_t US1_echo_start_us; // Falling edge of US1 trigger time
extern volatile uint32_t US1_trig_end_us;   // Rising edge of US2 echo time
extern volatile uint32_t US2_trig_end_us;   // Falling edge of US2 trigger time
extern volatile uint32_t US2_echo_start_us; // Rising edge of US2 echo time

void P2_Init(void);
void P10_Init(void);
void P4_Init(void);
void P4_5_Init(void);
void Port4_IRQHandler(void);
void Set_RG_LED1(uint8_t color);
void Set_RG_LED2(uint8_t color);

#endif /* GPIO_H_ */
