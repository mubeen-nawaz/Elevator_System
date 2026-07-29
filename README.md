# 8051 Elevator System Simulation

A simple 5-floor elevator controller built around the **AT89C51 (8051)** microcontroller, written in C using **Keil µVision** and simulated in **Proteus ISIS**.

## Overview

The system reads a floor-request input from Port 0 and drives a stepper motor (via Port 3) to simulate the elevator car moving up or down to the requested floor. The current floor number is reflected on Port 2 (e.g. driving 7-segment displays/LEDs in the Proteus schematic).

## How It Works

- `floor` tracks the elevator's current position (starts at floor 1).
- The `main()` loop polls **Port 0** for a floor request:
  | P0 value | Requested floor |
  |----------|-----------------|
  | 1        | 1               |
  | 2        | 2               |
  | 4        | 3               |
  | 8        | 4               |
  | 16       | 5               |
- `control()` compares the requested floor to the current floor and calls `up()` or `down()` with the number of floors to travel.
- `up()` / `down()` step a 4-phase sequence out on **Port 3** (`1 → 2 → 4 → 8` for up, reversed for down) to drive a stepper motor, pausing between steps via the `wait()` delay loop.
- After each floor is reached, **Port 2** is updated to show the new floor number.

## Hardware / Simulation

| Item | Details |
|---|---|
| MCU | AT89C51 |
| Input | Port 0 – floor request switches |
| Output | Port 3 – stepper motor driver (4-phase sequence) |
| Output | Port 2 – current floor display |
| Simulation | Proteus ISIS (`elevator.pdsprj`) |
| Firmware | Keil µVision 4/C51 project (`elevator.uvproj`) |

## Project Structure

```
├── elevator.c               # Main firmware source
├── STARTUP.A51              # 8051 startup/init assembly (Keil C51 default)
├── elevator.uvproj          # Keil µVision project file
├── elevator.uvopt           # Keil µVision project options
├── elevator.pdsprj          # Proteus ISIS simulation schematic
├── Objects/                 # Build output (.hex, .obj, link files)
├── Listings/                # Compiler/linker listing files
└── Project Backups/         # Proteus auto-save backups
```

## Getting Started

### Requirements
- [Keil µVision (µVision4/µVision5) with the C51 toolchain](https://www.keil.com/)
- [Proteus Design Suite (ISIS)](https://www.labcenter.com/)

### Build the Firmware
1. Open `elevator.uvproj` in Keil µVision.
2. Build the project (**F7**) to generate `Objects/elevator.hex`.

### Run the Simulation
1. Open `elevator.pdsprj` in Proteus ISIS.
2. Load `Objects/elevator.hex` onto the AT89C51 component in the schematic (if not already linked).
3. Run the simulation and toggle the Port 0 input switches to request a floor.

## Notes / Known Limitations

- `floor1` in `main()` is assigned but currently unused — a candidate for future work (e.g. displaying the requested vs. current floor).
- No debouncing or request-queuing logic is implemented; requests are polled continuously as level inputs rather than edge-triggered events.
- Motor step timing is a simple software delay loop (`wait()`), not timer-based.
