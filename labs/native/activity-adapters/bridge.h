/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/activity-adapters/bridge.h
 *
 * PURPOSE:
 *   Expose a fixed integer boundary for teaching platform adapters.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_ACTIVITY_BRIDGE_H
#define BTB_ACTIVITY_BRIDGE_H
#ifdef __cplusplus
extern "C" {
#endif
/* A nonnegative result is the new count; -1 means rejected input or a full
 * activity. This small teaching boundary never retains caller storage. */
int BtbActivityNext(int current);
#ifdef __cplusplus
}
#endif
#endif

