# ESP32 XY Plotter

The ESP32 XY Plotter is a two-axis drawing machine built around an ESP32 microcontroller. It uses stepper motors and A4988 drivers to control precise X/Y movement while streaming coordinate data over serial to a computer.

The computer software receives the coordinate data, recreates the movement digitally, and displays the drawing in real time. The resulting drawing can be saved and converted into digital formats such as SVG, allowing the physical machine and digital workspace to stay synchronized.

## Overview

This project started as a simple two-axis stepper motor controller, but it was expanded into a complete digital drawing system.

The device uses an ESP32 to process user inputs and control two stepper motors. The firmware manages the motor movement, tracks the current X/Y position, and continuously sends coordinate data through USB serial.

A computer application receives the coordinate stream and converts the movement into a live digital drawing. Each point from the physical plotter is represented digitally, allowing the drawing process to be monitored, stored, and exported.

The goal of the project is to bridge physical motion control and digital design by creating a machine that can both draw and communicate its movement data.

## Features

* ESP32-based motion controller
* Two-axis X/Y stepper motor system
* A4988 stepper motor drivers
* Manual directional controls
* Real-time coordinate tracking
* USB serial communication with computer
* Live drawing visualization
* Digital drawing export
* SVG-compatible output
* CNC-style motion control architecture

## Project Views

| Hardware View       | Drawing Interface           | Motion System          |
| ------------------- | --------------------------- | ---------------------- |
| Physical XY plotter | Live computer visualization | Stepper motor assembly |

## How It Works

The directional buttons send movement commands to the ESP32.

The ESP32 processes the inputs and generates STEP and DIR signals for the A4988 motor drivers. These drivers control the X and Y stepper motors, allowing precise movement along two axes.

While the motors are moving, the ESP32 tracks the actual motor position and sends the current coordinates over USB serial.

Example output:

```text
(0,0)
(10,0)
(10,5)
(20,5)
```

The computer receives this coordinate stream and plots each point in order, recreating the physical movement as a digital drawing.

The visualization system allows the drawing to be viewed live and saved into a digital vector format such as SVG.

## Coordinate System

The plotter uses a top-left origin coordinate system:

```text
(0,0) ---------------- X+
  |
  |
  |
  Y+
```

* Top-left position = `(0,0)`
* Moving right increases X
* Moving left decreases X
* Moving down increases Y
* Moving up decreases Y

## Hardware

| Part            | Details                                |
| --------------- | -------------------------------------- |
| Microcontroller | ESP32                                  |
| Motor Drivers   | 2x A4988 Stepper Drivers               |
| Motors          | X/Y Stepper Motors                     |
| Inputs          | Four directional buttons               |
| Communication   | USB Serial                             |
| Power           | External motor supply + ESP32 USB      |
| Wiring          | Breadboard prototype → perfboard final |

## Pin Configuration

### Buttons

| Button | ESP32 Pin |
| ------ | --------- |
| Up     | GPIO 1    |
| Down   | GPIO 2    |
| Left   | GPIO 42   |
| Right  | GPIO 41   |

### X Axis Driver

| Signal | ESP32 Pin |
| ------ | --------- |
| STEP   | GPIO 4    |
| DIR    | GPIO 5    |

### Y Axis Driver

| Signal | ESP32 Pin |
| ------ | --------- |
| STEP   | GPIO 6    |
| DIR    | GPIO 7    |

### Driver Enable

| Signal | ESP32 Pin |
| ------ | --------- |
| ENABLE | GPIO 8    |

## Electronics

The ESP32 controls the stepper drivers using STEP and DIR signals.

The A4988 drivers handle the current requirements of the stepper motors while allowing the ESP32 to maintain precise control over movement.

The system separates logic power and motor power:

* ESP32 powered through USB
* Stepper motors powered through an external motor supply

This design allows the controller electronics to remain isolated from the higher-current motor system.

## Firmware

The firmware is designed to:

* Read directional button inputs
* Control X/Y stepper movement
* Track actual motor position
* Maintain a coordinate system
* Stream coordinates over serial
* Provide real-time position data to the computer

Example serial output:

```text
XY Plotter Ready
(0,0)
(5,0)
(10,0)
(10,5)
```

The firmware uses the motor driver's tracked position rather than manually counting button presses, ensuring that the reported coordinates match the commanded stepper movement.

## Computer Software

The computer-side software receives coordinate data from the ESP32 through serial communication.

The visualization system is responsible for:

* Reading incoming coordinates
* Rendering the drawing in real time
* Displaying the current position
* Storing drawing paths
* Converting movement paths into digital drawings

The computer view acts as a digital mirror of the physical plotter. As the motors move, the drawing appears on screen at the same time.

The digital output can be represented as vector paths, allowing compatibility with formats such as SVG.

## CAD

The mechanical design includes:

* Stepper motor mounting system
* X/Y movement mechanism
* Drawing surface
* Tool mounting system

CAD files are used to design and refine the physical structure of the plotter, ensuring proper motor alignment, mechanical stability, and component placement.

## About

The ESP32 XY Plotter is a custom-built motion control and digital visualization system that combines embedded programming, electronics, mechanical design, and computer software into one integrated project.

The project demonstrates how a microcontroller-based machine can translate physical movement into digital information. By combining stepper motor control with serial communication, the system is able to understand its own position and communicate that information to a computer.

Unlike a traditional drawing machine that only produces a physical output, this system creates a connection between the physical and digital worlds. Every movement made by the motors is converted into coordinate data, allowing the computer to reconstruct the drawing, display it live, and store it as a digital file.

The project was designed as a foundation for CNC-style systems, focusing on accurate motion control, real-time data communication, and the integration of hardware and software. It combines concepts from robotics, embedded systems, computer graphics, and digital fabrication into a single platform.

The final system acts as both a physical XY plotter and a digital drawing interface, demonstrating how low-cost hardware can be used to create a complete computer-controlled manufacturing workflow.
