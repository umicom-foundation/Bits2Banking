/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Learning Laboratory
 * File: labs/native/driver-lifecycle/driver.c
 * PURPOSE: Reuse existing Umicom teaching lifecycle contracts without another
 *          interrupt controller, message queue, or driver implementation.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "driver.h"
#include <stddef.h>

BtbIrqStatus BtbDriverStart(BtbDriver *driver, uint32_t owner)
{
    if (driver == NULL || owner == 0U) return BTB_IRQ_INVALID_ARGUMENT;
    if (driver->stage != BTB_DRIVER_UNINITIALISED) return BTB_IRQ_WRONG_STAGE;
    const BtbIrqStatus status = BtbServiceStart(&driver->service, owner);
    if (status != BTB_IRQ_OK) return status;
    driver->owner = owner;
    driver->stage = BTB_DRIVER_READY;
    return BTB_IRQ_OK;
}
BtbIrqStatus BtbDriverComplete(BtbDriver *driver, uint32_t revision)
{
    if (driver == NULL || revision == 0U) return BTB_IRQ_INVALID_ARGUMENT;
    if (driver->stage != BTB_DRIVER_READY) return BTB_IRQ_WRONG_STAGE;
    BtbIrqStatus status = BtbServiceBegin(&driver->service, revision);
    if (status != BTB_IRQ_OK) return status;
    return BtbServiceCommit(&driver->service);
}
BtbIrqStatus BtbDriverFail(BtbDriver *driver, uint32_t revision)
{
    if (driver == NULL || revision == 0U) return BTB_IRQ_INVALID_ARGUMENT;
    if (driver->stage != BTB_DRIVER_READY) return BTB_IRQ_WRONG_STAGE;
    BtbIrqStatus status = BtbServiceBegin(&driver->service, revision);
    if (status != BTB_IRQ_OK) return status;
    status = BtbServiceFault(&driver->service);
    if (status == BTB_IRQ_OK) driver->stage = BTB_DRIVER_FAULTED;
    return status;
}
BtbIrqStatus BtbDriverReviewAndRecover(BtbDriver *driver, uint32_t reviewedRevision)
{
    if (driver == NULL || reviewedRevision == 0U) return BTB_IRQ_INVALID_ARGUMENT;
    if (driver->stage != BTB_DRIVER_FAULTED ||
        reviewedRevision != driver->service.inFlight)
        return BTB_IRQ_WRONG_STAGE;
    if (driver->reviewedFaults == UINT32_MAX) return BTB_IRQ_WRONG_STAGE;
    const BtbIrqStatus status = BtbServiceRecover(&driver->service);
    if (status == BTB_IRQ_OK) {
        driver->stage = BTB_DRIVER_READY;
        ++driver->reviewedFaults;
    }
    return status;
}
BtbIrqStatus BtbDriverStop(BtbDriver *driver)
{
    if (driver == NULL) return BTB_IRQ_INVALID_ARGUMENT;
    if (driver->stage != BTB_DRIVER_READY) return BTB_IRQ_WRONG_STAGE;
    const BtbIrqStatus status = BtbServiceStop(&driver->service);
    if (status == BTB_IRQ_OK) driver->stage = BTB_DRIVER_STOPPED;
    return status;
}
