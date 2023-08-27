# SINDiB Micromouse Project

Welcome to the repository for the SINDiB Micromouse project developed for RoboFest 2023 by the SINDiB team. In this project, we present our efforts to design and build a micromouse robot capable of navigating a maze autonomously. This README file provides an overview of the key components selected for the project, along with the rationale behind each choice, as well as details about the PCB design.

## Component Selection

### Microcontroller: STM32F405

We chose the STM32F405 microcontroller due to its impressive performance capabilities and generous memory capacity. Its powerful ARM Cortex-M4 core and ample Flash and RAM resources enable us to implement complex algorithms for maze-solving and motion control efficiently.

### Programming and Debugging: ST-Link V2

The ST-Link V2 serves as an essential tool for programming and debugging the STM32F405 microcontroller. Its reliable performance and compatibility with the STM32 ecosystem make it an ideal choice for development and testing.

### Voltage Regulators: TPS76850, AMS1117, TPS73633

- TPS76850: We've opted for the TPS76850 as a low dropout voltage 5V linear regulator to provide a stable power supply for the main components, ensuring reliable operation.
- AMS1117: The AMS1117 3.3V linear regulator is selected to power the IR Receiver, providing a clean and regulated voltage source for accurate sensor readings.
- TPS73633: This LDO linear regulator is used to power the microcontroller, ensuring a stable and noise-free power source for optimal performance.

### Infrared Components: SFH4545 (IR Emitter) and TEFT4300 (IR Receiver)

- SFH4545: We've chosen the SFH4545 as the IR emitter due to its efficient and focused infrared emission, which enhances the accuracy of distance measurement and obstacle detection.
- TEFT4300: The TEFT4300 IR Receiver is selected for its sensitivity and reliability in detecting the emitted infrared signals, enabling precise distance measurements.

### Gyroscope: L3GD20HTR

The L3GD20HTR gyroscope is utilized to provide accurate angular rate measurements, aiding in orientation and motion control algorithms. Its high sensitivity and reliability contribute to the robot's effective navigation through the maze.

### Motor: N20-500RPM with Gear Ratio 30:1

The N20-500RPM motor, paired with a gear ratio of 30:1, strikes a balance between speed and torque. This combination provides the necessary power to propel the robot through the maze while maintaining control and maneuverability.

### Motor Drivers: TC4427, ZXMHC3F38148

- TC4427: We've selected the TC4427 motor driver for its fast switching capabilities, ensuring precise control over the motor's speed and direction.
- ZXMHC3F38148: This motor driver complements the TC4427, offering additional motor control options and enhancing overall performance.

### User Interface: OLED Display, Buzzer, HC-06 Bluetooth Module

- OLED Display: The OLED display serves as an informative interface, displaying relevant data and status information during development and testing phases.
- Buzzer: We've integrated a buzzer to provide auditory feedback, aiding in debugging and providing alerts for specific events.
- HC-06 Bluetooth Module: The HC-06 module facilitates wireless communication with the micromouse, enabling remote debugging and configuration adjustments.

## PCB Design

Our PCB design features dimensions of 98mm by 74mm. This size constraint was chosen with the intention of accommodating potential future expansion, such as diagonal runs or additional components, while still fitting within the constraints of the micromouse challenge.

For more information, feel free to explore our repository's documentation and source code. We are excited to present our progress and look forward to showcasing our micromouse at RoboFest 2023!




1. [STM32-ST Link V2 Interfacing](https://www.robotics-university.com/2016/05/mini-st-linkv2-programming-tool-for-stm8-and-stm32.html)
2. [HC-06 Pinout](https://www.etechnophiles.com/hc06-pinout-specifications-datasheet/)