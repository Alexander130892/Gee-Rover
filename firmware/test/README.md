# Host tests

Unit tests for `sequencer` `handle(state, event)`, compiled with the host compiler.
The motion, buzzer and LED calls are replaced by fakes that record what was called.

Minimum cases, one per row of the transition table in
[sequencer.md](../../docs/sequencer.md), plus:

- 21st arrow press gives the "full" beep and is not stored
- GO with an empty program gives the error beep
- CLEAR in `MOVING` and in `PAUSING` stops and wipes
- stale `MOTION_DONE` / `PAUSE_DONE` in `IDLE` are ignored
- GO after completion replays the same program
