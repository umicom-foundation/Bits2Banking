/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/framework-activity/activity.c
 *
 * PURPOSE:
 *   Keep checked exercise-count logic independent of its console and GTK presentations.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "activity.h"
UmiStatus BtbActivityAdvance(unsigned current, unsigned *next)
{
    if (next == 0 || current > 1000U) return UMI_STATUS_INVALID_ARGUMENT;
    if (current == 1000U) return UMI_STATUS_CAPACITY_EXCEEDED;
    /* Validate before addition and publication. No caller observes a partial
     * update, and the fixed upper bound proves the addition cannot overflow. */
    *next = current + 1U;
    return UMI_STATUS_OK;
}
