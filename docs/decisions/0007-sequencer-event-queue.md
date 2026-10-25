# ADR-0007: Single event queue, pure state machine

- **Status:** Accepted
- **Date:** 2026-10-25

## Context

The sequencer must react to buttons, motion completion (from an ISR) and the
inter-step pause timer, and must handle CLEAR at any moment without races.

## Options

| Option | Pros | Cons |
|---|---|---|
| Polling flags | Simple | Races, missed events, busy loop |
| Task notifications per source | Light | Separate paths; ordering between sources not guaranteed |
| **One FIFO event queue, one consumer** | Total ordering; trivially testable | One more queue |

## Decision

- Events: `BTN_FWD`, `BTN_BACK`, `BTN_LEFT`, `BTN_RIGHT`, `BTN_GO`, `BTN_CLEAR`,
  `MOTION_DONE`, `PAUSE_DONE`.
- The ISR posts with `xQueueSendFromISR`; the pause timer is an `esp_timer` one-shot.
- The sequencer task blocks on `xQueueReceive`, then `next = handle(state, event)`.
- `handle()` calls only the motion/buzzer/LED APIs, so it compiles and runs on the host.
- States `MOVING` and `PAUSING` are separate, so each completion event is accepted in
  exactly one state.
- Rule: ignore `MOTION_DONE` / `PAUSE_DONE` in any other state.

## Consequences

- Stale completions after a CLEAR are dequeued before any later GO and are ignored in
  `IDLE`. No move IDs are needed, because only one move is ever in flight.
- Transition table: [sequencer.md](../sequencer.md).
