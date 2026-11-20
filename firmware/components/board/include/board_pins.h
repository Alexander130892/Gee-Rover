/** @file board_pins.h
 *
 * @brief GPIO assignment for the Gee-Rover.
 *
 * Single source of truth for pin numbers in firmware. Must match
 * docs/pinout.md and ADR-0010.
 *
 * @par
 * Copyright (c) 2026 Alexander Vindelinckx. MIT License.
 */

#ifndef BOARD_PINS_H
#define BOARD_PINS_H

#include <stdint.h>

/* Motors: all coil pins < 32 so both motors update with one register write. */
#define BOARD_PIN_MOTOR_L_IN1   (25U)
#define BOARD_PIN_MOTOR_L_IN2   (26U)
#define BOARD_PIN_MOTOR_L_IN3   (27U)
#define BOARD_PIN_MOTOR_L_IN4   (14U)

#define BOARD_PIN_MOTOR_R_IN1   (23U)
#define BOARD_PIN_MOTOR_R_IN2   (22U)
#define BOARD_PIN_MOTOR_R_IN3   (21U)
#define BOARD_PIN_MOTOR_R_IN4   (19U)

#define BOARD_MASK_MOTOR_L      ((1UL << BOARD_PIN_MOTOR_L_IN1) | \
                                 (1UL << BOARD_PIN_MOTOR_L_IN2) | \
                                 (1UL << BOARD_PIN_MOTOR_L_IN3) | \
                                 (1UL << BOARD_PIN_MOTOR_L_IN4))

#define BOARD_MASK_MOTOR_R      ((1UL << BOARD_PIN_MOTOR_R_IN1) | \
                                 (1UL << BOARD_PIN_MOTOR_R_IN2) | \
                                 (1UL << BOARD_PIN_MOTOR_R_IN3) | \
                                 (1UL << BOARD_PIN_MOTOR_R_IN4))

#define BOARD_MASK_COILS        (BOARD_MASK_MOTOR_L | BOARD_MASK_MOTOR_R)

/* Buttons: active low. 32/33/13 use internal pull-ups; 34/35/36 have
 * external 10 kOhm pull-ups (input-only pins). Read by polled debounce only
 * (ESP32 errata 3.11 on GPIO 36/39). */
#define BOARD_PIN_BTN_CLEAR     (32U)
#define BOARD_PIN_BTN_GO        (33U)
#define BOARD_PIN_BTN_RIGHT     (13U)
#define BOARD_PIN_BTN_FWD       (34U)
#define BOARD_PIN_BTN_BACK      (35U)
#define BOARD_PIN_BTN_LEFT      (36U)

/* Battery divider 100k/100k on ADC1 channel 3. */
#define BOARD_PIN_BATTERY       (39U)

/* Feedback. */
#define BOARD_PIN_BUZZER        (18U)   /* LEDC PWM -> SS8050 driver   */
#define BOARD_PIN_WS2812        (4U)    /* RMT -> 74AHCT125 -> eyes    */

/* Reserved for Defend mode (not populated): 2 servo, 5 IR receiver, 15 IR LED. */

#endif /* BOARD_PINS_H */

/*** end of file ***/
