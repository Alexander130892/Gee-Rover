# Interaction model and sequencer

Decision records: [ADR-0004](decisions/0004-bee-bot-interaction-model.md),
[ADR-0007](decisions/0007-sequencer-event-queue.md).

## For the child

| Button | Effect |
|---|---|
| ↑ | Add "one square forward" |
| ↓ | Add "one square back" |
| ← / → | Add "turn 90° left / right on the spot" |
| **GO** | Run the program. The program stays in memory, so GO again replays it. New presses are added to the end. |
| **CLEAR** (red) | Stop immediately and erase the program |

- Every press gives a short beep. After 20 steps the rover gives a "full" beep and
  ignores further moves.
- While driving, only CLEAR does anything.
- Between steps the rover pauses briefly and blinks its eyes.

## State machine

States: `IDLE` (program may be non-empty), `MOVING`, `PAUSING`.

| State | Event | Action | Next |
|---|---|---|---|
| IDLE | arrow | if len < 20: append + short beep; else "full" beep | IDLE |
| IDLE | GO | if len > 0: idx = 0, `motion_start(prog[0])`; else error beep | MOVING / IDLE |
| IDLE | CLEAR | wipe + clear beep | IDLE |
| MOVING | MOTION_DONE | step beep/blink, start pause timer | PAUSING |
| MOVING | CLEAR | `motion_stop()`, wipe | IDLE |
| PAUSING | PAUSE_DONE | idx++; if idx < len: `motion_start(prog[idx])` | MOVING |
| PAUSING | PAUSE_DONE (last) | "mission complete" jingle, keep program | IDLE |
| PAUSING | CLEAR | `esp_timer_stop()`, wipe | IDLE |
| any | anything else | ignore | — |

### Why stale events are harmless

All events (buttons, `MOTION_DONE` from the motion ISR, `PAUSE_DONE` from the pause
timer) go through one FIFO queue to one consumer. Each completion event is only
accepted in the single state that expects it. A completion posted around a CLEAR is
always dequeued before any later GO, lands in `IDLE`, and is ignored.
