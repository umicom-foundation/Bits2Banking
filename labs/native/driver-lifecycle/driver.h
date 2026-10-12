/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Learning Laboratory
 * File: labs/native/driver-lifecycle/driver.h
 * PURPOSE: Compose the earlier source-ownership and service-recovery models
 *          into an explicit fictional driver lifetime. No real I/O occurs.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_DRIVER_LIFECYCLE_H
#define BTB_DRIVER_LIFECYCLE_H
#include "recovery.h"
#include <stdint.h>

typedef enum BtbDriverStage {
    BTB_DRIVER_UNINITIALISED = 0,
    BTB_DRIVER_READY,
    BTB_DRIVER_FAULTED,
    BTB_DRIVER_STOPPED
} BtbDriverStage;

typedef struct BtbDriver {
    BtbService service;
    BtbDriverStage stage;
    uint32_t owner;
    uint32_t reviewedFaults;
} BtbDriver;

/* Start exactly once in zero-filled, address-stable memory; do not copy it. */
BtbIrqStatus BtbDriverStart(BtbDriver *driver, uint32_t owner);
/* Only strictly increasing fictional revisions can become accepted. */
BtbIrqStatus BtbDriverComplete(BtbDriver *driver, uint32_t revision);
/* A fault abandons the in-flight revision without increasing the committed one. */
BtbIrqStatus BtbDriverFail(BtbDriver *driver, uint32_t revision);
/* Explicit review is required before this teaching model may resume. */
BtbIrqStatus BtbDriverReviewAndRecover(BtbDriver *driver, uint32_t reviewedRevision);
/* Stop releases the owned interrupt source only from the READY state. */
BtbIrqStatus BtbDriverStop(BtbDriver *driver);
#endif
