# Bring-up and test plan

Hardware is brought up one block at a time. Each test has a measurable pass
criterion; a test only starts when the tests it depends on have passed. Record the
measured value, not just "OK". Firmware logic is tested separately on the host
(`firmware/test/`).

Instruments: multimeter, logic analyzer. No bench supply or oscilloscope assumed.

## Results

| ID | Test | Depends on | Date | Measured | Result |
|---|---|---|---|---|---|
| T01 | Cell and charger | — | 2026-11-19 | 3.64 V as delivered → 4.16 V after ~4 h, LED turned blue | **Pass** |
| T02 | Boost, no load | T01 | 2026-11-19 | 5.16 V on, 0 V off. First attempt: OUT± 2.6 V (DW01 trip, likely a loose strand), reset after rewiring | **Pass** |
| T03 | Boost under motor load | T02 | | | |
| T04 | Battery divider | T01 | | | |
| T05 | ESP32 on the 5 V rail | T03 | | | |
| T06 | Battery ADC accuracy | T04, T05 | | | |
| T07 | Buttons | T05 | | | |
| T08 | Buzzer driver | T05 | | | |
| T09 | WS2812 eyes | T05 | | | |
| T10 | One motor: sequence and timing | T03, T05 | | | |
| T11 | Start reliability (decides the ramp) | T10 | | | |
| T12 | Both motors, rail stability | T10 | | | |
| T13 | Current draw | T12 | | | |
| T14 | Thermal | T12 | | | |
| T15 | Calibration on the mat | T12, chassis | | | |
| T16 | Runtime and low-battery stop | T15 | | | |
| T17 | Step jitter with Bluetooth active | T10, Pilot mode | | | |

## Power

### T01 — Cell and charger

1. Measure the new cell: expect ~3.5–3.8 V (shipping charge).
2. Solder the cell holder to TP4056 **B+/B−** (not OUT±). Check polarity twice.
3. Charge from a USB charger. Red LED = charging.
4. When the LED turns blue, measure the cell.

**Pass:** charging terminates (blue) and the cell reads **4.15–4.20 V**.
Record the charge time.

### T02 — Boost, no load

1. Mark IN+/IN−/OUT+/OUT− on the boost board before connecting. It has **no
   reverse-polarity protection**.
2. TP4056 OUT+ → rocker switch → boost IN+; OUT− → boost IN−. Nothing on the output.
3. Switch on; measure the output.

**Pass:** **4.90–5.25 V** (USB VBUS limit; every load on the rail is rated for it); switch off → output
drops to 0 V.

**If OUT± reads well below B±** (e.g. 2.6 V with the cell at 4.1 V): the DW01 protection
has switched OUT− off, after a short or an over-current. Remove the cause, then plug in
the micro-USB charger for a few seconds to reset it.

### T03 — Boost under motor load

A held stepper is a convenient dummy load (~160–240 mA per motor).

1. Connect one ULN2003 board to the boost output (+, −). Fit the 1000 µF across the
   output.
2. Tie IN1 and IN2 to 5 V with jumper wires: the motor holds two coils energised.
3. Measure the output; then do the same with both ULN2003 boards.

**Pass:** **≥ 4.85 V** with both motors holding. Both ULN2003 boards and the boost are
only warm after 2 minutes.

### T04 — Battery divider

1. Build the 100 kΩ / 100 kΩ divider with 100 nF, fed from TP4056 OUT+ after the switch.
2. Measure the cell and the divider midpoint.

**Pass:** midpoint = cell / 2 **± 2 %**. With the switch off, the midpoint reads 0 V
(the divider does not drain the cell while the rover is off).

## Controller

### T05 — ESP32 on the 5 V rail

Rules from experience with USB hosts that refuse to enumerate when VBUS is already live:
- **Flash with the rocker switch off.**
- For tests that need the serial monitor while on battery power: **plug in the laptop
  first, then switch on.**

1. Boost OUT+ → **V5**, OUT− → GND. Flash a hello-world that logs once per second.
2. Switch off, unplug USB, switch on. Measure the 3V3 pin.
3. Plug the laptop in first, then switch on: does the monitor still show the log?

**Pass:** 3V3 = **3.3 ± 0.1 V** on battery power; the board boots without USB; the
serial monitor works in the documented order. Note what happens in the other order.

### T06 — Battery ADC accuracy

1. Divider to GPIO 39. Read with `adc_oneshot` + `adc_cali` (curve fitting / line
   fitting), 11 dB attenuation, averaged over 16 samples.
