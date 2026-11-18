# Build guide

Work in progress: steps are filled in as the first unit is built.

## 0. Before you start

- Read [power.md](power.md): the rover uses a Li-ion cell.
- Order the parts from the [BoM](bom.md).
- Tools: 3D printer, soldering iron with heat-set insert tip, multimeter. A logic
  analyzer is recommended for checking step timing.

## 1. Print the parts

<!-- TODO: part list, orientation, material, infill, supports — see hardware/stl/README.md -->

## 2. Electronics on the bench

Follow the [test plan](test-plan.md) in order: power chain (T01–T04), controller and
peripherals (T05–T09), then motion (T10–T14). Each block is tested before the next
one is connected.

<!-- TODO: schematic in docs/wiring/, photos per step -->

## 3. Flash the firmware

See [`firmware/README.md`](../firmware/README.md).

## 4. Calibrate

The 28BYJ-48 gear ratio varies (often ~63.68:1, not 64:1), and turns depend on track
width and tyre grip. Calibrate **on the actual mat**:

1. Steps per square: drive 4 squares, measure, adjust `STEPS_PER_SQUARE`.
2. Steps per 90°: turn 4× right, check the rover faces the start direction, adjust
   `STEPS_PER_90_DEG`.

<!-- TODO: record final calibration values per unit -->

## 5. Final assembly

<!-- TODO -->

## 6. Hand-over checklist

- [ ] Cell fully charged, battery compartment screwed shut
- [ ] Micro-USB cable included
- [ ] Short instruction card for the parents (charging, CLEAR = stop)
