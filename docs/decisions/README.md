# Architecture Decision Records

Each record captures one decision: the context, the options considered, the choice
and its consequences. Records are never rewritten. When a decision changes, add a new
record and mark the old one `Superseded by ADR-XXXX`.

| ADR | Title | Status |
|---|---|---|
| [0001](0001-mcu-classic-esp32.md) | Classic ESP32 as the microcontroller | Accepted |
| [0002](0002-drivetrain-28byj48-steppers.md) | 28BYJ-48 steppers, open loop | Accepted |
| [0003](0003-power-li-ion-usb-recharge.md) | 1S Li-ion with USB charging and 5 V boost | Accepted |
| [0004](0004-bee-bot-interaction-model.md) | Bee-Bot interaction model, 6 buttons | Accepted |
| [0005](0005-firmware-esp-idf-bluepad32.md) | ESP-IDF with Bluepad32 as a component | Accepted |
| [0006](0006-step-generation-gptimer.md) | Step generation in a GPTimer ISR | Accepted |
| [0007](0007-sequencer-event-queue.md) | Single event queue, pure state machine | Accepted |
| [0008](0008-feedback-buzzer-ws2812.md) | Passive buzzer and WS2812 eyes with drivers | Accepted |
| [0009](0009-licensing.md) | MIT for code, CC BY-SA 4.0 for hardware and docs | Accepted |

Template: [`template.md`](template.md).
