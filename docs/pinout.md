# ESP32 pin map

Board: 38-pin ESP32-DevKitC V4 layout (AZ-Delivery), micro-USB, **ESP32-WROOM-32**
module. Decision record: [ADR-0010](decisions/0010-pin-map.md).

The map deliberately **does not use GPIO 16/17**, so it also works on boards with a
WROVER module (where those pins belong to the PSRAM).

## Assignment

| GPIO | Header | Function | Direction / peripheral | Why this pin |
|---|---|---|---|---|
| 25 | L | Left motor IN1 | Out (GPIO register 0) | Coils must be < 32 for one `out_w1ts/w1tc` write; 25-26-27-14 are adjacent on the left header |
| 26 | L | Left motor IN2 | Out | ″ |
| 27 | L | Left motor IN3 | Out | ″ |
| 14 | L | Left motor IN4 | Out | ″ (may toggle briefly at boot: harmless, coils are off before init) |
| 23 | R | Right motor IN1 | Out | 23-22-21-19 are on the right header, separated only by TX/RX/GND |
| 22 | R | Right motor IN2 | Out | ″ |
| 21 | R | Right motor IN3 | Out | ″ |
| 19 | R | Right motor IN4 | Out | ″ |
| 32 | L | **CLEAR** | In, internal pull-up | Safety button (stop): Clean pin, no external part to fail |
| 33 | L | **GO** | In, internal pull-up | Clean pin |
| 13 | L | → RIGHT | In, internal pull-up | Last Clean pin |
| 34 | L | ↑ FORWARD | In, **external 10 kΩ to 3V3** | Input-only, no internal pull-up |
| 35 | L | ↓ BACK | In, **external 10 kΩ to 3V3** | ″ |
| 36 (VP) | L | ← LEFT | In, **external 10 kΩ to 3V3** + 100 nF to GND | Input-only; errata 3.11 glitch while ADC1 samples → RC filter + polled debounce |
| 39 (VN) | L | Battery voltage | ADC1 channel 3 | Input-only; ADC1 (ADC2 is shared with Wi-Fi) |
| 18 | R | Buzzer | Out, LEDC PWM | Any output pin works |
| 4 | R | WS2812 data (via 74AHCT125) | Out, RMT | Any output pin works |

### Reserved for Defend mode (not populated)

| GPIO | Function | Why this pin |
|---|---|---|
| 2 | Servo | Strapping: internal pull-down holds it low at reset, so no stray servo pulse |
| 5 | IR receiver (TSOP) | Strapping, must be high at reset: a TSOP output idles high |
| 15 | IR LED (via transistor) | Strapping; a boot-time glitch is only an invisible IR flash |

### Not used

| GPIO | Reason |
|---|---|
| 0 | BOOT button; low at reset = download mode |
| 12 | Strapping: high at reset selects 1.8 V flash and the chip won't boot |
| 16, 17 | PSRAM on WROVER modules (kept free for portability) |
| 1, 3 | UART0: flashing and logging |
| 6–11 (SD0–SD3, CMD, CLK) | SPI flash. Never connect. |

## Pin buckets (reference)

| Bucket | GPIO |
|---|---|
| Clean (I/O, internal pull-up, no boot role) | 4, 13, 14, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33 (+ 16, 17 on WROOM only) |
| Strapping | 0, 2, 5, 12, 15 |
| Input-only, no pull-up (ADC1) | 34, 35, 36, 39 |
| Never | 1, 3, 6–11 |

GPIO 32 and 33 live in the second output register (`out1_w1ts`), so they cannot share
the single-write coil update. That is why they carry buttons.

## Firmware rules that follow from this map

- **Buttons are read by polled debounce**, not edge interrupts. On GPIO 36/39 the input
  pulses low for ~80 ns whenever ADC1 samples (ESP32 errata 3.11); an edge ISR would
  register phantom LEFT presses.
- Coil masks: left `(1<<25)|(1<<26)|(1<<27)|(1<<14)`, right
  `(1<<23)|(1<<22)|(1<<21)|(1<<19)`, both in `GPIO.out_w1ts` / `GPIO.out_w1tc`.
- Drive all coil pins low in the first lines of `app_main`, before any other init.

## Wiring notes

- 5 V rail (boost output) → the board's **V5** pin.
- ULN2003 inputs accept 3.3 V logic directly.
- WS2812 data: GPIO 4 → 74AHCT125 (VCC = 5 V, /OE to GND) → 470 Ω → first LED DIN.
- Buzzer: GPIO 18 → 470 Ω → SS8050 base; buzzer + 22 Ω between 5 V and collector;
  1N4148 across the buzzer (cathode to 5 V).
- Battery: cell+ → 100 kΩ → GPIO 39 → 100 kΩ → GND, 100 nF from GPIO 39 to GND.
- Buttons: each switch between its GPIO and GND.
