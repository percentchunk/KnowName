# Bill of Materials (BOM)

## ESP32 XY Plotter

This document contains the hardware components required to build the ESP32 XY Plotter.

## Components

| Component | Quantity | Purpose |
|---|---:|---|
| ESP32-S3 | 1 | Main microcontroller responsible for motion control and serial communication |
| NEMA 17 Stepper Motor | 2 | Provides X and Y axis movement |
| A4988 Stepper Driver | 2 | Controls current and movement of each stepper motor |
| 9V Battery | 2 | Power source for the prototype system |
| 300mm V-Slot Extrusion | 1 | Structural frame component for the motion system |
| V-Slot Carriage | 1 | Provides linear movement along the extrusion |
| Jumper Wires | Various | Electrical connections between components |

## Hardware Summary

The system uses an ESP32-S3 as the main controller, communicating with two A4988 stepper drivers to control a pair of NEMA 17 stepper motors. The motors are mounted onto a V-Slot extrusion system, creating the X/Y motion platform.

The electronics and mechanical components work together to create a compact two-axis drawing machine capable of streaming movement coordinates to a computer for digital visualization.

## Assembly Requirements

Additional items may be required depending on the final build configuration:

- Motor mounting hardware
- Power connectors
- Motor wiring
- Breadboard or custom PCB
- Mechanical fasteners
- Drawing tool/pen holder
