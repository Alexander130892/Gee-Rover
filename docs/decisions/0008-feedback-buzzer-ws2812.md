# ADR-0008: Passive buzzer and WS2812 eyes with drivers

- **Status:** Accepted
- **Date:** 2026-10-25

## Context

Feedback is essential for a child who cannot read: a beep per press, a "full" beep,
a mission-complete jingle, and expressive eyes (including "tired rover" on low battery).

## Decision

**Buzzer:** passive 16 Ω electromagnetic buzzer (~2 kHz resonance) driven by an
SS8050 NPN low-side switch from the 5 V rail:
- 470 Ω base resistor: ~5.5 mA base current keeps the transistor saturated.
- 22 Ω series resistor: ~125 mA peak, ~0.17 W at 50 % duty (47 Ω if too loud).
- 1N4148 flyback diode across the coil.
- Driven by LEDC PWM at 50 % duty; step beeps near 2 kHz (loudest).

A direct GPIO drive would draw ~200 mA, about 5× the pin's absolute maximum.

**Eyes:** 2× WS2812B on the 5 V rail. The data line goes through a 74AHCT125 level
shifter (3.3 V → 5 V) and a 470 Ω series resistor. WS2812 V_IH is 0.7 × VDD = 3.5 V
at 5 V, above a 3.3 V GPIO high level.

## Consequences

- Three extra small parts per function, all on the perfboard.
- The buzzer module originally chosen (with an on-board transistor) was out of stock,
  which prompted this discrete driver.
