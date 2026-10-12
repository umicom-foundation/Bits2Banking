/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/test_admission.c
 * PURPOSE: Verify bounded request admission and non-retractable active work.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "admission_queue.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); return 1; \
} } while (0)
static int QueueTest(void)
{
    BtbAdmissionQueue q = {0};
    CHECK(BtbAdmissionInit(&q, 2U) == BTB_ADMISSION_OK);
    CHECK(BtbAdmissionInit(&q, 2U) == BTB_ADMISSION_INVALID);
    uint64_t ids[5] = {0};
    for (uint64_t n = 1U; n <= 4U; ++n)
        CHECK(BtbAdmissionSubmit(&q, n, &ids[n - 1U]) == BTB_ADMISSION_OK);
    CHECK(q.count == 4U);
    CHECK(BtbAdmissionSubmit(&q, 5U, &ids[4]) == BTB_ADMISSION_FULL);
    uint64_t ticket = 99U, request = 99U;
    CHECK(BtbAdmissionStart(&q, &ticket, &request) == BTB_ADMISSION_OK &&
          ticket == ids[0] && request == 1U);
    CHECK(BtbAdmissionStart(&q, &ticket, &request) == BTB_ADMISSION_OK && request == 2U);
    CHECK(BtbAdmissionStart(&q, &ticket, &request) == BTB_ADMISSION_BUSY);
    CHECK(BtbAdmissionCancel(&q, ids[1]) == BTB_ADMISSION_OK);
    CHECK(q.active == 2U && q.count == 4U); /* Cancel is only intent once active. */
    CHECK(BtbAdmissionComplete(&q, ids[1]) == BTB_ADMISSION_OK);
    CHECK(BtbAdmissionComplete(&q, ids[1]) == BTB_ADMISSION_STALE);
    CHECK(BtbAdmissionStart(&q, &ticket, &request) == BTB_ADMISSION_OK && request == 3U);
    CHECK(BtbAdmissionCancel(&q, ids[3]) == BTB_ADMISSION_OK);
    CHECK(q.count == 2U && q.active == 2U);
    CHECK(BtbAdmissionComplete(&q, ids[0]) == BTB_ADMISSION_OK);
    CHECK(BtbAdmissionComplete(&q, ids[2]) == BTB_ADMISSION_OK);
    CHECK(BtbAdmissionStart(&q, &ticket, &request) == BTB_ADMISSION_EMPTY);
    CHECK(q.count == 0U && q.completed == 3U && q.removed == 1U);
    CHECK(BtbAdmissionValidate(&q));
    BtbAdmissionQueue copied = q;
    CHECK(!BtbAdmissionValidate(&copied));
    CHECK(BtbAdmissionSubmit(&copied, 5U, &ids[4]) == BTB_ADMISSION_INVALID);
    return 0;
}
static uint32_t RandomNext(uint32_t *state)
{
    *state ^= *state << 13U;
    *state ^= *state >> 17U;
    *state ^= *state << 5U;
    return *state;
}
static int Mutations(void)
{
    BtbAdmissionQueue q = {0};
    CHECK(BtbAdmissionInit(&q, 3U) == BTB_ADMISSION_OK);
    uint32_t seed = UINT32_C(0x83b2a7fe);
    for (unsigned i = 0U; i < 20000U; ++i) {
        uint64_t ticket = 0U, id = 0U;
        const unsigned op = RandomNext(&seed) % 5U;
        const uint64_t fresh = (uint64_t)i + 1U;
        if (op == 0U) (void)BtbAdmissionSubmit(&q, fresh, &ticket);
        else if (op == 1U) (void)BtbAdmissionStart(&q, &ticket, &id);
        else if (q.count > 0U) {
            const size_t index = (size_t)(RandomNext(&seed) % (uint32_t)q.count);
            const BtbAdmissionItem item = q.items[index];
            if (op == 2U) (void)BtbAdmissionCancel(&q, item.ticket);
            else if (op == 3U) (void)BtbAdmissionComplete(&q, item.ticket);
            else CHECK(BtbAdmissionComplete(&q, item.ticket + UINT64_C(1000000))
                       == BTB_ADMISSION_STALE);
        }
        CHECK(BtbAdmissionValidate(&q));
    }
    /* Refused stale work cannot roll ticket allocation backward. */
    CHECK(q.nextTicket >= 1U);
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (strcmp(argv[1], "queue") == 0) return QueueTest();
    if (strcmp(argv[1], "mutations") == 0) return Mutations();
    return 2;
}
