# ESP32 XY Plotter

The ESP32 XY Plotter is a two-axis drawing machine built around an ESP32 microcontroller. It uses stepper motors and A4988 drivers to achieve precise X/Y movement while streaming live coordinate data to a computer.

The computer software receives the coordinate data, recreates the movement digitally, and displays the drawing in real time. The resulting drawing can be saved and converted into digital formats such as SVG, allowing the physical machine and digital workspace to stay synchronized.

## Overview

This project started as a simple two-axis stepper motor controller, but it was expanded into a complete digital drawing system.

The device uses an ESP32 to process user inputs and control two stepper motors. The firmware manages motor movement, tracks the current X/Y position, and continuously sends coordinate data through USB serial.

A computer application receives the coordinate stream and converts the movement into a live digital drawing. Each point from the physical plotter is represented digitally, allowing the drawing process to be monitored, stored, and exported.

The goal of this project is to bridge physical motion control and digital design by creating a machine that can both draw and communicate its movement data.

## Features

- ESP32-based motion controller
- Two-axis X/Y stepper motor system
- Dual A4988 stepper motor drivers
- Manual directional controls
- Real-time coordinate tracking
- USB serial communication with computer
- Live drawing visualization
- Vector drawing export (SVG)
- CNC-style motion control architecture

## Project Views

| Hardware View | Drawing Interface | Motion System |
|---|---|---|
| <img src="https://github.com/user-attachments/assets/c67b0878-b89c-4e91-b804-1cb8e85571b2" width="300"/> | <img src="https://github.com/user-attachments/assets/726d7f56-df82-41b1-82ef-733352fb688d" width="300"/> | <img src="https://github.com/user-attachments/assets/98c9bf7f-b3be-485a-a1a7-c76cff52e2d1" width="300"/> |
| Physical XY plotter | Live computer visualization | Stepper motor assembly |

## How It Works

The directional buttons send movement commands to the ESP32.

The ESP32 processes the inputs and generates STEP and DIR signals for the A4988 motor drivers. These drivers control the X and Y stepper motors, allowing precise movement along two axes.

While the motors are moving, the ESP32 tracks the current motor position and sends the coordinates over USB serial.

Example output:

```text
(0,0)
(10,0)
(10,5)
(20,5)
