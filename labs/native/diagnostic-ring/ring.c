/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Learning Laboratory
 * File: labs/native/diagnostic-ring/ring.c
 * PURPOSE: Bound diagnostic retention and make losses observable.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "ring.h"

static int Valid(const BtbDiagnosticRing *ring)
{
    return ring != NULL && ring->self == ring &&
           ring->count <= BTB_DIAGNOSTIC_RING_CAPACITY &&
           ring->head < BTB_DIAGNOSTIC_RING_CAPACITY;
}
BtbDiagnosticStatus BtbDiagnosticRingInit(BtbDiagnosticRing *ring)
{
    if (ring == NULL) return BTB_DIAGNOSTIC_BAD_ARGUMENT;
    if (ring->self != NULL) return BTB_DIAGNOSTIC_BAD_STATE;
    ring->nextSequence = 1U;
    ring->lastTick = 0U;
    ring->dropped = 0U;
    ring->head = 0U;
    ring->count = 0U;
    ring->self = ring;
    return BTB_DIAGNOSTIC_OK;
}
BtbDiagnosticStatus BtbDiagnosticPush(BtbDiagnosticRing *ring, uint64_t tick,
                                       uint32_t source, uint32_t code)
{
    if (ring == NULL || source == 0U || code == 0U)
        return BTB_DIAGNOSTIC_BAD_ARGUMENT;
    if (!Valid(ring)) return BTB_DIAGNOSTIC_BAD_STATE;
    if (tick < ring->lastTick) return BTB_DIAGNOSTIC_TIME_REVERSED;
    if (ring->nextSequence == 0U) return BTB_DIAGNOSTIC_SEQUENCE_EXHAUSTED;
    if (ring->count == BTB_DIAGNOSTIC_RING_CAPACITY && ring->dropped == UINT64_MAX)
        return BTB_DIAGNOSTIC_SEQUENCE_EXHAUSTED;
    const size_t offset = (ring->head + ring->count) % BTB_DIAGNOSTIC_RING_CAPACITY;
    if (ring->count == BTB_DIAGNOSTIC_RING_CAPACITY) {
        /* Replace oldest; next arrival must never make a lost row invisible. */
        ring->head = (ring->head + 1U) % BTB_DIAGNOSTIC_RING_CAPACITY;
        ++ring->dropped;
    } else {
        ++ring->count;
    }
    ring->records[offset] = (BtbDiagnostic){ring->nextSequence, tick, source, code};
    /* UINT64_MAX may be issued once. Zero thereafter means exhausted. */
    ring->nextSequence = ring->nextSequence == UINT64_MAX ? 0U : ring->nextSequence + 1U;
    ring->lastTick = tick;
    return BTB_DIAGNOSTIC_OK;
}
BtbDiagnosticStatus BtbDiagnosticRead(const BtbDiagnosticRing *ring,
                                      BtbDiagnosticSnapshot *snapshot)
{
    if (ring == NULL || snapshot == NULL) return BTB_DIAGNOSTIC_BAD_ARGUMENT;
    if (!Valid(ring)) return BTB_DIAGNOSTIC_BAD_STATE;
    BtbDiagnosticSnapshot next = {0};
    next.count = ring->count;
    next.dropped = ring->dropped;
    for (size_t i = 0U; i < ring->count; ++i)
        next.records[i] = ring->records[(ring->head + i) % BTB_DIAGNOSTIC_RING_CAPACITY];
    *snapshot = next;
    return BTB_DIAGNOSTIC_OK;
}
