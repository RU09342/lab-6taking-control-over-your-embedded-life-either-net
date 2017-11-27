# Lab 6: Taking Control Over your Embedded Life

This repo contains the source code for Lab 6 by the Either Net team. It is organized into the following sub-folders:

* High Power Control
* Precision Control
* Open Loop Systems

## High Power Control

Features source code for driving a high-power load using the MSP430G2553 and either relay or MOSFET switching.

## Precision Control

Designing an R2R-ladder DAC for precision-control. PWM is also reviewed.

## Open Loop Systems

This section delves into open-loop control for systems. A system consisting of a fan and a temperature sensor is designed to control the temperature of a linear regulator as it heats up during normal operation. By PWM'ing the fan and observing the temperature sensed over UART, a temperature vs. duty cycle curve is created. A program is then written to set the fan speed given a desired temperature.