/**
 * Main program for ECE595R Final Project
 * Spring 2025, Professor Shahnam Mirzaei
 * Digital Theramin / Air Drums
 *
 * WIRING:
 *
 *      Ultrasonic Sensors:
 *          - VDD to 5V/3.3V, GND to GND, GND2 to GND
 *          - TRIG1 to P4.0, ECHO1 to P4.1
 *          - TRIG2 to P4.2, ECHO2 to P4.3=
 *
 *      Speakers:
 *          - Currently mono audio (both speakers driven by the same signal)
 *          - P4.5 output to killswitch to gate of power NMOS
 *
 *      LEDs:
 *          - Common Anode RG LED 1:
 *              - Red+ to P10.2, Green+ to P10.3, GND to GND
 *          - Common Anode RG LED 2:
 *              - Red+ to P10.0, Green+ to P10.1, GND to GND
 */

// IMPORTED FILES --------------------------------------------------------------

#include <stdint.h>                 // uintN_t types
#include <stdio.h>                  // Printf
#include "msp.h"                    // MSP432P401R library
#include "inc/Clock.h"              // Clock_Delay1us(), Clock_Delay1ms(),
#include "inc/CortexM.h"            // Enable_Interrupts()
#include "inc/EUSCI_A0_UART.h"      // Directs printf to serial console

// HANDWRITTEN FILES -----------------------------------------------------------

#include "inc/Timer_A0.h"           // Ultrasonic sensor timing
#include "inc/Timer_A1.h"           // Speaker signal timing/PWM
#include "inc/SysTick.h"            // CURRENTLY UNUSED
#include "inc/GPIO.h"               // All GPIO pins (sensors, speakers, LEDs)
#include "inc/Ultrasonic_Sensor.h"  // Ultrasonic sensor functionality
#include "inc/Speaker.h"            // Speaker functionality

// MAIN FUNCTION ---------------------------------------------------------------

void main(void)
{
    Clock_Init48MHz();              // System clock
    EUSCI_A0_UART_Init_Printf();    // Serial console for printf statements
    Timer_A0_Init();                // Ultrasonic sensor timing
    Timer_A1_Init();                // Timer A1 speaker tone timing
    P2_Init();                      // Pushbuttons
    P10_Init();                     // RG LEDs
    P4_Init();                      // Ultrasonic sensor pins on P4.0 - P4.3
    P4_5_Init();                    // Speaker pin on P4.5

	EnableInterrupts();             // Enable ALL system interrupts

    Turn_Off_Speaker();


	while(1) {

	    if (US_sensors_trig_ready)
	    {
	        Trigger_US_Sensors();
	        US_sensors_trig_ready = 0;
	    }
	    if (US_sensors_echo_ready) {
	        Calculate_US_Distances();
	        US_sensors_echo_ready = 0;

	        // DEBUG PRINTS
	        //printf("T1: %6d, E1: %6d, T2: %6d, E2: %6d\n", US1_trig_end_us,
	        //        US1_echo_start_us, US2_trig_end_us, US2_echo_start_us);
	        printf("MAIN: US1 Distance: %5.1fcm, US2 Distance: %5.1fcm\n",
	               US1_distance_cm, US2_distance_cm);

	        Update_Speakers();
	    }
	}
}
