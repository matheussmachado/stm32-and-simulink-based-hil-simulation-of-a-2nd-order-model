# STM32 and Simulink-based HIL Simulation of a 2nd-order Model.

## About

TThis project consists of developing a Hardware-in-the-Loop (HIL) test setup using two microcontrollers: one to run the physical plant model and another to run the designed controller. The plant is modeled based on the parameters of a 2nd-order Butterworth low-pass filter, which was also implemented as a physical circuit for comparison purposes due to its simplicity and availability in practice.

MATLAB and Simulink were used for plant modeling, controller design, and the HIL test itself. The goal of this project is to provide a practical setup for developing and validating real-time control systems that can be reused, improved, and expanded for other applications.

*Project overview*

![HIL-simulation-overview](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-simulation.png)

*Project running*

https://github.com/user-attachments/assets/47358cbd-f617-43dd-8a0a-f05c09b67609


## Features

- **STM32F407ZGT6 MCU based board**: Acting as a real-time plant simulator (Target Hardware).
- **STM32401CDU6 MCU based board**: Acting as a controller under test.
- **2nd-order Butterworth low-pass analog filter**: Serves as the actual plant (referred to as “Actual Hardware” in this project).
- **MATLAB and Simulink**: Used for modeling, design, simulation, and real-time visualization via serial communication during the HIL test.
- **Simulink Embedded Coder**: Used to generate C code for both the plant and controller models.

## Control System Modeling

*Control System Model*

![control-system-model](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/control-system-model-evolution.png)

Initially, the control system was modeled in a simple way **(a)**, and later modularized into blocks **(b)** to generate code for each component. The models were configured with a fixed-step solver and a sampling time of 50 ms. The plant model used the ode4 (Runge-Kutta) solver. The file SystemParameters.m defines the physical parameters of the plant, i.e., the values of the analog filter circuit components. 

Simulink Embedded Coder was used with the Quick Start option to generate C code. The configuration selected was ARM-compatible (Cortex-M) and optimized for Execution Efficiency. The following settings were manually reverted to the values below:

1. Code Generation -> Identifiers
- Constant macros: \$R\$N\$M
- Global types: \$N\$R\$M_T
- Global variables: \$R\$N\$M
- Subsystem methods: \$R\$N\$M\$F

2. Math and Data Types
- Use division for fixed-point net slope computation: Off

After code generation, all real numbers (initially defined as double) were manually changed to float in their respective .h files.

## Hardware/Firmware and Signal Interfacing Aspects

### Controller
- Timer: 220 kHz (for 50 ms fixed sampling time).
- PWM: 1 kHz (used for control input signal).
- ADC: For feedback from the output voltage signal.

### Target Hardware
- Timer: 40 kHz (model step every 20 kHz).
- Input Capture: 1 kHz (to acquire the PWM duty cycle from the controller).
- DAC: Outputs the analog signal from the simulated plant.
- ADC: Reads the output voltage from the real plant (Actual Hardware).
- USART: Sends the simulated and real plant output values to the HIL simulation model in Simulink.


## Pinout and Prototype

*Target Hardware Pinout*

![target-hardware-pinout](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/target-hardware-pinout.png)

The PIN_PWR_ON_CONTROLLER of the Target Hardware is connected to the NRST pin of the Controller MCU.

*Controller Pinout*

![controller-pinout](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/controller-pinout.png)

*Prototype Circuit*

![circuit](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/circuit.png)

## Hardware-in-the-loop Test

This model runs the desired control system and receives the simulated and real plant output values via serial communication. Results are visualized in the Scope for validation. After powering on both microcontrollers, the HILSimulation.slx model should be run to start the simulation. To restart, both microcontrollers must be reset first.

*HIL Simulation Model*

![HIL-simulation-model](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-simulation-model.png)

Two scenarios were tested:

### HIL Closed Loop and Actual Hardware Open Loop

This scenario corresponds to the original setup (see HIL Simulation Overview).

*HIL Closed Loop and Plant Open Loop*

![HIL-ClosedLoop-Plant-OpenLoop](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-ClosedLoop-Plant-OpenLoop.png)


*HIL Closed Loop and Plant Open Loop (zoomed)*

![HIL-ClosedLoop-Plant-OpenLoop(zoomed)](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-ClosedLoop-Plant-OpenLoop(zoomed).png)

The HIL simulation closely matches the ideal case. However, a gain was observed in the analog filter (Actual Hardware), likely due to real-world component characteristics. Despite this, the system's dynamic response remained consistent.

### HIL Open Loop and Actual Hardware Closed Loop

In this scenario, the Actual Hardware output is connected to the ADC_PLANT_OUTPUT pin of the controller. The DAC output from the simulated plant is fed into the ADC_ACTUAL_HW_OUTPUT pin of the Target Hardware.

*HIL Closed Loop and Plant Open Loop*

![HIL-OpenLoop-Plant-ClosedLoop](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-OpenLoop-Plant-ClosedLoop.png)

*HIL Open Loop and Plant Closed Loop (zoomed)*

![HIL-OpenLoop-Plant-ClosedLoop(zoomed)](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-OpenLoop-Plant-ClosedLoop(zoomed).png)

A negative offset was observed between the ideal and actual outputs, again confirming the gain in the analog filter. Nonetheless, the simulated plant closely matched the real plant’s dynamic behavior.


## Notes

An undesirable effect was noted during testing: at times, the output of the simulated plant shows an overshoot followed by a delay compared to the ideal response. This suggests a possible desynchronization between the Controller and the Plant Simulator. Although it hasn't destabilized the test, future work will aim to diagnose and correct this issue.

*HIL Closed Loop and Plant Open Loop - overshoot and delay*

![HIL-ClosedLoop-Plant-OpenLoop-delayed](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-ClosedLoop-Plant-OpenLoop-delayed.png)


*HIL Closed Loop and Plant Open Loop - delay (zoomed)*

![HIL-ClosedLoop-Plant-OpenLoop-delayed(zoomed)](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-ClosedLoop-Plant-OpenLoop-delayed(zoomed).png)
