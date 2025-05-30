
#include "inc/TIMER_A0.h"

void Timer_A0_Init()
{
    TIMER_A0->CTL     &= ~0x0030;   // Stop Timer A0
    TIMER_A0->CTL     |=  0x02C0;   // SMCLK (f = 24MHz), prescale by 8
    TIMER_A0->EX0     |=  0x0002;   // Divide input by 3, f = 1MHz (T = 1us)
    TIMER_A0->CCTL[0] |=  0x0010;   // Enable interrupts on timer rollover
    TIMER_A0->CCTL[1] |=  0x0010;   // Enable interrupts on cutoff register

    TIMER_A0->CCR[0] = SAMPLE_PERIOD_MS * 1000 - 1; // Rollover period (in us)
    TIMER_A0->CCR[1] = CUTOFF_TIME_MS   * 1000 - 1; // ECHO timeout cutoff time

    NVIC->ISER[0] |= 0x00000100;    // Enable TA0 CCR0 interrupt (interrupt 8)
    NVIC->ISER[0] |= 0x00000200;    // Enable TA0 CCRn interrupt (interrupt 9)

    TIMER_A0->CTL |= 0x0014;        // Clear and enable Timer A0 in up mode
}

// Indicates timer rollover
void TA0_0_IRQHandler()
{
    TIMER_A0->CCTL[0] &= ~0x0001;   // Acknowledge interrupt (clear IFG bit)
    US_sensors_trig_ready = 1; // Set flag to trigger US sensors in main loop
}

// Indicates Ultrasonic ECHO timeout
void TA0_N_IRQHandler()
{
    // Determine the source of the interrupt
    if (TIMER_A0->CCTL[1] & 0x0001)
    {
        TIMER_A0->CCTL[1] &= ~0x0001; // Acknowledge interrupt (clear IFG bit)

        US_sensors_echo_ready = 1;  // Set flag to read US sensors in main loop

        // Ensure that the sensors are not awaiting response
        if (US1_active) { US1_active = 0; }
        if (US2_active) { US2_active = 0; }
    }
}
