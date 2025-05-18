# STM32 and Simulink-based HIL Simulation of a 2nd-order Model.

## About

The project consists on the developing of a Hardware-in-the-Loop test setup, in which was used two microcontrollers, one for run the model of a physic plant and the other to run the designed controller. The plant was modeled using parameters of a 2nd-order Butterworth low-pass filter, which also was implemented in this project for the purpose of comparision and because it is easy to obtain in practice. Furthermore, was used MATLAB and Simulink to plant modelling, controller design, and Hardware-in-the-Loop test. This project seeks to bring practices to facilitate the development and validation of real-time control systems, which can be reused, improved and expanded for other use cases.

| ![HIL-simulation-overview](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-simulation.png) |
| Project overview |

https://github.com/user-attachments/assets/47358cbd-f617-43dd-8a0a-f05c09b67609

| Project running |

## Features

- STM32F407ZGT6 MCU based board: Acting as a real-time plant simulator (Target Hardware).
- STM32401CDU6 MCU based board: Acting as a controller under test.
- 2nd-order Butterworth low-pass analog filter: Acting as the real plant (Actual Production Hardware, or just Actual Hardware in this project).
- MATLAB and Simulink: Modeling, design, simulation and real-time visualization of the control system through serial communication (HIL test).
- Simulink Embedded Coder: C code generation of plant and controller models.

## Control System Modeling

| ![control-system-model](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/control-system-model-evolution.png) |
| Project overview |

First, the control system was modeled in a simply way (a) and finally model blocks were created for each part (b) for the purpose of generating code for each component of the control system. Models was configured as fixed-step with the sampling time of 50 ms. Plant model was configured with Solver ode4 (Runge-Kutta). The SystemParameters.m file contains the physical parameters of the plant, that is, the values ​​of the components of the analog filter circuit. 

Simulink Embedded Coder was used to generate C code for each block of the model, using the Quick Start option. The settings were: ARM-compatible (Cortex - M) and Execution efficiency. In addition, the following settings were manually reverted to the following values:


1. Code Generation -> Identifiers
- Constant macros: \$R\$N\$M
- Global types: \$N\$R\$M_T
- Global variables: \$R\$N\$M
- Subsystem methods: \$R\$N\$M\$F

2. Math and Data Types
- Use division for fixed-point net slope computation: Off

After code generation, all real number definitions, previously assigned as double, were reassigned as float in their respective header files (.h).

## Hardware/Firmware and Signal Interfacing Aspects

### Controller
- Timer: 20 kHz for fixed sampling time of 50 ms.
- PWM: 1 kHz for input control signal.
- ADC: For feedback of the output voltage signal.

### Target Hardware
- Timer: 40 kHz (model step each 20 kHz)
- Input Capture: 1 kHz to acquire the PWM duty cycle value sent by the controller.
- DAC: To generate analog output value of the simulated plant.
- ADC: To acquire the output voltage value the of real plant (Actual Hardware).
- USART: To transmit the simulated and real output values to the HIL Simulation model running in Simulink.


## Pinout and Prototype

| ![target-hardware-pinout](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/target-hardware-pinout.png) |

| Target Hardware Pinout |

The pin PIN_PWR_ON_CONTROLLER of the Target Hardware is connected to the NRST pin of the Controller MCU.


| ![controller-pinout](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/controller-pinout.png) |

| Controller Pinout |


| ![circuit](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/circuit.png) |

| Prototype Circuit |


## Hardware-in-the-loop Test

This model is intended to execute the Desired Control System and receive via serial the output values ​​of the simulated plant and the real plant controlled by the designed controller. The results are presented in the Scope for validation. After powering on both microcontrollers, you need to run the HILSimulation.slx model to start the simulation. To restart the simulation, it is important to first restart the microcontrollers.

| ![HIL-simulation-model](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-simulation-model.png) |

| HIL Simulation Model |


Experiment were done for two scenarios:

### HIL Closed Loop and Actual Hardware Open Loop

This scenario consists of the original case of this project (see HIL Simulation Overview).

| ![HIL-ClosedLoop-Plant-OpenLoop](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-ClosedLoop-Plant-OpenLoop.png) |

| HIL Closed Loop and Plant Open Loop |

| ![HIL-ClosedLoop-Plant-OpenLoop(zoomed)](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-ClosedLoop-Plant-OpenLoop(zoomed).png) |

| HIL Closed Loop and Plant Open Loop (zoomed) |

It can be observed that the HIL simulation performed practically the same as the ideal scenario. On the other hand, it is possible to observe a difference in the output signal of the analog filter (Actual Hardware). In practice, an output gain was observed in the analog filter, probably due to the physical characteristics of the real electrical components. However, the dynamic system reponse was preserved.

### HIL Open Loop and Actual Hardware Closed Loop

In this scenario the Actual Hardware output was connected to the Controller's ADC_PLANT_OUTPUT pin. On the Target Hardware, the DAC_SIM_PLANT_OUTPUT was connected to the ADC_ACTUAL_HW_OUTPUT pin.

| ![HIL-OpenLoop-Plant-ClosedLoop](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-OpenLoop-Plant-ClosedLoop.png) |

| HIL Closed Loop and Plant Open Loop |

| ![HIL-OpenLoop-Plant-ClosedLoop(zoomed)](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-OpenLoop-Plant-ClosedLoop(zoomed).png) |

| HIL Open Loop and Plant Closed Loop (zoomed) |

In this scenario, a negative difference is noted between the ideal output and the output of the controlled system, confirming the existence of the Actual Hardware output gain. It can also be observed that the real-time simulated plant emulates the dynamics of the real plant with good accuracy.


## Notes

There is an undesirable effect during the test. At some point, an overshoot followed by a delay in the Plant Simulator output response in relation to the ideal response of the control system can be observed. There seems to be some kind of desynchronization between the Controller and the Plant Simulator. This problem, so far, has not destabilized the HIL test. Future work will focus on better exploring the causes and resolving this problem.

| ![HIL-ClosedLoop-Plant-OpenLoop-delayed](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-ClosedLoop-Plant-OpenLoop-delayed.png) |

| HIL Closed Loop and Plant Open Loop - delayed |

| ![HIL-ClosedLoop-Plant-OpenLoop-delayed(zoomed)](https://github.com/matheussmachado/stm32-and-simulink-based-hil-simulation-of-a-2nd-order-model/blob/main/HIL-ClosedLoop-Plant-OpenLoop-delayed(zoomed).png) |

| HIL Closed Loop and Plant Open Loop - delayed (zoomed) |