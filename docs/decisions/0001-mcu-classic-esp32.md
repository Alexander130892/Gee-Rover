# ADR-0001: Classic ESP32 as the microcontroller

- **Status:** Accepted
- **Date:** 2026-10-24

## Context

The rover needs 8 motor outputs, 6 button inputs, a buzzer, an LED data line and one
ADC channel. The Pilot-mode stretch goal needs a Bluetooth gamepad, and Bluepad32
supports Bluetooth Classic pads (DualShock 4, Switch Pro, ...) as well as BLE pads.

## Options

| Option | Pros | Cons |
|---|---|---|
| Classic ESP32 (WROOM-32) | Enough GPIO; BT Classic + BLE; cheap; already in hand | Strapping and flash pins reduce the usable set; ADC2 shared with Wi-Fi |
| ESP32-S3 / C3 | Newer cores, USB native | BLE only: no Bluetooth Classic gamepads |
| RP2040 / AVR | Simple | No radio, so Pilot mode needs extra hardware |

## Decision

Classic ESP32 on a 30-pin dev board (ESP32-WROOM-32, USB-C, AMS1117-3.3 regulator).

## Consequences

- The pin map must avoid flash pins 6–11 and strapping pins for buttons
  (see [pinout.md](../pinout.md)).
- The AMS1117's ~1.1 V dropout requires a stable 5 V input. Solved by ADR-0003.
