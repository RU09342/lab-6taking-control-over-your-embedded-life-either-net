/**
 * Description: This program is designed to be used with the MSP430F5529 to generate a triangle wave from a PWM-analog signal converter.
 * Authors: Damon Boorstein and Brendan Nugent
 * Date: 11/29/2017
 */

#include <msp430.h>

void initializeTimer();

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // Stop WDT

    P1DIR &= ~BIT2; 
    P1DIR |= BIT2;
    P1SEL |= BIT2;             //Select primary peripheral module function on P1.2 for timer PWM

    initializeTimer();

    __bis_SR_register(GIE);       // Enable interrupts

    int y = -1;

    while(1)
    {
        if (TA0CCR1 == 1000 || TA0CCR1 == 0)
            y = -y;
        TA0CCR1 += y;
    }

}

void initializeTimer(void)
{
    TA0CCR0 = 0x1000; // Set max value
    TA0CCTL1 = OUTMOD_7; // set output on reset
    TA0CCR1 = 0; // initialize compare register for 50% cycle
    TA0CTL = TASSEL_2 + MC_1; // Use the SMCLK and up mode
}
