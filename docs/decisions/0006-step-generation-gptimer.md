# ADR-0006: Step generation in a GPTimer ISR

- **Status:** Accepted (acceleration ramp: open, decided at bench test)
- **Date:** 2026-10-25

## Context

15 RPM × ~4076 half-steps/rev ÷ 60 ≈ 1000 half-steps/s, so a ~1 ms step period
(probably 1.2–1.5 ms in practice for torque margin). Jitter must stay low, including
when Bluetooth is active.

## Options

| Option | Pros | Cons |
|---|---|---|
| FreeRTOS task + `vTaskDelay` | Simple | Resolution is one tick (10 ms at ESP-IDF's default 100 Hz); cannot produce 1.3 ms; preemption jitter |
| `esp_timer` | µs resolution | Callbacks dispatched from a task by default: scheduling jitter |
| **GPTimer ISR** | Hardware alarm, deterministic, independent of the BT core | ISR must be tiny and IRAM-safe |

## Decision

One GPTimer periodic alarm drives **both** motors:

- Every Bee-Bot move uses equal step counts on both wheels; only the directions
  differ. One ISR tick advances both motors one half-step, so straight runs are
  straight by construction.
- The ISR indexes an 8-entry half-step table, writes all 8 coils with one
  `GPIO.out_w1ts` / `out_w1tc` pair, decrements `steps_remaining`. At zero it stops the
  alarm, de-energises the coils and posts `MOTION_DONE` to the sequencer queue.
- The callback and phase table are IRAM-safe (`IRAM_ATTR`,
  `CONFIG_GPTIMER_ISR_IRAM_SAFE`).
- The period is **per step**, not fixed, so an acceleration ramp can be added later
  as a lookup table applied with `gptimer_set_alarm_action`.

## Consequences

- All 8 coil pins in GPIO 0–31 (single register).
- Verification: logic analyzer on one coil pin, period jitter idle and with BT active.
- Open: whether a ramp is needed. Decided when the bench test shows whether the motors
  start reliably at the chosen period with the rover's real weight.
