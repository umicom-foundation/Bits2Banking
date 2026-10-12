/* Bits2Banking | Umicom Foundation | bounded diagnostic ring regression test | MIT */
#include "ring.h"
#include <stdio.h>
#include <string.h>
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr,"Failed at line %d: %s\n",__LINE__,#condition); return 1; \
} } while (0)
int main(void)
{
    BtbDiagnosticRing ring = {0};
    BtbDiagnosticSnapshot view = {0};
    CHECK(BtbDiagnosticRingInit(&ring) == BTB_DIAGNOSTIC_OK);
    CHECK(BtbDiagnosticRingInit(&ring) == BTB_DIAGNOSTIC_BAD_STATE);
    CHECK(BtbDiagnosticPush(&ring, 5U, 1U, 4U) == BTB_DIAGNOSTIC_OK);
    CHECK(BtbDiagnosticPush(&ring, 4U, 1U, 4U) == BTB_DIAGNOSTIC_TIME_REVERSED);
    CHECK(BtbDiagnosticPush(&ring, 5U, 1U, 0U) == BTB_DIAGNOSTIC_BAD_ARGUMENT);
    for (uint64_t t = 6U; t <= 17U; ++t)
        CHECK(BtbDiagnosticPush(&ring, t, 1U, 40U) == BTB_DIAGNOSTIC_OK);
    CHECK(BtbDiagnosticRead(&ring, &view) == BTB_DIAGNOSTIC_OK);
    CHECK(view.count == 8U && view.dropped == 5U);
    CHECK(view.records[0].sequence == 6U && view.records[7].sequence == 13U);
    CHECK(view.records[7].logicalTick == 17U);
    BtbDiagnosticRing invalidCopy = ring;
    BtbDiagnosticSnapshot unchanged;
    memset(&unchanged, 0xa5, sizeof(unchanged));
    BtbDiagnosticSnapshot old = unchanged;
    CHECK(BtbDiagnosticRead(&invalidCopy, &unchanged) == BTB_DIAGNOSTIC_BAD_STATE);
    CHECK(memcmp(&unchanged, &old, sizeof(old)) == 0);
    ring.nextSequence = UINT64_MAX;
    CHECK(BtbDiagnosticPush(&ring, 18U, 1U, 40U) == BTB_DIAGNOSTIC_OK);
    CHECK(BtbDiagnosticPush(&ring, 19U, 1U, 40U) == BTB_DIAGNOSTIC_SEQUENCE_EXHAUSTED);
    CHECK(BtbDiagnosticRead(&ring, &view) == BTB_DIAGNOSTIC_OK);
    CHECK(view.records[7].sequence == UINT64_MAX);
    puts("Diagnostic ring: bounded copies, loss accounting, and refusal invariants checked.");
    return 0;
}
