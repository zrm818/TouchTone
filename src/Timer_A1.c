
#include "inc/Timer_A1.h"

void Timer_A1_Init()
{
    TIMER_A1->CTL     &= ~0x0030; // Stop Timer A1
    TIMER_A1->CTL     |=  0x02C0; // Source to SMCLK (f = 24MHz), prescale by 8
    TIMER_A1->EX0     |=  0x0002; // Divide input by 3 again, f = 1MHz (T=1us)
    TIMER_A1->CCTL[0] |=  0x0010; // Enable interrupts on timer rollover
    TIMER_A1->CCTL[1] |=  0x0010; // Enable interrupts on cutoff register
    TIMER_A1->CCR[0]  = 3822 - 1; // Initialize to C4 note (261.63Hz or so)
    TIMER_A1->CCR[1]  = 1911 - 1; // 50% Duty Cycle

    NVIC->ISER[0] |= 0x00000400;  // Enable TA1 CCR0 interrupt (interrupt 10)
    NVIC->ISER[0] |= 0x00000800;  // Enable TA1 CCRn interrupt (interrupt 11)

    TIMER_A1->CTL |= 0x0014;      // Clear and enable Timer A1 in up mode
}

// Toggles the speaker pin on timer rollover (CCR0 value)
void TA1_0_IRQHandler()
{
    TIMER_A1->CCTL[0] &= ~0x0001;   // Acknowledge interrupt and clear IFG flag
    P4->OUT ^= 0x20;                // Toggle P4.5
}

// Toggles the speaker pin on CCR1 value
void TA1_N_IRQHandler()
{
    if (TIMER_A1->CCTL[1] & 0x0001)
    {
        TIMER_A1->CCTL[1] &= ~0x0001;   // Acknowledge interrupt and clear IFG
        P4->OUT ^= 0x20;                // Toggle P4.5
    }
}

// Shuts down Timer_A1, modifies the period using the period_us argument, sets
// pulse width to half the new period, and restarts Timer_A1
void Update_Timer_A1_Period(uint16_t period_us)
{
    TIMER_A1->CTL &= ~0x0030;               // Shut down Timer A1
    TIMER_A1->CCR[0] = period_us - 1;       // Set new period
    TIMER_A1->CCR[1] = (period_us / 2) - 1; // Set 50% duty cycle
    TIMER_A1->CTL |= 0x0014;                // Clear and restart timer
}

// Shuts down Timer_A1, modifies the pulse width using the pulse_width_us
// argument, and restarts Timer_A1
void Update_Timer_A1_Pulse_Width(uint16_t pulse_width_us)
{
    TIMER_A1->CTL &= ~0x0030;               // Shut down Timer A1
    TIMER_A1->CCR[1] = pulse_width_us - 1;  // Set new pulse width
    TIMER_A1->CTL |= 0x0014;                // Clear and restart timer
}
