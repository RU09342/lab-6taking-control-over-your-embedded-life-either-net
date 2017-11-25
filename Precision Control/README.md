# Precision Control with MSP430
The programs included are compatible with the MSP430F5529 and are intended to, separately, do the following: convert a pulse-width modulated pin to an analog voltage, generate a triangle wave using an R2R ladder and generate a triangle wave using the low-pass filter used in the PWM-analog converter. 

## Dependencies
These programs are dependent only on having the MSP430F5529-specific header file, which is included in the main files. This file is the MSP430.h header file included at the beginning of each main file.

## PWM Part 2

### How it Works
The MSP430 microcontroller is used to generate an analog voltage from its PWM pin. The program uses the MCU's hardware PWM capability to adjust the duty cycle based on input via UART. The output (P1.2) is connected to a 3.6k resistor, as shown in the schematic below. The opposite end of the resistor is connected to the positive leg of a 4.7uF capacitor, to complete a simple low-pass filter.

![PWMtoAnalog](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-either-net/blob/master/Precision%20Control/circuit.JPG)

The RC circuit is designed to allow the carrier frequency of the PWM signal to pass and block the remaining frequencies, outputting a DC voltage. The carrier frequency is calculated to be approximately 1kHz:

	Period of the square wave = T = 1000 cycles/(frequency of SMCLK) = 1000 cycles * 10^-6 = 0.001
	1/T = carrier frequency = 1kHz
	
The UART module is configured for a standard 9600 baud rate on P3.3(TX) and P3.4(RX). Altering the duty cycle will adjust the analog voltage output. The analog voltage is equal to the duty cycle times the system voltage (3.3V). For example, a 50% duty cycle will result in a 1.65V analog voltage.

The oscilloscope screenshot below shows the analog voltage being adjusted over UART. The values entered include 0x64(100%), 0x32(50%) and 0x00(0%).

![AdjustingVoltage](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-either-net/blob/master/Precision%20Control/PWMtoAnalog/adjustingvoltage.png)

### Usage
To use this PWM-analog system, program the MSP430F5529 with the included .c file. Connect pins 3.3 and 3.4 to UART TX and RX respectively. Connect the PWM pin (P1.2) to the resistor leg opposite of the capacitor-resistor node. Open a UART terminal, such as RealTerm, and open the appropriate port. Send values in as hex to alter the duty cycle and thus analog voltage.

## R2R DAC
### How it Works
The MSP430 microcontroller is used to generate a triangle wave on the R/2R ladder, a traditional implementation of a digital-to-analog converter. To do so, all of port 3, P3.0-P3.7, is incremented until the value = 1111 1111(b) or 255d. The register is then decremented until the value = 0. This is continuously repeated. Each pin is connected to a node (a_n). These bits' contribution to the voltage are weighted through the voltage divider network, as the resistance for a less significant bit is greater than that of a more significant bit.

The output voltage is related to the port 3 value through the following equation: V_o = (V_s) * (value/2^N) = 3.3 * (value/2^8)

![R/2R Schematic](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-either-net/blob/master/Precision%20Control/R2R/R2Rschematic.png)


### Usage
To generate the triangle wave: Program the MSP430F5529 with the main file in R2R5529 and connect each pin to the nodes labeled(a_n) in the schematic above. P3.0 is connected to the node a_0. The most significant bit, P3.7, is connected to a_7. Attach a scope probe to ground and to V_out. The triangle wave should appear on the oscilloscope and vary from 0V to 3.29V as shown below.

## Loading Effects

Adding a varying load resistance, as expected, does not affect the frequency of the generated triangle wave. However, it does affect the peak-to-peak voltage of the signal at large resistances. The oscilloscope measurements are included below.

|Load Resistance| Pk-Pk Voltage |
| ------------- | ------------- |
| w/o 			| 2.33V  |
| 100		    | 2.29V  |
| 300			| 2.29V  |
| 1000			| 2.33V  |
| 10000			| 2.29V  |
| 220k			| 1.93V  |  



