# ADR-0005: ESP-IDF with Bluepad32 as a component

- **Status:** Accepted
- **Date:** 2026-10-25

## Context

The motion code needs precise hardware timers and direct GPIO register writes. Pilot
mode (stretch goal) needs Bluepad32, which ships as an ESP-IDF or Arduino project
template and runs the Bluetooth stack on core 0.

## Options

| Option | Pros | Cons |
|---|---|---|
| Arduino / PlatformIO | Fast start, many libraries | Hides timer and core configuration; porting to Bluepad32's template later |
| ESP-IDF | Direct GPTimer and FreeRTOS control; fits a BARR-C, register-level style; Bluepad32 integrates as a component | More setup |

## Decision

ESP-IDF (C, BARR-C style, fixed-width types). Bluepad32 is added as a component when
Pilot mode is implemented; the project layout anticipates it from the start.

## Consequences

- Core assignment: Bluetooth on core 0; motion ISR, sequencer and feedback tasks
  pinned to core 1.
- The sequencer's `handle()` contains no hardware calls, so it is unit-tested on the
  host (`firmware/test/`).
