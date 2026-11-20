# Firmware

ESP-IDF project in C (BARR-C style, fixed-width types). Architecture decisions:
[ADR-0005](../docs/decisions/0005-firmware-esp-idf-bluepad32.md) to
[ADR-0008](../docs/decisions/0008-feedback-buzzer-ws2812.md).

## Status

Bring-up stage T05: coils forced off, reset reason and a 1 Hz heartbeat on the log.
Pin numbers live in `components/board/include/board_pins.h` (must match
[pinout.md](../docs/pinout.md)).

## Build and flash

```sh
. $IDF_PATH/export.sh          # ESP-IDF v5.3.2
cd firmware
idf.py build                   # target esp32 comes from sdkconfig.defaults
idf.py -p <port> flash monitor
```

Turn the rover's power switch **off** while flashing over USB.

## Module layout

| Component | Responsibility | Interface (planned) |
|---|---|---|
| `components/motion` | GPTimer ISR, half-step table, coil writes | `motion_start(move)`, `motion_stop()`; posts `MOTION_DONE` |
| `components/sequencer` | Program buffer (20 steps), state machine | `handle(state, event)` — pure, host-testable |
| `components/input` | Polled button debounce (no edge ISRs, see [ADR-0010](../docs/decisions/0010-pin-map.md)) | posts `BTN_*` events |
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
