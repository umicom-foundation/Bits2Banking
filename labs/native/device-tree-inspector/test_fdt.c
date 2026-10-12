/*-----------------------------------------------------------------------------
 * Bits2Banking — Device Tree Inspector
 * File: labs/native/device-tree-inspector/test_fdt.c
 * PURPOSE: Validate the FDT reader and refusal without output mutation.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "fdt.h"
#include "fixture.h"
#include <stdio.h>
#include <string.h>

#define CHECK(cond) do { if (!(cond)) { \
    fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); return 1; \
} } while (0)

static int InspectErrors(void)
{
    unsigned char original[512];
    unsigned char mutated[512];
    const size_t size = BtbFdtMakeFixture(original, sizeof(original));
    CHECK(size > 0U);
    BtbFdtSummary expected = {0};
    CHECK(BtbFdtInspect(original, size, &expected) == BTB_FDT_OK);
    CHECK(expected.nodeCount == 2U && expected.propertyCount == 4U);
    CHECK(expected.virtioMmioCount == 1U);
    CHECK(expected.proposedMmioBase == UINT64_C(0x10001000));
    CHECK(expected.proposedMmioBytes == 4096U);
    CHECK(BtbFdtInspect(NULL, size, &expected) == BTB_FDT_INVALID_ARGUMENT);
    CHECK(BtbFdtInspect(original, size, NULL) == BTB_FDT_INVALID_ARGUMENT);
    CHECK(BtbFdtInspect(original, 12U, &expected) == BTB_FDT_TRUNCATED);
    CHECK(BtbFdtInspect(original, size - 1U, &expected) == BTB_FDT_TRUNCATED);
    memcpy(mutated, original, size);
    mutated[0] ^= 0x1U;
    CHECK(BtbFdtInspect(mutated, size, &expected) == BTB_FDT_MALFORMED);
    memcpy(mutated, original, size);
    BtbFdtWriteBe32(mutated + 12U, 0xfffffffcU);
    CHECK(BtbFdtInspect(mutated, size, &expected) == BTB_FDT_MALFORMED);
    memcpy(mutated, original, size);
    BtbFdtWriteBe32(mutated + 20U, 16U);
    CHECK(BtbFdtInspect(mutated, size, &expected) == BTB_FDT_UNSUPPORTED);
    memcpy(mutated, original, size);
    BtbFdtWriteBe32(mutated + 32U, 0U);
    CHECK(BtbFdtInspect(mutated, size, &expected) == BTB_FDT_MALFORMED);
    memcpy(mutated, original, size);
    BtbFdtWriteBe32(mutated + 16U, 56U);
    CHECK(BtbFdtInspect(mutated, size, &expected) == BTB_FDT_MALFORMED);
    /* A denied parse must not publish partly decoded data. */
    BtbFdtSummary sentinel = expected;
    uint32_t seed = UINT32_C(0x9e3779b9);
    for (unsigned iteration = 0U; iteration < 10000U; ++iteration) {
        memcpy(mutated, original, size);
        seed ^= seed << 13U;
        seed ^= seed >> 17U;
        seed ^= seed << 5U;
        const size_t position = (size_t)(seed % (uint32_t)size);
        mutated[position] = (unsigned char)(mutated[position] ^ (unsigned char)((seed >> 16U) | 1U));
        BtbFdtSummary out = sentinel;
        BtbFdtStatus result = BtbFdtInspect(mutated, size, &out);
        if (result != BTB_FDT_OK) CHECK(memcmp(&out, &sentinel, sizeof(out)) == 0);
        else CHECK(out.nodeCount <= BTB_FDT_MAX_NODES && out.propertyCount <= BTB_FDT_MAX_PROPERTIES);
    }
    puts("FDT validation: 10,000 deterministic mutations; no unsafe publication.");
    return 0;
}
int main(void) { return InspectErrors(); }
