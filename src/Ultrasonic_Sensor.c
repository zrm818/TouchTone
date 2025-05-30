
#include "inc/Ultrasonic_Sensor.h"

// This function pulses the trigger pins of the ultrasonic sensors for 10us
// and resets all sensor timing measurements. The falling edge of the trigger
// pins triggers a GPIO interrupt which captures the end of the trigger signal
void Trigger_US_Sensors()
{
    // Reset all sensor timing measurements
    US1_trig_end_us   = 0;
    US1_echo_start_us = 0;
    US2_trig_end_us   = 0;
    US2_echo_start_us = 0;

    // Pulse both trigger signals (P4.0, P4.2)
    P4->OUT |= 0x05;
    Clock_Delay1us(10); // Minimum 10us from datasheet
    P4->OUT &= ~0x01;
    Clock_Delay1us(5);  // Ensure that falling edges occur at different times
    P4->OUT &= ~0x04;
}

// This function converts sensor timing measurements to distance measurements
// in accordance with the formula: Distance = V_sound * (t / 2)
void Calculate_US_Distances()
{
    // Calculate the distance measurements
    US1_distance_cm = SPEED_OF_SOUND *
            (float)(US1_echo_start_us - US1_trig_end_us) / 2 / 1000000 * 100;
    US2_distance_cm = SPEED_OF_SOUND *
            (float)(US2_echo_start_us - US2_trig_end_us) / 2 / 1000000 * 100;

    // Replace out-of-bounds values with sentinel value (-1) and set LEDs
    if ((US1_distance_cm > SPEAKER_UPPER_BOUND_CM) || (US1_distance_cm < 1))
    {
        US1_distance_cm = -1;
        Set_RG_LED1(RG_LED1_RED);
    }
    else { Set_RG_LED1(RG_LED1_GREEN); }

    if ((US2_distance_cm > SPEAKER_UPPER_BOUND_CM) || (US2_distance_cm < 1))
    {
        US2_distance_cm = -1;
        Set_RG_LED2(RG_LED2_RED);
    }
    else { Set_RG_LED2(RG_LED2_GREEN); }
}
