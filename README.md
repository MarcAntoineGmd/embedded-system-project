# Autonomous Inspection Robot — INF1900 (École Polytechnique de Montréal)

Marc-Antoine Gaumond · Alexis Chapados · Alex Carpentier · Frédéric Labelle

A bare-metal C++ robot built for AVR that autonomously runs an inspection circuit, identifies objects and people across six rooms, and sends a live status report back to a PC — no operating system involved.

## Overview

1. **Loads a mission** — a custom bytecode program is sent to the robot over UART, defining which direction to travel, where to park, and which sounds to play.
2. **Follows the track** — a 5-sensor IR array combined with wall-detection sensors lets the robot stay on the line, recognize corners, and enter rooms from either direction (clockwise or counterclockwise).
3. **Performs inspections in six rooms:**
   - Hallways: identifies damaged sections of the floor by matching obstacle patterns
   - Storage areas: counts items using a forward-facing proximity sensor
   - Workrooms: detects people (represented by poles) through ADC threshold readings, sounding a distinct note for each one found
4. **Docks itself** in one of four designated parking spaces, relying on timed movement sequences and wall-following adjustments.
5. **Reports results live** — as each room is inspected, a corresponding data row is transmitted over UART right away, rather than waiting for the full run to finish.

## Engineering details

- **Hardware:** ATmega324PA microcontroller running at 8 MHz, coded entirely in bare-metal C++ (AVR-GCC, no RTOS)
- **Sensing:** 5-channel MakerLine module handles line-following, wall detection, corners, and obstacles; ADC readings handle proximity detection for poles
- **Bytecode system:** an assembler running on the PC compiles mission instructions (opcodes like `trd`, `trg`, `sgo`, `att`, etc.) into a compact format, which the robot pulls from I2C EEPROM and interprets at runtime
- **Non-volatile memory:** mission parameters and inspection data are stored on an external 24LCxxx EEPROM chip over I2C/TWI, so nothing is lost if power drops
- **Live UART output:** results stream out row-by-row as inspections complete, instead of batching everything until the end
- **Custom driver library:** a dedicated static library (`libequipe7987.a`) keeps hardware drivers (motor, LED, UART, EEPROM, ADC, buzzer) cleanly separated from the application-level logic

## Tech stack

| Layer | Technology |
|---|---|
| Language | C++17 (bare-metal, no stdlib) |
| MCU | ATmega324PA (AVR 8-bit) |
| Build system | AVR-GCC, GNU Make |
| Flashing | avrdude / USBasp |
| Communication | UART (9600 baud), I2C/TWI |
| Sensors | MakerLine IR array, ADC, digital IR |
