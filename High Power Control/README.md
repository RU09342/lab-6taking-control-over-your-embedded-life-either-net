# Lab 6: "High Power" Control

This sub-folder contains the code for high-power control systems.

## Dependencies

This code requires the MSP430G2553 header file. 
```c
#include <msp430g2553.h>
```

## Function

This code produces a PWM, 50% duty cycle square wave output on `P1.2`. The first peripheral function is set on `P1.2` which is tied to the `CCR1` output. `CCTL0` is configured with `OUTMOD_7` which is "reset/set". Lowest DCOx and MOD settings used.

```c
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
```

## Elaboration

Observing the output on `P1.2` on an oscilloscope, you will see something similar to this ![How a relay works.](https://cdn4.explainthatstuff.com/how-a-relay-works.gif).

Relay and MOSFET switching requires a modulated signal, which the G2553 is able to generate. These two types of high-power control are similar in function, but each has its own limitations and benefits.

### Relay Switching



### MOSFET Switching

