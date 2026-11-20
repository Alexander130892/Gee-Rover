/** @file main.c
 *
 * @brief Gee-Rover application entry point.
 *
 * Current stage: bring-up test T05 (docs/test-plan.md). Forces all motor
 * coils off, logs the reset reason once, then a counter once per second.
 *
 * @par
 * Copyright (c) 2026 Alexander Vindelinckx. MIT License.
 */

#include <stdint.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"

#include "board_pins.h"

static const char * const g_tag = "gee-rover";

/*!
 * @brief Drive every motor coil pin low.
 *
 * Runs first in app_main so the steppers are de-energised as early as
 * possible after reset (docs/pinout.md, firmware rules).
 */
static void
coils_force_off (void)
{
    gpio_config_t const cfg =
    {
        .pin_bit_mask = (uint64_t) BOARD_MASK_COILS,
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };

    /* Set the output latch low before enabling the output driver. */
    for (uint32_t pin = 0U; pin < 32U; pin++)
    {
        if (0U != (BOARD_MASK_COILS & (1UL << pin)))
        {
            (void) gpio_set_level((gpio_num_t) pin, 0U);
        }
    }

    ESP_ERROR_CHECK(gpio_config(&cfg));
}

/*!
 * @brief Human-readable name of a reset reason.
 */
static char const *
reset_reason_str (esp_reset_reason_t reason)
{
    switch (reason)
    {
        case ESP_RST_POWERON:   return "POWERON (power applied)";
        case ESP_RST_BROWNOUT:  return "BROWNOUT (supply dipped)";
        case ESP_RST_SW:        return "SW (esp_restart)";
        case ESP_RST_PANIC:     return "PANIC (exception)";
        case ESP_RST_INT_WDT:   return "INT_WDT";
        case ESP_RST_TASK_WDT:  return "TASK_WDT";
        case ESP_RST_WDT:       return "WDT (other)";
        case ESP_RST_DEEPSLEEP: return "DEEPSLEEP";
        case ESP_RST_EXT:       return "EXT (reset pin)";
        case ESP_RST_SDIO:      return "SDIO";
        default:                return "UNKNOWN";
    }
}

void
app_main (void)
{
    coils_force_off();

    esp_reset_reason_t const reason = esp_reset_reason();
    ESP_LOGI(g_tag, "boot, reset reason: %s", reset_reason_str(reason));

    uint32_t counter = 0U;

    for (;;)
    {
        ESP_LOGI(g_tag, "alive %" PRIu32, counter);
        counter++;
        vTaskDelay(pdMS_TO_TICKS(1000U));
    }
}

/*** end of file ***/
