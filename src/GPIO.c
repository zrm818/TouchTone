
#include "inc/GPIO.h"

// PUSHBUTTONS -----------------------------------------------------------------

// Initializes pushbuttons on P2.4 through P2.7
void P2_Init()
{
    P2->DIR  &= ~0xF0;  // Set pushbutton pins to input
    P2->SEL1 &= ~0xF0;  // Default function select
    P2->SEL0 &= ~0xF0;  // ^^^
    P2->IES  &= ~0xF0;  // P4.0, P4.2 flags set with low-to-high transition
    P2->IE   |=  0xF0;  // Interrupts enabled on P2.4 through P2.7

    NVIC->ISER[1] |= 0x00000010;  // Enable interrupts (#36 == 32 + 4 == bit 4)
}

// Pushbutton interrupt handler (*** TEST PHASE ***)
void PORT2_IRQHandler()
{
    uint16_t pb_status = P2->IV;
    switch (pb_status) {
        case 0x02: // P2.0 IFG
            printf("PB0 pressed!\n");
            break;
        case 0x04: // P2.1 IFG
            printf("PB1 pressed!\n");
            break;
        case 0x06: // P2.2 IFG
            printf("PB2 pressed!\n");
            break;
        case 0x08: // P2.3 IFG
            printf("PB3 pressed!\n");
            break;
        default: break;
    }
}

// ULTRASONIC SENSORS ----------------------------------------------------------

// Initializes ultrasonic sensors 1 and 2 on P4.0/P4.1 and P4.2/P4.3
void P4_Init()
{
    P4->DIR  |=  0x05;  // Set trigger pins (P4.0, P4.2) to output
    P4->DIR  &= ~0x0A;  // Set echo pins (P4.1, P4.3) to input
    P4->SEL1 &= ~0x0F;  // Default function select
    P4->SEL0 &= ~0x0F;  // ^^^
    P4->IES  |=  0x05;  // Set trigger IFGs on high-to-low transition
    P4->IES  &= ~0x0A;  // Set echo IFGs on low-to-high transition
    P4->IE   |=  0x0F;  // Interrupts enabled on P4.0 through P4.3

    NVIC->ISER[1] |= 0x00000040;  // Enable interrupts (#38 == 32 + 6 == bit 6)
}

// Ultrasonic trigger/echo pin interrupt handler
void PORT4_IRQHandler()
{
    uint16_t iv = P4->IV; // Find highest pending interrupt and clear its flag
    switch (iv) {
        case 0x02: // P4.0 IFG (US1 TRIG)
            US1_trig_end_us = TIMER_A0->R;
            US1_active = 1;
            break;
        case 0x04: // P4.1 IFG (US1 ECHO)
            if (US1_active) {
                US1_echo_start_us = TIMER_A0->R;
                US1_active = 0;
            }
            break;
        case 0x06: // P4.2 IFG (US2 TRIG)
            US2_trig_end_us = TIMER_A0->R;
            US2_active = 1;
            break;
        case 0x08: // P4.3 IFG (US2 ECHO)
            if (US2_active) {
                US2_echo_start_us = TIMER_A0->R;
                US2_active = 0;
            }
            break;
        default: break;
    }
}

// SPEAKERS --------------------------------------------------------------------

// Initializes speaker output on P4.5
void P4_5_Init()
{
    P4->DIR  |=  0x20;  // Set speaker pin (P4.5) to output
    P4->SEL1 &= ~0x20;  // Default function select
    P4->SEL0 &= ~0x20;  // ^^^
    P4->OUT  &= ~0x20;  // Clear output of speaker pin
}

// RG STATUS LEDS --------------------------------------------------------------

// Initializes RG LED pins on P10.0 through P10.3
void P10_Init()
{
    P10->SEL0 &= ~0x0F;
    P10->SEL1 &= ~0x0F;
    P10->DIR  |=  0x0F;
    P10->OUT  &= ~0x0F;
}

// Sets the color displayed by the Red-Green LED above US1
void Set_RG_LED1(uint8_t color)
{
    switch (color)
    {
    case RG_LED1_OFF:
        P10->OUT &= ~(RG_LED1_RED + RG_LED1_GREEN);
        break;
    case RG_LED1_GREEN:
        P10->OUT &= ~RG_LED1_RED;
        P10->OUT |= RG_LED1_GREEN;
        break;
    case RG_LED1_RED:
        P10->OUT &= ~RG_LED1_GREEN;
        P10->OUT |= RG_LED1_RED;
        break;
    default: break;
    }
}

// Sets the color displayed by the Red-Green LED above US2
void Set_RG_LED2(uint8_t color)
{
    switch (color)
    {
    case RG_LED2_OFF:
        P10->OUT &= ~(RG_LED2_RED + RG_LED2_GREEN);
        break;
    case RG_LED2_GREEN:
        P10->OUT &= ~RG_LED2_RED;
        P10->OUT |= RG_LED2_GREEN;
        break;
    case RG_LED2_RED:
        P10->OUT &= ~RG_LED2_GREEN;
        P10->OUT |= RG_LED2_RED;
        break;
    default: break;
    }
}
