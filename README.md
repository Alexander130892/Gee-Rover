# Gee-Rover

A 3D-printed, programmable "Mars rover" for young kids, inspired by the Bee-Bot
educational robot. Children enter a sequence of moves on the arrow buttons on the
rover's back, press **GO**, and the rover drives the program square by square
across a printed planet mat.

> **Status:** in development. Target: first unit finished by 25 December 2026.

![Gee-Rover](docs/images/gee-rover-final.jpg)
<!-- TODO: add final build photo (rover on the mat only) -->

## Features

| Mode | What it does | Status |
|---|---|---|
| **Mission** | Bee-Bot style programming: enter ↑ ↓ ← →, press GO, the rover executes. Up to 20 steps. | MVP |
| **Pilot** | Live driving with a Bluetooth gamepad (Bluepad32) | Stretch |
| **Defend** | IR "laser" turret and printed alien targets that react to hits | Follow-up |

- 15 cm grid moves and 90° pivot turns, open-loop with stepper motors
- Beeps and RGB "eyes" for feedback
- USB-rechargeable 18650 Li-ion cell with layered protection
- Firmware in C on ESP-IDF, with a host-testable state machine

## Repository map

| Path | Contents |
|---|---|
| [`docs/build-guide.md`](docs/build-guide.md) | Step-by-step build: print → wire → flash → calibrate |
| [`docs/bom.md`](docs/bom.md) | Bill of materials with sources and prices |
| [`docs/power.md`](docs/power.md) | Battery, charging, power budget and safety |
| [`docs/pinout.md`](docs/pinout.md) | ESP32 pin map and constraints |
| [`docs/sequencer.md`](docs/sequencer.md) | Button behaviour and firmware state machine |
| [`docs/decisions/`](docs/decisions/) | Architecture Decision Records (why things are the way they are) |
| [`firmware/`](firmware/) | ESP-IDF project |
| [`hardware/`](hardware/) | Fusion 360 source, STEP, STL files and planet mat artwork |

## Build your own

Start with the [build guide](docs/build-guide.md). You will need a 3D printer, a
soldering iron, and an ESP-IDF toolchain. The parts cost about €60 (see the
[BoM](docs/bom.md)).

## Licenses

- Firmware and code: [MIT](LICENSE)
- Hardware designs, STL files, mat artwork and documentation:
  [CC BY-SA 4.0](LICENSE-HARDWARE.md)

## Acknowledgements

- The Bee-Bot floor robot, for the interaction model
- [Bluepad32](https://github.com/ricardoquesada/bluepad32), for gamepad support
