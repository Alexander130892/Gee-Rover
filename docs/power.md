# Power

Decision record: [ADR-0003](decisions/0003-power-li-ion-usb-recharge.md).

## Architecture

```
micro-USB ─► TP4056 + DW01 ──B+/B−── 18650 Li-ion (protected)
               │
              OUT+ ─► rocker switch ─┬─► 5 V / 2 A boost ─► 5 V rail
                                     │                       ├─► ESP32 5V pin (→ AMS1117 → 3.3 V)
                                     │                       ├─► 2× ULN2003 + 28BYJ-48
                                     │                       ├─► 74AHCT125 + WS2812 eyes
                                     │                       └─► buzzer driver
                                     └─► 100 k / 100 k divider ─► ESP32 ADC1 (cell voltage)
```

- The **switch sits after the charger output**: the cell charges with the rover off,
  and the divider does not drain the cell while it is off.
- The **boost converter** holds the rail at a stable 5 V for the whole discharge. That
  keeps motor torque consistent and keeps the ESP32's AMS1117 out of dropout.
- **1000 µF on the 5 V rail**, close to the ESP32, absorbs stepper switching transients.

## Protection layers

| Layer | Trips at | Purpose |
|---|---|---|
| Firmware "tired rover" | ~3.4 V under load (TBC on bench) | Refuse GO, red eyes; graceful stop before any hardware cut-off |
| Boost converter UVLO | < 2.7 V in (restarts > 3.2 V) | — |
| TP4056 board DW01 | < 2.5 V or > 3 A | Over-discharge, over-current, short |
| Cell protection PCB | ~2.5 V, over-current, 4.2 V | Last line of defence |

## Power budget (estimates, to be measured)

| Load | Current @ 5 V |
|---|---|
| 2× 28BYJ-48 energised (half-step) | ~2 × 160–240 mA |
| ESP32 active, radio off | ~50–80 mA |
| ESP32 Bluetooth peaks (Pilot mode) | up to ~250 mA |
| 2× WS2812 | up to ~2 × 60 mA at full white |
| Buzzer (peak, 50 % duty) | ~125 mA peak |

Driving: about 3 W from the 5 V rail, so roughly 0.9 A from the cell through the boost.
The 3500 mAh cell (~13 Wh) covers several 30-minute play sessions per charge.
Motors are de-energised when idle.

## Battery monitoring

Divider of 100 kΩ / 100 kΩ: 4.2 V full → 2.1 V at the ADC, inside the linear range.
Add 100 nF from the ADC pin to GND. Use an **ADC1** pin: ADC2 is shared with the Wi-Fi
driver.

## Charging

- Any USB charger with a micro-USB cable. The TP4056 charges at 1 A, so a full charge
  of the 3500 mAh cell takes about 4 hours.
- TP4056 LEDs: red = charging, blue = full. The shell has a light pipe for them.
- **Charge under supervision**, not unattended overnight in a toy box.
- Power switch **off** while flashing firmware over the ESP32's USB port.
