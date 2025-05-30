/*
 * SysTick.c
 *
 *  Created on: Apr 28, 2025
 *      Author: zaxaw
 */

#include "inc/SysTick.h"





// SysTick system timer initialized with 1ms rollover
void SysTick_Init()
{
    SysTick->CTRL &= ~0x01;     // Disable timer
    SysTick->LOAD  =  4800;     // 100 us rollover
    SysTick->CTRL |=  0x07;     // Enable timer w/ interrupts, sourced on core clock (FCLK, 48MHz)
}

//
void SysTick_Handler()
{
    SysTick_us_elapsed += 100;

    if (SysTick_us_elapsed % 1000 == 0)
    {
        SysTick_ms_elapsed++;
    }
}
