# Firmware

ESP-IDF project in C (BARR-C style, fixed-width types). Architecture decisions:
[ADR-0005](../docs/decisions/0005-firmware-esp-idf-bluepad32.md) to
[ADR-0008](../docs/decisions/0008-feedback-buzzer-ws2812.md).

## Status

Skeleton only. Not yet built against a pinned ESP-IDF version.

## Build and flash

```sh
. $IDF_PATH/export.sh          # ESP-IDF v5.x — pin the exact version once chosen
cd firmware
idf.py set-target esp32
idf.py build
idf.py -p <port> flash monitor
```

Turn the rover's power switch **off** while flashing over USB.

## Module layout

| Component | Responsibility | Interface (planned) |
|---|---|---|
| `components/motion` | GPTimer ISR, half-step table, coil writes | `motion_start(move)`, `motion_stop()`; posts `MOTION_DONE` |
| `components/sequencer` | Program buffer (20 steps), state machine | `handle(state, event)` — pure, host-testable |
| `components/input` | Button debouncing | posts `BTN_*` events |
| `components/feedback` | Buzzer (LEDC) and WS2812 eyes (RMT) | `beep(type)`, `eyes(mood)` |
| `components/battery` | ADC1 cell voltage, low-battery threshold | `battery_is_low()` |
| `test/` | Host unit tests for the sequencer | |

Each component directory gets its own `CMakeLists.txt`
(`idf_component_register(...)`) when its code is written.

## Core assignment

- Core 0: Bluetooth stack (Bluepad32, Pilot mode)
- Core 1: motion ISR, sequencer, input and feedback tasks

## Calibration constants

`STEPS_PER_SQUARE` and `STEPS_PER_90_DEG` are measured on the mat per unit
(see [build guide](../docs/build-guide.md#4-calibrate)).
