# Lab 6: Open Loop Systems

This sub-folder contains the code for Lab 6: Open Loop Systems.

## Dependencies

This code requires two header files: one for the MSP430FR6989

```c
#include <msp430fr6989.h>
```

and one for the LCD Driver.

```c
#include "LCDDriver.h"
```

## Usage

This project was debugged and is intended to be debugged in Code Composer Studio. Create a new project with the FR6989 as the target configuration. Include the three files in the source code folder in the project and debug.

## Function

Given a desired temperature, this code sets a PWM duty cycle. It is intended to be used in a system with a linear regulator, a temperature sensor to monitor the regulator's temperature, and a fan to control this temperature. The duty-cycle-to-temperature relationship was determined through experimentation.

## Elaboration

We can control the temperature of a voltage regulator as it heats up using an open-loop system. By touching a temperature sensor to the voltage regulator (safely, on a breadboard), we can observe its temperature. Then, turning a fan at a specific speed, we can control this temperature. With this system, we can determine a relationship between the speed of the fan and the temperature of the regulator.

To achieve this, power a fan with 14V and PWM its speed using the microcontroller (several online examples of PWM code for MSP430 devices are available). Then, build the following circuit:

![Circuit]()



Our results can be seen in the following table.

**Temperature for Fan Speed**

| Duty Cycle (%) | Temperature (degC) |
|:--------------:|:------------------:|
| 10             | 77                 |
| 20             | 69                 |
| 30             | 63                 |
| 40             | 58                 |
| 50             | 54                 |
| 60             | 51                 |
| 70             | 47                 |
| 80             | 46                 |
| 90             | 44                 |
| 100            | 43                 |

We then generated a graph in Excel.

 ![Temperature vs. Duty Cycle](temp_vs_duty.png)

Temperature can then be represented in a piecewise function. In the code, when the duty cycle is less than or equal to 54, this function is used:

```c
if(temp >= 54) // first piecewise function
{
   duty = (int)(-1.754386*(temp-81.3));
}
```

...and when it is greater, this function:

```c
else
{
    duty = (int)(-5.263158*(temp-61.4));
}
```