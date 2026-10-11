/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Learning Laboratory
 * File: labs/native/interrupt-ownership/owner.c
 * PURPOSE: A small serial state machine; it never touches hardware or CSRs.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "owner.h"

/* This is one synchronous educational owner on one thread. No interrupts,
 * locks, atomics, hardware, DMA or real service privilege are modelled. */
static BtbIrqStatus LookUp(const BtbIrqDomain *domain, BtbIrqLease lease,
                            uint32_t *outIndex)
{
    if (domain == 0 || outIndex == 0) return BTB_IRQ_INVALID_ARGUMENT;
    if (domain->initialised != 1U || domain->self != domain)
        return BTB_IRQ_NOT_INITIALISED;
    if (lease.source == 0U || lease.source > BTB_IRQ_SOURCE_COUNT ||
        lease.owner == 0U || lease.generation == 0U) return BTB_IRQ_INVALID_ARGUMENT;
    const BtbIrqSource *source = &domain->sources[lease.source - 1U];
    if (source->stage == BTB_IRQ_FREE || source->generation != lease.generation)
        return BTB_IRQ_STALE_LEASE;
    if (source->owner != lease.owner) return BTB_IRQ_WRONG_OWNER;
    *outIndex = lease.source - 1U;
    return BTB_IRQ_OK;
}
BtbIrqStatus BtbIrqInitialize(BtbIrqDomain *domain)
{
    if (domain == 0) return BTB_IRQ_INVALID_ARGUMENT;
    if (domain->initialised != 0U) return BTB_IRQ_WRONG_STAGE;
    *domain = (BtbIrqDomain){.self = domain, .initialised = 1U};
    return BTB_IRQ_OK;
}
BtbIrqStatus BtbIrqClaim(BtbIrqDomain *domain, uint32_t sourceId,
                          uint32_t owner, uint32_t generation,
                          BtbIrqLease *outLease)
{
    if (domain == 0 || outLease == 0 || sourceId == 0U ||
        sourceId > BTB_IRQ_SOURCE_COUNT || owner == 0U || generation == 0U)
        return BTB_IRQ_INVALID_ARGUMENT;
    if (domain->initialised != 1U || domain->self != domain)
        return BTB_IRQ_NOT_INITIALISED;
    BtbIrqSource *source = &domain->sources[sourceId - 1U];
    if (source->stage != BTB_IRQ_FREE || generation <= source->lastGeneration)
        return BTB_IRQ_WRONG_STAGE;
    source->owner = owner;
    source->generation = generation;
    source->lastGeneration = generation;
    source->stage = BTB_IRQ_LEASED;
    *outLease = (BtbIrqLease){sourceId, owner, generation};
    return BTB_IRQ_OK;
}
static BtbIrqStatus Transition(BtbIrqDomain *domain, BtbIrqLease lease,
                               BtbIrqStage from, BtbIrqStage to)
{
    uint32_t index = 0U;
    BtbIrqStatus status = LookUp(domain, lease, &index);
    if (status != BTB_IRQ_OK) return status;
    BtbIrqSource *source = &domain->sources[index];
    if (source->stage != from) return BTB_IRQ_WRONG_STAGE;
    source->stage = to;
    return BTB_IRQ_OK;
}
BtbIrqStatus BtbIrqArm(BtbIrqDomain *d, BtbIrqLease lease)
{
    return Transition(d, lease, BTB_IRQ_LEASED, BTB_IRQ_ARMED);
}
BtbIrqStatus BtbIrqEnter(BtbIrqDomain *d, BtbIrqLease lease)
{
    return Transition(d, lease, BTB_IRQ_ARMED, BTB_IRQ_SERVICING);
}
BtbIrqStatus BtbIrqAcknowledge(BtbIrqDomain *d, BtbIrqLease lease)
{
    return Transition(d, lease, BTB_IRQ_SERVICING, BTB_IRQ_ACKED);
}
BtbIrqStatus BtbIrqReturn(BtbIrqDomain *d, BtbIrqLease lease)
{
    return Transition(d, lease, BTB_IRQ_ACKED, BTB_IRQ_LEASED);
}
BtbIrqStatus BtbIrqCancel(BtbIrqDomain *d, BtbIrqLease lease)
{
    return Transition(d, lease, BTB_IRQ_ARMED, BTB_IRQ_LEASED);
}
BtbIrqStatus BtbIrqFault(BtbIrqDomain *d, BtbIrqLease lease)
{
    uint32_t index = 0U;
    BtbIrqStatus status = LookUp(d, lease, &index);
    if (status != BTB_IRQ_OK) return status;
    BtbIrqSource *source = &d->sources[index];
    if (source->stage != BTB_IRQ_SERVICING && source->stage != BTB_IRQ_ACKED)
        return BTB_IRQ_WRONG_STAGE;
    source->stage = BTB_IRQ_FAULTED;
    return BTB_IRQ_OK;
}
BtbIrqStatus BtbIrqRecover(BtbIrqDomain *d, BtbIrqLease lease)
{
    return Transition(d, lease, BTB_IRQ_FAULTED, BTB_IRQ_LEASED);
}
BtbIrqStatus BtbIrqRelease(BtbIrqDomain *d, BtbIrqLease lease)
{
    uint32_t index = 0U;
    BtbIrqStatus status = LookUp(d, lease, &index);
    if (status != BTB_IRQ_OK) return status;
    BtbIrqSource *source = &d->sources[index];
    if (source->stage != BTB_IRQ_LEASED) return BTB_IRQ_WRONG_STAGE;
    source->stage = BTB_IRQ_FREE;
    source->owner = 0U;
    source->generation = 0U;
    return BTB_IRQ_OK;
}
BtbIrqStatus BtbIrqReadStage(const BtbIrqDomain *domain,
                              BtbIrqLease lease, BtbIrqStage *outStage)
{
    if (outStage == 0) return BTB_IRQ_INVALID_ARGUMENT;
    uint32_t index = 0U;
    BtbIrqStatus status = LookUp(domain, lease, &index);
    if (status == BTB_IRQ_OK) *outStage = domain->sources[index].stage;
    return status;
}
