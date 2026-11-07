/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/microdevices/pico-activity/main.c
 *
 * PURPOSE:
 *   Read a Pico button and present the shared C activity model on the board LED.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "pico/stdlib.h"
#include "../../native/activity-adapters/button.h"

#if !defined(PICO_DEFAULT_LED_PIN) || defined(CYW43_WL_GPIO_LED_PIN)
#error "This lesson requires the non-wireless Pico GPIO LED board configuration"
#endif

enum { LESSON_BUTTON_GPIO = 15 };

int main(void)
{
    BtbActivityButton activity = {0};
    gpio_init(LESSON_BUTTON_GPIO);
    gpio_set_dir(LESSON_BUTTON_GPIO, GPIO_IN);
    gpio_pull_up(LESSON_BUTTON_GPIO);
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, false);

    for (;;) {
        /* The board adapter translates the active-low input. The existing
         * adapter detects sampled edges and the shared C model bounds the
         * count. No desktop SDK binary is linked into this firmware. */
        const bool pressed = !gpio_get(LESSON_BUTTON_GPIO);
        if (BtbActivityButtonSample(&activity, pressed)) {
            gpio_put(PICO_DEFAULT_LED_PIN, (activity.completed & 1U) != 0U);
        }
        /* Sampling is deliberately visible. Mechanical bounce can produce
         * more than one accepted edge; this is not a debouncing algorithm. */
        sleep_ms(10);
    }
}

