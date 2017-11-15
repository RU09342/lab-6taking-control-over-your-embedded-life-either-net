#include <msp430g2553.h>

/**
 * Lab 6: High Power Systems
 *  by Damon Boorstein
 *
 * File Name: main.c
 * Description: A pin is switched at a particular rate. Used to switch a relay.
 */

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    DCOCTL  = 0;              // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;    // Set DCO
    DCOCTL  = CALDCO_1MHZ;

    // initialize LED
    P1SEL|=BIT2+BIT3; // Select I/O direction for P1.0
    P1DIR|=BIT2+BIT3; // Set P1.0 to output direction
    P1OUT&=~(BIT2+BIT3); // Turn the LEDs off

    // initialize Timer
    CCR0=511; // Timer A0 Period
    CCTL1|=OUTMOD_7; // Output = Reset/Set
    TACTL|=TASSEL_1+MC_1+TACLR; // SMCLK, Continuous mode

    __bis_SR_register(LPM3_bits+GIE); // LPM0 with interrupts enabled
}
