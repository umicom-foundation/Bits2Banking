/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/activity-adapters/bridge.c
 *
 * PURPOSE:
 *   Translate platform integers into the existing activity contract.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "bridge.h"
#include "../framework-activity/activity.h"
int BtbActivityNext(int current)
{
    unsigned next = 0U;
    /* Check the signed boundary before converting. The shared activity model
     * remains responsible for its upper limit and success/failure decision. */
    if (current < 0) return -1;
    if (BtbActivityAdvance((unsigned)current, &next) != UMI_STATUS_OK) return -1;
    return (int)next; /* The activity contract bounds successful values to 1000. */
}

