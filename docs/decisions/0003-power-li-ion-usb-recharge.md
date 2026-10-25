# ADR-0003: 1S Li-ion with USB charging and 5 V boost

- **Status:** Accepted (replaces the initial 4× NiMH AA plan)
- **Date:** 2026-10-25

## Context

The first plan was 4× NiMH AA (4.8 V nominal) straight onto the 5 V rail. Two problems:

1. **Dropout.** The ESP32 board's AMS1117-3.3 needs ≥ ~4.4 V in. A 4× NiMH pack sags
   to ~4.0–4.4 V under stepper load late in the discharge, putting the 3.3 V rail
   below the ESP32's 3.0 V minimum.
2. **Recharging.** The toy should be USB-rechargeable. Charging NiMH correctly needs
   −ΔV or temperature termination. Cheap USB NiMH boards are mostly timer-based.

## Options

| Option | Pros | Cons |
|---|---|---|
| A. 4× NiMH + on-board NiMH charger | Safe chemistry | Poor charge termination on cheap boards; dropout issue remains |
| B. 1S Li-ion + TP4056/DW01 + 5 V boost | Stable 5 V for the whole discharge; standard parts; USB charging | Li-ion safety needs care |
| C. Commercial power bank inside | Certified | Bulky; many switch off at low load and would kill an idle rover |

## Decision

Option B: protected 18650 (XTAR 3500 mAh) → TP4056 charger with DW01 protection
(micro-USB) → rocker switch → 5 V / 2 A boost converter.

## Consequences

- Stable 5 V: the AMS1117 dropout problem disappears; motor torque is constant.
- Separate charger and boost avoid the auto-off behaviour of integrated
  charge+boost modules.
- Protection in depth: firmware cut-off, boost UVLO, DW01, cell PCB
  (see [power.md](../power.md)).
- The cell needs a holder sized for protected cells.
- The battery divider measures the cell (3.0–4.2 V), not a 5 V pack.
- Charge supervised; screwed battery compartment.
- The USB-C TP4056 variant was out of stock. The micro-USB variant also avoids the
  missing-CC-resistor problem of cheap USB-C boards.
