/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Service-Recovery Laboratory
 * File: labs/native/service-recovery/recovery.c
 * PURPOSE: Preserve accepted work on fault, refuse abandoned in-flight work.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "recovery.h"

BtbIrqStatus BtbServiceStart(BtbService *service, uint32_t owner)
{
    if (service == 0 || owner == 0U) return BTB_IRQ_INVALID_ARGUMENT;
    if (service->started != 0U || service->stopped != 0U) return BTB_IRQ_WRONG_STAGE;
    BtbIrqStatus status = BtbIrqInitialize(&service->sourceDomain);
    if (status != BTB_IRQ_OK) return status;
    status = BtbIrqClaim(&service->sourceDomain, 1U, owner, 1U, &service->lease);
    if (status != BTB_IRQ_OK) return status;
    status = BtbIrqArm(&service->sourceDomain, service->lease);
    if (status == BTB_IRQ_OK) service->started = 1U;
    return status;
}
BtbIrqStatus BtbServiceBegin(BtbService *service, uint32_t revision)
{
    if (service == 0 || revision == 0U) return BTB_IRQ_INVALID_ARGUMENT;
    if (service->started == 0U || service->stopped != 0U ||
        service->inFlight != 0U || revision <= service->committed)
        return BTB_IRQ_WRONG_STAGE;
    const BtbIrqStatus status = BtbIrqEnter(&service->sourceDomain, service->lease);
    if (status == BTB_IRQ_OK) service->inFlight = revision;
    return status;
}
BtbIrqStatus BtbServiceCommit(BtbService *service)
{
    if (service == 0) return BTB_IRQ_INVALID_ARGUMENT;
    if (service->started == 0U || service->stopped != 0U || service->inFlight == 0U)
        return BTB_IRQ_WRONG_STAGE;
    BtbIrqStatus status = BtbIrqAcknowledge(&service->sourceDomain, service->lease);
    if (status != BTB_IRQ_OK) return status;
    status = BtbIrqReturn(&service->sourceDomain, service->lease);
    if (status != BTB_IRQ_OK) return status;
    /* Publish the checked local result only after successful completion;
     * acceptance is not the same thing as durable filesystem persistence. */
    service->committed = service->inFlight;
    service->inFlight = 0U;
    return BtbIrqArm(&service->sourceDomain, service->lease);
}
BtbIrqStatus BtbServiceFault(BtbService *service)
{
    if (service == 0) return BTB_IRQ_INVALID_ARGUMENT;
    if (service->started == 0U || service->stopped != 0U || service->inFlight == 0U)
        return BTB_IRQ_WRONG_STAGE;
    return BtbIrqFault(&service->sourceDomain, service->lease);
}
BtbIrqStatus BtbServiceRecover(BtbService *service)
{
    if (service == 0) return BTB_IRQ_INVALID_ARGUMENT;
    if (service->started == 0U || service->stopped != 0U || service->inFlight == 0U)
        return BTB_IRQ_WRONG_STAGE;
    BtbIrqStatus status = BtbIrqRecover(&service->sourceDomain, service->lease);
    if (status != BTB_IRQ_OK) return status;
    /* The failed revision was never acknowledged. Do not claim it committed.
     * A deliberate new Begin call may retry that revision after review. */
    service->inFlight = 0U;
    return BtbIrqArm(&service->sourceDomain, service->lease);
}
BtbIrqStatus BtbServiceStop(BtbService *service)
{
    if (service == 0) return BTB_IRQ_INVALID_ARGUMENT;
    if (service->started == 0U || service->stopped != 0U || service->inFlight != 0U)
        return BTB_IRQ_WRONG_STAGE;
    BtbIrqStatus status = BtbIrqCancel(&service->sourceDomain, service->lease);
    if (status != BTB_IRQ_OK) return status;
    status = BtbIrqRelease(&service->sourceDomain, service->lease);
    if (status == BTB_IRQ_OK) service->stopped = 1U;
    return status;
}
