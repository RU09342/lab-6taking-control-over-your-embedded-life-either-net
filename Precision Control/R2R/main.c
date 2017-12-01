#include <msp430.h> 


/**
 * main.c
 * Description: This program is designed for use with the MSP430F5529 and an R/2R ladder. The 
 * microcontroller's port 3 is incremented to its maximum value(255) and decremented to zero to produce a triangle wave)
 * Authors: Damon Boorstein and Brendan Nugent
 */
int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P3DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7; // set port 3 to output
	P3OUT = 0x00;
	int x = -1;

	while (1)
	{
	    if (P3OUT == 0xFF || P3OUT == 0x00) // change direction up->down or down->up
	        x = -x;
	    P3OUT += x; // increment/decrement port 3
	}
}
