/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/activity-adapters/button.c
 *
 * PURPOSE:
 *   Adapt sampled button edges to the single shared activity rule.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "button.h"
#include "../framework-activity/activity.h"
bool BtbActivityButtonSample(BtbActivityButton *state, bool pressed)
{
    if (state == 0) return false;
    bool rising = pressed && !state->was_pressed;
    state->was_pressed = pressed;
    /* Input sampling owns edge detection; the existing application model owns
     * count validation. A rejected update leaves the completed value intact. */
    return rising && BtbActivityAdvance(state->completed, &state->completed) == UMI_STATUS_OK;
}

