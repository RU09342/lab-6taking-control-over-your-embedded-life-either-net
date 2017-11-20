#include <msp430g2553.h>

/**
 * Lab 6: High Power Systems
 *  by Damon Boorstein
 *
 * File Name: main.c
 * Description: This code produces a PWM, 50% duty cycle square wave output on P1.2.
 * The first peripheral function is set on P1.2 which is tied to the CCR1 output.
 * CCTL0` is configured with OUTMOD_7 which is "reset/set". Lowest DCOx and MOD settings used.
 */

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    DCOCTL  = 0;              // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;    // Set DCO
    DCOCTL  = CALDCO_1MHZ;

    // initialize LED
    P1SEL|=BIT2;    // Select peripheral mode for P1.2 and P1.3
    P1DIR|=BIT2;    // Set pins to output direction
    P1OUT&=~BIT2;   // Set the pins low

    // initialize Timer
    CCR0=511; // Timer A0 Period
    CCTL1|=OUTMOD_7; // Output = Reset/Set
    CCR1=254; // 50% duty cycle
    TACTL|=TASSEL_1+MC_1+TACLR; // SMCLK, Continuous mode

    __bis_SR_register(LPM3_bits+GIE); // LPM0 with interrupts enabled
}
