# ESP32 pin map

Board: 30-pin ESP32-WROOM-32 dev board. Status: **draft, not yet assigned.**

## Signals to place

| Signal | Count | Direction | Requirement |
|---|---|---|---|
| Left motor IN1–IN4 | 4 | Out | GPIO 0–31, so one `GPIO.out_w1ts/w1tc` write updates both motors |
| Right motor IN1–IN4 | 4 | Out | Same register as the left motor |
| Buttons ↑ ↓ ← → GO CLEAR | 6 | In | Internal pull-up required, active low |
| Buzzer | 1 | Out (LEDC PWM) | Any output-capable pin |
| WS2812 data | 1 | Out (RMT) | Any output-capable pin, through the 74AHCT125 |
| Battery voltage | 1 | ADC | ADC1 channel (ADC2 is shared with the Wi-Fi driver) |

## Constraints

| Pins | Constraint |
|---|---|
| GPIO 6–11 | Connected to the SPI flash. Never use. |
| GPIO 0, 2, 5, 12, 15 | Strapping pins, sampled at boot. Avoid for buttons (a held button changes the boot mode) and check the default level for outputs. GPIO 12 sets flash voltage: avoid entirely. |
| GPIO 1, 3 | UART0 TX/RX used for flashing and logging. Avoid. |
| GPIO 34–39 | Input only, **no internal pull-ups**. Fine for the ADC, not for buttons. |
| GPIO 32–39 | ADC1 |

## Assignment

| GPIO | Function | Notes |
|---|---|---|
| TBD | | |

<!-- Fill in after the pin-map design step; record the reasoning per pin. -->

## Wiring notes

- ULN2003 inputs accept 3.3 V logic directly.
- WS2812 data: GPIO → 74AHCT125 (VCC = 5 V, /OE to GND) → 470 Ω → first LED DIN.
- Buzzer: GPIO → 470 Ω → SS8050 base; buzzer + 22 Ω between 5 V and collector;
  1N4148 across the buzzer (cathode to 5 V).
