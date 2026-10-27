/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/framework-activity/activity.h
 *
 * PURPOSE:
 *   Declare a small application contract using Framework status values.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_FRAMEWORK_ACTIVITY_H
#define BTB_FRAMEWORK_ACTIVITY_H
#include "umicom/base/status.h"
/* Count completed exercises, up to 1000. On any failure, leave next unchanged.
 * The caller owns next; this function does not retain its address. */
UmiStatus BtbActivityAdvance(unsigned current, unsigned *next);
#endif
