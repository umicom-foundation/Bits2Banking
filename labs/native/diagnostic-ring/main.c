/* Bits2Banking | Umicom Foundation | C23 bounded diagnostics demonstration | MIT */
#include "ring.h"
#include <stdio.h>
int main(void)
{
    BtbDiagnosticRing ring = {0};
    BtbDiagnosticSnapshot view = {0};
    if (BtbDiagnosticRingInit(&ring) != BTB_DIAGNOSTIC_OK) return 1;
    for (uint64_t tick = 1U; tick <= 10U; ++tick)
        if (BtbDiagnosticPush(&ring, tick, 2U, 200U) != BTB_DIAGNOSTIC_OK)
            return 1;
    if (BtbDiagnosticRead(&ring, &view) != BTB_DIAGNOSTIC_OK) return 1;
    printf("Retained rows: %zu. Overwritten rows: %llu. First sequence: %llu.\n",
           view.count, (unsigned long long)view.dropped,
           (unsigned long long)view.records[0].sequence);
    return 0;
}
