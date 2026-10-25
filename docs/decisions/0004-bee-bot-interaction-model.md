# ADR-0004: Bee-Bot interaction model, 6 buttons

- **Status:** Accepted
- **Date:** 2026-10-25

## Context

The primary user is 6 years old. The interaction must be learnable without reading and
consistent with how educational floor robots already work.

## Decision

- Follow Bee-Bot logic: arrows add steps, GO runs the program, the program stays in
  memory after a run, new presses append.
- **6 buttons**: ↑ ↓ ← → GO CLEAR. No separate STOP.
- **CLEAR = abort + wipe, in every state.** One button, one meaning; the child learns
  that CLEAR stops everything.
- **Program buffer: 20 steps.** When full, a distinct "full" beep; further moves are
  ignored.
- While driving, every button except CLEAR is ignored.

## Consequences

- A 7th "stop but keep the program" button was considered and rejected: it adds a
  GPIO and a state-table row for little value at this age.
- Full behaviour: [sequencer.md](../sequencer.md).