2. Compare with the multimeter at the cell, at two charge levels if possible.

**Pass:** firmware cell voltage within **± 50 mV** of the multimeter.

### T07 — Buttons

1. Wire all six buttons (pull-ups per [pinout.md](pinout.md)). Firmware: polled scan
   every 5 ms, logs each debounced press with its name.
2. Press each button 10 times.
3. Phantom test: leave buttons untouched, sample the battery ADC at 100 Hz for 60 s.

**Pass:** 60/60 presses logged under the right name; **zero** presses during the
phantom test.

### T08 — Buzzer driver

1. Build the SS8050 driver (470 Ω base, 22 Ω series, 1N4148 across the buzzer).
2. LEDC tone at 2 kHz, 50 % duty. Then sweep 500–4000 Hz.
3. During a continuous tone, measure the DC voltage across the 22 Ω (average current
   ≈ V / 22).

**Pass:** clearly audible at arm's length, loudest near 2 kHz; average current
**≤ 70 mA**; transistor and resistor only warm after 1 minute. If too loud, change
22 Ω → 47 Ω and record it here.

### T09 — WS2812 eyes

1. GPIO 4 → 74AHCT125 → 470 Ω → LED 1 → LED 2. 100 nF at the 74AHCT125 VCC pin.
2. Logic analyzer on the 74AHCT125 output: logic high must be 5 V level (check with
   the multimeter on a static high).
3. Show red, green, blue, white on each eye.

**Pass:** both eyes show the commanded colours in the right order (catches GRB/RGB
mix-ups); no flicker over 1 minute.

## Motion

### T10 — One motor: sequence and timing

1. Left motor on GPIO 25/26/27/14. Firmware: GPTimer ISR, half-step table, fixed period
   (start at 1.5 ms).
2. Logic analyzer on all four coil pins: check the 8-step half-step pattern and
   direction reversal.
3. Measure the period on one pin over ≥ 1000 steps.
4. Mark the output shaft; command **4076** half-steps.

**Pass:** pattern correct in both directions; period within **± 10 µs** of nominal;
the shaft mark returns to its start (± a few degrees). Record the error. It is the
first estimate of the true gear ratio.

### T11 — Start reliability (decides the acceleration ramp, ADR-0006)

1. Motor loaded realistically: mounted in the chassis with the rover's full weight,
   on the mat.
2. For periods 1.5, 1.3, 1.2, 1.1 ms: 20 starts from standstill, each one square.

**Pass:** the shortest period with **20/20** clean starts (no stall, no buzzing in
place). Use ~20 % margin above it as the operating period. If no period ≥ 1.2 ms
passes, add a ramp and record the decision in a new ADR.

### T12 — Both motors, rail stability

1. Both motors; program of 20 moves including all four directions, repeated 5×.
2. Measure the 5 V rail during motion (minimum reading).

**Pass:** 100 moves without a brownout reset (check the reset reason in the log);
rail **≥ 4.85 V**.

### T13 — Current draw

Multimeter (10 A range) in series with the rocker switch.

| State | Expected | Measured |
|---|---|---|
| Idle, coils off, eyes dim | ~0.1 A | |
| Driving, both motors | ~0.9 A | |
| Peak (driving + beep + eyes) | < 1.2 A | |

**Pass:** all states within the expected range. Update [power.md](power.md) with the
measured values.

### T14 — Thermal

After 30 minutes of continuous mission loops, touch-check, or measure if possible:
motors, ULN2003, boost, buzzer resistor.

**Pass:** nothing hotter than **~50 °C** (can be held comfortably).

### T15 — Calibration on the mat

1. Forward 4 squares from a grid corner; measure the error. Adjust
   `STEPS_PER_SQUARE`.
2. Right turn ×4; measure the heading error. Adjust `STEPS_PER_90_DEG`. Repeat for left.
3. Run a 10-move test course that ends on the start square.

**Pass:** after the 10-move course, the rover is within **±1 cm** and **±5°** of its start.
Record the constants in [build-guide.md](build-guide.md).

### T16 — Runtime and low-battery stop

1. Full cell. Run mission loops continuously until "tired rover".
2. Log the cell voltage every minute.

**Pass:** runtime **≥ 30 min** (several hours expected); "tired rover" engages at the
firmware threshold before any hardware cut-off; GO is refused afterwards. Record the
runtime and the voltage curve.

### T17 — Step jitter with Bluetooth active

Repeat the T10 period measurement with Bluepad32 running and a gamepad connected.

**Pass:** period within **± 10 µs**, as in T10.
