# ADR-0009: MIT for code, CC BY-SA 4.0 for hardware and docs

- **Status:** Accepted
- **Date:** 2026-10-25

## Context

The repository should let anyone rebuild and adapt the rover.

## Decision

- `firmware/`: MIT License.
- `hardware/` and `docs/`: Creative Commons Attribution-ShareAlike 4.0.

## Consequences

- Derivatives of the physical design stay open; the firmware can be reused freely.
- Bluepad32 and its Bluetooth stack carry their own licenses. Check their terms
  before any commercial use of a build that includes Pilot mode.
