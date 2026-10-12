/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/nonblocking_policy.h
 * PURPOSE: Deterministic C23 connection lifetime and deadline policy.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_NONBLOCKING_POLICY_H
#define BTB_NONBLOCKING_POLICY_H
#include <stdint.h>

/* A policy model independent of sockets and wall-clock time. It can be tested
 * with synthetic monotonic timestamps before it governs real descriptors. */
typedef enum BtbNbPhase {
    BTB_NB_FREE = 0,
    BTB_NB_READING,
    BTB_NB_WRITING,
    BTB_NB_COMPLETE,
    BTB_NB_FAILED
} BtbNbPhase;

typedef struct BtbNbLifetime {
    BtbNbPhase phase;
    uint64_t openedAtMs;
    uint64_t lastProgressMs;
} BtbNbLifetime;

/* Open only a zero-filled, free lifetime. Every accepted descriptor has its
 * own owner; previous timestamps must never carry into a reused slot. */
int BtbNbLifetimeOpen(BtbNbLifetime *lifetime, uint64_t nowMs);
/* Progress is permitted only within an active phase and at monotonic times. */
int BtbNbLifetimeAdvance(BtbNbLifetime *lifetime, BtbNbPhase nextPhase,
                         uint64_t nowMs);
/* Returns 1 on inactivity, total expiry, or regressed monotonic time. */
int BtbNbLifetimeExpired(const BtbNbLifetime *lifetime, uint64_t nowMs,
                         uint64_t idleMs, uint64_t totalMs);
/* Marks a terminal phase. Only the descriptor owner releases its resources. */
int BtbNbLifetimeFinish(BtbNbLifetime *lifetime, int success);
#endif
