/**
 * Pulse width modulation using the internal connection between TIMERA output and P1.2
 * The program is designed for use with the MSP430F5529. It can be used with an RC circuit to generate an analog voltage from the PWM signal
 * Date: 11/29/2017
 * Authors: Damon Boorstein and Brendan Nugent
 */

#include <msp430.h>

unsigned int x = 0;

void initializeTimer();

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // Stop WDT

    P1DIR |= BIT2;
    P1SEL |= BIT2;             //Select primary peripheral module function on P1.2 --> Connect to P1.0 for test

    initializeTimer();

    // Configure UART
    P3SEL = BIT3+BIT4;                        // P3.4,5 = USCI_A0 TXD/RXD
    UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
    UCA0BR0 = 0x03;                           // 32kHz/9600=3.41 (see User's Guide)
    UCA0BR1 = 0x00;                           //
    UCA0MCTL = UCBRS_3+UCBRF_0;               // Modulation UCBRSx=3, UCBRFx=0
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

    __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled

    __enable_interrupt();

    while(1) {}
}

void initializeTimer(void)
{
    TA0CCR0 = 1000 - 1; // Set max value
    TA0CCTL1 = OUTMOD_7; // set output on reset
    TA0CCR1 = 0; // initialize compare register for 50% cycle
    TA0CTL = TASSEL_2 + MC_1; // Use the SMCLK and up mode
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    UCA0TXBUF = UCA0RXBUF;                  // TX -> RXed character
    x = UCA0RXBUF;
    TA0CCR1 = 10 * x;						// set CCR1 according to duty cycle selected
    break;
  case 4:break;                             // Vector 4 - TXIFG
  default: break;
  }
}
