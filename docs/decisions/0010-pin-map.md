# ADR-0010: Pin map without GPIO 16/17

- **Status:** Accepted
- **Date:** 2026-11-18

## Context

17 signals must be placed: 8 coils, 6 buttons, buzzer, WS2812 data and battery ADC,
plus 3 reserved for Defend mode (servo, IR LED, IR receiver). The repository is meant
to be rebuilt by others, who will buy whatever "ESP32 devkit" they find. On WROVER
modules GPIO 16/17 are taken by the PSRAM.

Constraints:
- Coils in GPIO 0–31, so both motors update in one register write (ADR-0006).
- Buttons need a pull-up and must not sit on strapping pins (a held button at power-on
  would change the boot mode).
- Battery ADC on ADC1.

## Options

| Option | Pros | Cons |
|---|---|---|
| Use GPIO 16/17 | 15 Clean pins; fewer external parts | Fails on WROVER boards |
| **Avoid GPIO 16/17; 3 buttons on input-only pins with external pull-ups** | Works on WROOM and WROVER; no button on a strapping pin | 3× 10 kΩ + 1× 100 nF; zero spare Clean pins |

## Decision

Avoid GPIO 16/17. Assignment in [pinout.md](../pinout.md):
- Coils on 25/26/27/14 (left header) and 23/22/21/19 (right header).
- CLEAR and GO on Clean pins with internal pull-ups (CLEAR is the safety button).
- Three arrows on input-only 34/35/36 with external pull-ups; battery ADC on 39.
- Defend mode reserved on strapping pins 2/5/15, chosen so each pin's boot level is
  compatible with the device on it.

## Consequences

- Buttons are scanned with polled debounce, never edge interrupts, because of the
  GPIO 36/39 glitch during ADC1 sampling (ESP32 errata 3.11). GPIO 36 also gets a
  100 nF filter capacitor.
- No spare pin with an internal pull-up remains. A future input needs an external
  pull-up, or GPIO 16/17 on WROOM-only builds.
- The boards' USB-UART chip and connector do not matter to the map.
