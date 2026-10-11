/*-----------------------------------------------------------------------------
 * Bits2Banking · Umicom Foundation
 * File: labs/native/page-fault-model/page_map.c
 * PURPOSE: Validate individual simulated virtual-page access and refusal.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "page_map.h"
#include <string.h>

static int BtbCanonicalSv39(uint64_t virtualAddress)
{
    const uint64_t upper = virtualAddress >> 39U;
    const uint64_t signBit = (virtualAddress >> 38U) & 1U;
    return signBit == 0U ? upper == 0U : upper == (UINT64_MAX >> 39U);
}

void BtbAddressSpaceInit(BtbAddressSpace *space)
{
    if (space != NULL) memset(space, 0, sizeof(*space));
}

BtbPageStatus BtbPageMap(BtbAddressSpace *space, uint64_t virtualPage,
                         uint64_t physicalFrame, unsigned rights)
{
    if (space == NULL || space->mappingCount > BTB_MAX_PAGE_MAPPINGS ||
        virtualPage % BTB_PAGE_BYTES != 0U ||
        physicalFrame % BTB_PAGE_BYTES != 0U ||
        rights == 0U || (rights & ~7U) != 0U ||
        ((rights & BTB_PAGE_WRITE) != 0U && (rights & BTB_PAGE_READ) == 0U) ||
        ((rights & BTB_PAGE_WRITE) != 0U && (rights & BTB_PAGE_EXECUTE) != 0U) ||
        physicalFrame > UINT64_MAX - (BTB_PAGE_BYTES - 1U))
        return BTB_PAGE_INVALID_ARGUMENT;
    if (!BtbCanonicalSv39(virtualPage)) return BTB_PAGE_NON_CANONICAL;
    for (size_t i = 0U; i < space->mappingCount; ++i)
        if (space->mappings[i].virtualPage == virtualPage)
            return BTB_PAGE_ALREADY_MAPPED;
    if (space->mappingCount == BTB_MAX_PAGE_MAPPINGS)
        return BTB_PAGE_OUT_OF_SPACE;
    space->mappings[space->mappingCount++] =
        (BtbPageMapping){virtualPage, physicalFrame, rights};
    return BTB_PAGE_OK;
}

BtbPageStatus BtbPageAccessAddress(const BtbAddressSpace *space,
                                   uint64_t virtualAddress, BtbPageAccess action,
                                   uint64_t *outPhysicalAddress)
{
    if (space == NULL || outPhysicalAddress == NULL ||
        space->mappingCount > BTB_MAX_PAGE_MAPPINGS ||
        (action != BTB_ACCESS_READ && action != BTB_ACCESS_WRITE &&
         action != BTB_ACCESS_EXECUTE))
        return BTB_PAGE_INVALID_ARGUMENT;
    if (!BtbCanonicalSv39(virtualAddress)) return BTB_PAGE_NON_CANONICAL;
    const uint64_t page = virtualAddress & ~(BTB_PAGE_BYTES - 1U);
    for (size_t i = 0U; i < space->mappingCount; ++i) {
        if (space->mappings[i].virtualPage != page) continue;
        if ((space->mappings[i].rights & (unsigned)action) == 0U)
            return BTB_PAGE_PROTECTION_FAULT;
        /* The physical frame is aligned. The original offset remains intact;
         * denied accesses never modify the caller's previous output value. */
        *outPhysicalAddress = space->mappings[i].physicalFrame +
                              (virtualAddress & (BTB_PAGE_BYTES - 1U));
        return BTB_PAGE_OK;
    }
    return BTB_PAGE_NOT_MAPPED;
}

BtbPageStatus BtbPageUnmap(BtbAddressSpace *space, uint64_t virtualPage)
{
    if (space == NULL || space->mappingCount > BTB_MAX_PAGE_MAPPINGS ||
        virtualPage % BTB_PAGE_BYTES != 0U)
        return BTB_PAGE_INVALID_ARGUMENT;
    if (!BtbCanonicalSv39(virtualPage)) return BTB_PAGE_NON_CANONICAL;
    for (size_t i = 0U; i < space->mappingCount; ++i) {
        if (space->mappings[i].virtualPage != virtualPage) continue;
        for (size_t j = i + 1U; j < space->mappingCount; ++j)
            space->mappings[j - 1U] = space->mappings[j];
        --space->mappingCount;
        space->mappings[space->mappingCount] = (BtbPageMapping){0};
        return BTB_PAGE_OK;
    }
    return BTB_PAGE_NOT_MAPPED;
}

const char *BtbPageStatusText(BtbPageStatus status)
{
    switch (status) {
    case BTB_PAGE_OK: return "allowed";
    case BTB_PAGE_INVALID_ARGUMENT: return "invalid mapping or access";
    case BTB_PAGE_NON_CANONICAL: return "non-canonical virtual address";
    case BTB_PAGE_ALREADY_MAPPED: return "page already mapped";
    case BTB_PAGE_OUT_OF_SPACE: return "mapping table full";
    case BTB_PAGE_NOT_MAPPED: return "unmapped page fault";
    case BTB_PAGE_PROTECTION_FAULT: return "protection fault";
    }
    return "unknown result";
}
