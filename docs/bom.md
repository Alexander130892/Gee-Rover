# Bill of materials

Prices are from TinyTronics (NL) in October 2026, incl. VAT. Quantities include
spares where noted. Equivalent parts from any shop work; check the notes column for
the property that actually matters.

## Electronics

| # | Part | Qty | Unit € | Source | Notes |
|---|---|---|---|---|---|
| 1 | ESP32 dev board, 30-pin, ESP32-WROOM-32, USB-C | 1 | ~5 | any | Classic ESP32 needed for Bluetooth Classic + BLE (Bluepad32). The tested board has an AMS1117-3.3 regulator. |
| 2 | 28BYJ-48 stepper motor, **5 V** | 3 | 2.50 | [TinyTronics](https://www.tinytronics.nl/en/mechanics-and-actuators/motors/stepper-motors/28byj-48-stepper-motor-5v) | 2 + 1 spare. Must be the 5 V, 5-wire unipolar version. |
| 3 | ULN2003 stepper driver module | 3 | 3.00 | [TinyTronics](https://www.tinytronics.nl/en/mechanics-and-actuators/motor-controllers-and-drivers/stepper-motor-controllers-and-drivers/uln2003-stepper-motor-driver-module) | 2 + 1 spare |
| 4 | WS2812B on small PCB | 4 | 0.50 | [TinyTronics](https://www.tinytronics.nl/en/components/leds/leds/ws2812b-digital-5050-rgb-led-pcb-separate-white) | 2 eyes + spares |
| 5 | SN74AHCT125N level shifter (DIP-14) | 2 | 1.00 | [TinyTronics](https://www.tinytronics.nl/en/components/ics-and-microcontroller-chips/ics/sn74ahct125n-4-channel-level-converter-3.3v-to-5v-14-pin-dip) | 3.3 V → 5 V for WS2812 data |
| 6 | Passive buzzer 16 Ω, 2 kHz, with leads | 2 | 1.00 | [TinyTronics](https://www.tinytronics.nl/en/audio/speakers/buzzers/passive-buzzer-3-12v-ac-2khz-dupont-jumper) | Passive = melodies possible. Needs the transistor driver. |
| 7 | SS8050 NPN transistor | 3 | 0.20 | [TinyTronics](https://www.tinytronics.nl/en/components/transistors/npn-transistor-ss8050) | Buzzer driver. Check pinout (usually E-B-C). |
| 8 | 1N4148 diode | 3 | 0.10 | [TinyTronics](https://www.tinytronics.nl/nl/componenten/diodes/diode-high-speed-1n4148) | Buzzer flyback diode |
| 9 | Resistor set 10 Ω–1 MΩ, 1/4 W | 1 | 5.00 | [TinyTronics](https://www.tinytronics.nl/en/components/resistors/resistors/10%CF%89-1m%CF%89-resistor-set) | Uses: 22 Ω, 470 Ω (×2), 100 kΩ (×2) |
| 10 | 1000 µF 25 V electrolytic | 3 | 0.25 | [TinyTronics](https://www.tinytronics.nl/en/components/capacitors/aishi-elektrolytic-capacitor-1000uf-25v) | Bulk capacitor on the 5 V rail |
| 11 | 100 nF ceramic capacitor | 5 | — | any | Decoupling (74AHCT125) and ADC filter |
| 12 | Tactile switch set with keycaps (4 arrows + OK), 12×12 mm | 1 | 3.00 | [TinyTronics](https://www.tinytronics.nl/en/switches/manual-switches/pcb-switches/tactile-pushbutton-switch-set-with-keycaps-5x-black) | ↑ ↓ ← → and GO |
| 13 | Tactile switch 12×12×7.3 mm | 2 | 0.25 | [TinyTronics](https://www.tinytronics.nl/shop/nl/componenten/schakelaars/tactile-pushbutton-switch-momentary-4pin-12*12*7.3mm) | CLEAR + spare |
| 14 | Button cap 12×12, red | 1 | 0.15 | [TinyTronics](https://www.tinytronics.nl/en/components/knobs,-caps-and-covers/button-cap-for-tactile-pushbutton-switch-momentary-12x12x7.3mm-red) | CLEAR |
| 15 | JST-XH 6p cable + header | 2 | 1.00 | [TinyTronics](https://www.tinytronics.nl/en/cables-and-connectors/cables-and-adapters/jst-compatible/jst-xh-6p-compatible-connector-with-cable-and-pcb-connector) | ULN2003 control leads |
| 16 | JST-XH 2p cable + header | 2 | 0.40 | [TinyTronics](https://www.tinytronics.nl/en/cables-and-connectors/cables-and-adapters/jst-compatible/jst-connector-with-cable-and-pcb-connector) | Battery lead |
| 17 | Perfboard, female 2.54 mm headers, hookup wire, heat shrink | — | — | any | Socket the ESP32 so it can be replaced |

## Power

See [power.md](power.md) for the reasoning and wiring.

| # | Part | Qty | Unit € | Source | Notes |
|---|---|---|---|---|---|
| 18 | XTAR 18650 Li-ion 3500 mAh, **protected**, button top | 1 | 8.50 | [TinyTronics](https://www.tinytronics.nl/en/power/batteries/18650/xtar-18650-li-ion-battery-with-with-protection-circuit-3500mah-10a) | Protected cells are longer than plain 18650s |
| 19 | 1× 18650 holder, button top (fits protected cells) | 1 | 1.00 | [TinyTronics](https://www.tinytronics.nl/en/power/battery-holders-and-clips/18650/1x-18650-battery-holder-with-loose-wires-button-top) | Standard holders do not fit protected cells |
| 20 | TP4056 charger 1 A with DW01 protection, micro-USB | 1 | 2.00 | [TinyTronics](https://www.tinytronics.nl/en/power/bms-and-chargers/li-ion-and-li-po/with-protection-circuit/tp4056-micro-usb-li-ion-charger-1a-with-li-ion-protection-circuit) | The USB-C variant also works; it lacks CC resistors, so only USB-A → USB-C cables charge it |
| 21 | DC-DC boost 5 V / 2 A | 1 | 3.00 | [TinyTronics](https://www.tinytronics.nl/shop/en/power/voltage-converters/boost-(step-up)-converters/dc-dc-step-up-boost-converter-2a-5v-output) | No reverse-polarity protection |
| 22 | Mini rocker switch, ≥3 A | 1 | ~0.50 | any | Not a SS12D00 mini slide switch (0.5 A rating is too low) |

## Mechanical

| # | Part | Qty | Unit € | Source | Notes |
|---|---|---|---|---|---|
| 23 | M3 heat-set inserts, 5.7 mm (20×) | 1 | 2.75 | [TinyTronics](https://www.tinytronics.nl/en/tools-and-mounting/installation-and-mounting-material/threaded-inserts/threaded-insert-m3-5.7mm-20-pieces) | |
| 24 | M3 screws, assorted | — | — | any | |
| 25 | Metal ball caster, 20 mm high, 40 mm hole spacing | 1 | 1.20 | [Bits & Parts](https://www.bitsandparts.nl/ball-caster-wheel-kogelwieltje-metaal-0-6inch-1-56cm-p1066176) | Or print one around a steel ball |
| 26 | Tyres: TPU filament or O-rings | — | — | any | Grip on the mat determines turn accuracy |
| 27 | Filament (PLA/PETG) for chassis and shell | ~150 g | ~4 | any | |
| 28 | Planet mat, vinyl print, 90 × 90 cm, 15 cm grid | 1 | 5–10 | local print shop | Artwork in `hardware/mat/` |

## Not included

- USB charger and **micro-USB cable**: include one with the toy.
- Gamepad for Pilot mode: any Bluepad32-supported pad (DualShock 4, DualSense,
  Switch Pro, 8BitDo, recent Xbox).
