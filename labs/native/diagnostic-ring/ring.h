/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Learning Laboratory
 * File: labs/native/diagnostic-ring/ring.h
 * PURPOSE: Store bounded copies of fictional device diagnostics in RAM.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_DIAGNOSTIC_RING_H
#define BTB_DIAGNOSTIC_RING_H
#include <stddef.h>
#include <stdint.h>
#define BTB_DIAGNOSTIC_RING_CAPACITY 8U
typedef enum BtbDiagnosticStatus {
    BTB_DIAGNOSTIC_OK = 0,
    BTB_DIAGNOSTIC_BAD_ARGUMENT,
    BTB_DIAGNOSTIC_BAD_STATE,
    BTB_DIAGNOSTIC_TIME_REVERSED,
    BTB_DIAGNOSTIC_SEQUENCE_EXHAUSTED
} BtbDiagnosticStatus;
typedef struct BtbDiagnostic {
    uint64_t sequence;
    uint64_t logicalTick;
    uint32_t source;
    uint32_t code;
} BtbDiagnostic;
typedef struct BtbDiagnosticRing {
    const struct BtbDiagnosticRing *self;
    uint64_t nextSequence;
    uint64_t lastTick;
    uint64_t dropped;
    size_t head;
    size_t count;
    BtbDiagnostic records[BTB_DIAGNOSTIC_RING_CAPACITY];
} BtbDiagnosticRing;
typedef struct BtbDiagnosticSnapshot {
    size_t count;
    uint64_t dropped;
    BtbDiagnostic records[BTB_DIAGNOSTIC_RING_CAPACITY];
} BtbDiagnosticSnapshot;

/* Initialise exactly once in zero-filled, address-stable caller storage. */
BtbDiagnosticStatus BtbDiagnosticRingInit(BtbDiagnosticRing *ring);
/* Bad input does not change the ring. When full, the oldest record is replaced.
 * This is intentionally a memory-only bounded cache, NOT durable evidence. */
BtbDiagnosticStatus BtbDiagnosticPush(BtbDiagnosticRing *ring, uint64_t tick,
                                       uint32_t source, uint32_t code);
/* Snapshot in chronological order; no internal pointers escape. */
BtbDiagnosticStatus BtbDiagnosticRead(const BtbDiagnosticRing *ring,
                                      BtbDiagnosticSnapshot *snapshot);
#endif
