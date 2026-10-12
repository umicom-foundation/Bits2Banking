/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/test_nonblocking.c
 * PURPOSE: C23 deterministic deadline, transition and adversarial tests.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "nonblocking_policy.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "%s:%d: failed: %s\n", __FILE__, __LINE__, #condition); \
    return 1; \
} } while (0)

static int BtbTestPolicy(void)
{
    BtbNbLifetime lifetime = {0};
    CHECK(BtbNbLifetimeOpen(&lifetime, 100U));
    CHECK(!BtbNbLifetimeOpen(&lifetime, 200U));
    CHECK(lifetime.phase == BTB_NB_READING);
    CHECK(!BtbNbLifetimeExpired(&lifetime, 3099U, 3000U, 10000U));
    CHECK(BtbNbLifetimeExpired(&lifetime, 3100U, 3000U, 10000U));
    CHECK(!BtbNbLifetimeAdvance(&lifetime, BTB_NB_FREE, 300U));
    CHECK(!BtbNbLifetimeAdvance(&lifetime, BTB_NB_READING, 99U));
    CHECK(BtbNbLifetimeAdvance(&lifetime, BTB_NB_READING, 2000U));
    CHECK(!BtbNbLifetimeExpired(&lifetime, 4999U, 3000U, 10000U));
    CHECK(BtbNbLifetimeExpired(&lifetime, 5000U, 3000U, 10000U));
    CHECK(BtbNbLifetimeAdvance(&lifetime, BTB_NB_WRITING, 9000U));
    CHECK(!BtbNbLifetimeAdvance(&lifetime, BTB_NB_READING, 9001U));
    CHECK(!BtbNbLifetimeExpired(&lifetime, 10099U, 3000U, 10000U));
    CHECK(BtbNbLifetimeExpired(&lifetime, 10100U, 3000U, 10000U));
    CHECK(BtbNbLifetimeExpired(&lifetime, 1U, 3000U, 10000U));
    CHECK(BtbNbLifetimeExpired(&lifetime, 9000U, 0U, 10000U));
    CHECK(BtbNbLifetimeExpired(&lifetime, 9000U, 3000U, 0U));
    CHECK(BtbNbLifetimeFinish(&lifetime, 1));
    CHECK(lifetime.phase == BTB_NB_COMPLETE);
    CHECK(!BtbNbLifetimeFinish(&lifetime, 0));
    CHECK(!BtbNbLifetimeAdvance(&lifetime, BTB_NB_WRITING, 11000U));
    CHECK(!BtbNbLifetimeExpired(&lifetime, 11000U, 3000U, 10000U));
    (void)memset(&lifetime, 0, sizeof lifetime);
    CHECK(BtbNbLifetimeOpen(&lifetime, UINT64_MAX - 20U));
    CHECK(!BtbNbLifetimeExpired(&lifetime, UINT64_MAX, 21U, 21U));
    CHECK(BtbNbLifetimeExpired(&lifetime, UINT64_MAX, 20U, 21U));
    CHECK(BtbNbLifetimeExpired(&lifetime, 1U, 20U, 21U));
    CHECK(BtbNbLifetimeFinish(&lifetime, 0));
    CHECK(lifetime.phase == BTB_NB_FAILED);
    CHECK(!BtbNbLifetimeOpen(NULL, 100U));
    CHECK(!BtbNbLifetimeAdvance(NULL, BTB_NB_WRITING, 100U));
    CHECK(BtbNbLifetimeExpired(NULL, 100U, 100U, 100U));
    CHECK(!BtbNbLifetimeFinish(NULL, 1));
    return 0;
}

static int BtbTestMutations(void)
{
    uint32_t seed = UINT32_C(0x42e1c0de);
    unsigned active = 0U;
    for (unsigned i = 0U; i < 30000U; ++i) {
        seed = seed * UINT32_C(1664525) + UINT32_C(1013904223);
        BtbNbLifetime lifetime = {0};
        const uint64_t started = (uint64_t)(seed >> 4U);
        CHECK(BtbNbLifetimeOpen(&lifetime, started));
        CHECK(!BtbNbLifetimeOpen(&lifetime, started + 1U));
        const uint64_t progressed = started + (uint64_t)(seed % 900U);
        const BtbNbPhase phase = (seed & 1U) != 0U ?
            BTB_NB_READING : BTB_NB_WRITING;
        CHECK(BtbNbLifetimeAdvance(&lifetime, phase, progressed));
        CHECK(!BtbNbLifetimeExpired(&lifetime, progressed + 100U,
                                    500U, 2000U));
        CHECK(BtbNbLifetimeExpired(&lifetime, progressed + 500U,
                                   500U, 2000U));
        CHECK(!BtbNbLifetimeAdvance(&lifetime, BTB_NB_FREE, progressed));
        CHECK(BtbNbLifetimeFinish(&lifetime, (seed & 2U) != 0U));
        CHECK(!BtbNbLifetimeAdvance(&lifetime, BTB_NB_WRITING,
                                     progressed + 200U));
        ++active;
    }
    CHECK(active == 30000U);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (strcmp(argv[1], "policy") == 0) return BtbTestPolicy();
    if (strcmp(argv[1], "mutations") == 0) return BtbTestMutations();
    return 2;
}
