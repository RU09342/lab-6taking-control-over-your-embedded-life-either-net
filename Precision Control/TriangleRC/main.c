/**
 * Brendan Nugent
 */

#include <msp430.h>

int x = 0;
unsigned int buttonPressed = 0;
unsigned int count = 0;

void initializeTimer();

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // Stop WDT

    P1DIR &= ~BIT2;
    P1DIR |= BIT2;
    P1SEL |= BIT2;             //Select primary peripheral module function on P1.2 --> Connect to P1.0 for test

    initializeTimer();

    __bis_SR_register(GIE);       // Enter LPM3, interrupts enabled

    int y = -1;

    while(1)
    {
        if (TA0CCR1 == 1000 || TA0CCR1 == 0)
            y = -y;
        TA0CCR1 += y;
        __delay_cycles(1000);
    }

}

void initializeTimer(void)
{
    TA0CCR0 = 0x1000; // Set max value
    TA0CCTL1 = OUTMOD_7; // set output on reset
    TA0CCR1 = 0; // initialize compare register for 50% cycle
    TA0CTL = TASSEL_2 + MC_1; // Use the SMCLK and up mode
}
