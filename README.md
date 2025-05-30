# TouchTone
ECE595R (Robotics & Embedded Systems) Final Project - Touchless Musical Instrument

This is the code for a digital theramin I made for an embedded systems class at CSUN in Spring 2025. The code won't run by itself, it needs to be placed in a project in TI Code Composer Studio and requires some dependencies provided by Texas Instruments. These dependencies are provided when selecting the board you are using from within Code Composer Studio and creating a CCS project.

The following files were NOT written by me:
- The msp.c file is a library for interfacing with the Texas Instruments MSP432P401R microcontroller board, and is provided by Texas Instruments.
- The CortexM.c and Clock.c files enable systemwide interrupts and provide clock-related functions. Both files were written by Jonathan Valvano, the author of the book "Embedded Systems: Introduction to Robotics".
- The EUSCI_A0_UART.c file directs print statements to the serial console, and was written by Aaron Nanas, my lab instructor.

All other files in the src and inc folders (and main.c) were written by me as a part of the final project in the class.

There is also a pptx and pdf of my final report materials for the class, which may be helpful to understand the project.
