#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P3DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
	P3OUT = 0x00;
	unsigned int count = 0;
	int x = -1;

	while (1)
	{
	    if (P3OUT == 0xFF || P3OUT == 0x00)
	        x = -x;
	    P3OUT += x;
	    //__delay_cycles(1000);
	}
}
