/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/nonblocking_policy.c
 * PURPOSE: No-socket, deterministic connection and timeout state machine.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "nonblocking_policy.h"
#include <stddef.h>

int BtbNbLifetimeOpen(BtbNbLifetime *lifetime, uint64_t nowMs)
{
    if (lifetime == NULL || lifetime->phase != BTB_NB_FREE) return 0;
    lifetime->openedAtMs = nowMs;
    lifetime->lastProgressMs = nowMs;
    lifetime->phase = BTB_NB_READING;
    return 1;
}

int BtbNbLifetimeAdvance(BtbNbLifetime *lifetime, BtbNbPhase nextPhase,
                         uint64_t nowMs)
{
    if (lifetime == NULL ||
        (lifetime->phase != BTB_NB_READING && lifetime->phase != BTB_NB_WRITING) ||
        (nextPhase != BTB_NB_READING && nextPhase != BTB_NB_WRITING) ||
        (lifetime->phase == BTB_NB_WRITING && nextPhase == BTB_NB_READING) ||
        nowMs < lifetime->lastProgressMs) return 0;
    lifetime->phase = nextPhase;
    lifetime->lastProgressMs = nowMs;
    return 1;
}

int BtbNbLifetimeExpired(const BtbNbLifetime *lifetime, uint64_t nowMs,
                         uint64_t idleMs, uint64_t totalMs)
{
    if (lifetime == NULL || idleMs == 0U || totalMs == 0U) return 1;
    if (lifetime->phase != BTB_NB_READING && lifetime->phase != BTB_NB_WRITING)
        return 0;
    /* Subtraction after ordering checks avoids overflow when the process has
     * been up for a very long time. Exact boundaries are expired. */
    if (nowMs < lifetime->openedAtMs || nowMs < lifetime->lastProgressMs)
        return 1;
    return (nowMs - lifetime->openedAtMs >= totalMs ||
            nowMs - lifetime->lastProgressMs >= idleMs);
}

int BtbNbLifetimeFinish(BtbNbLifetime *lifetime, int success)
{
    if (lifetime == NULL ||
        (lifetime->phase != BTB_NB_READING && lifetime->phase != BTB_NB_WRITING))
        return 0;
    lifetime->phase = success != 0 ? BTB_NB_COMPLETE : BTB_NB_FAILED;
    return 1;
}
