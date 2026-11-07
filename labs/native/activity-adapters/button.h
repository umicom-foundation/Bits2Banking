/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/activity-adapters/button.h
 *
 * PURPOSE:
 *   Declare caller-owned button state for a small-device teaching model.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_ACTIVITY_BUTTON_H
#define BTB_ACTIVITY_BUTTON_H
#include <stdbool.h>
typedef struct {
    unsigned completed;
    bool was_pressed;
} BtbActivityButton;
/* Return true only when an accepted rising edge changes completed.
 * State must be initialized. No GPIO register or timer is accessed here. */
bool BtbActivityButtonSample(BtbActivityButton *state, bool pressed);
#endif

