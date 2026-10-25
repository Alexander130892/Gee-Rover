# ADR-0002: 28BYJ-48 steppers, open loop

- **Status:** Accepted
- **Date:** 2026-10-24

## Context

Mission mode needs repeatable moves on a 15 cm grid: one square forward/back and 90°
pivot turns. A 6-year-old's toy must be cheap, quiet and robust. Speed matters little.

## Options

| Option | Pros | Cons |
|---|---|---|
| DC gearmotors + encoders | Faster, more torque | Needs closed-loop control and encoder wiring for repeatable squares |
| DC gearmotors, timed | Simplest | Not repeatable: distance varies with battery and floor |
| 28BYJ-48 steppers + ULN2003 | Open-loop precision, cheap, geared, 3.3 V-logic drivers | Slow (~15 RPM), modest torque, 8 GPIOs |

## Decision

2× 28BYJ-48 (5 V) with ULN2003 drivers, half-step drive, two driven wheels plus a ball
caster.

## Consequences

- The gear ratio is often ~63.68:1 (~4076 half-steps/rev), not the nominal 64:1, and
  varies per unit. Steps per square and steps per 90° are **calibrated empirically on
  the mat** and stored as constants.
- At ~15 RPM with 60 mm wheels, one 15 cm square takes about 3 s.
- Coils are de-energised when idle to save power and keep the motors cool.
- A spare motor is part of the BoM.
