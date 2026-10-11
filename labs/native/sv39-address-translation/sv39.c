/*-----------------------------------------------------------------------------
 * Bits2Banking — Sv39 Page Translation Laboratory
 * File: sv39.c
 * PURPOSE: Explain a three-level RISC-V page-table walk in portable C23.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "sv39.h"
#include <string.h>

#define PTE_VALID UINT64_C(1)
#define PTE_ACCESSED UINT64_C(64)
#define PTE_DIRTY UINT64_C(128)
#define MIDDLE_PPN UINT64_C(2)
#define LEAF_PPN UINT64_C(3)
#define PTE_PPN_SHIFT 10U

static int CanonicalSv39(uint64_t virtualAddress)
{
    const uint64_t upper = virtualAddress >> 39U;
    const uint64_t sign = (virtualAddress >> 38U) & UINT64_C(1);
    return upper == (sign ? ((UINT64_C(1) << 25U) - 1U) : UINT64_C(0));
}

static size_t Index(uint64_t address, unsigned shift)
{
    return (size_t)((address >> shift) & UINT64_C(511));
}

BtbSv39Result BtbSv39MapOne(BtbSv39Space *space, uint64_t virtualFrame,
                             uint64_t physicalFrame, uint64_t permissions)
{
    if (space == NULL) return BTB_SV39_BAD_ARGUMENT;
    if (!CanonicalSv39(virtualFrame) ||
        (virtualFrame & (BTB_SV39_PAGE_BYTES - 1U)) != 0U ||
        (physicalFrame & (BTB_SV39_PAGE_BYTES - 1U)) != 0U ||
        ((permissions & (BTB_SV39_READ | BTB_SV39_WRITE | BTB_SV39_EXEC)) == 0U) ||
        (permissions & ~(BTB_SV39_READ | BTB_SV39_WRITE | BTB_SV39_EXEC)) != 0U ||
        ((permissions & BTB_SV39_WRITE) != 0U &&
         (permissions & BTB_SV39_READ) == 0U))
        return BTB_SV39_INVALID_ADDRESS;
    /* RISC-V Sv39 PPN fields occupy bits 53:10 (44 PPN bits). */
    if ((physicalFrame >> 12U) > ((UINT64_C(1) << 44U) - 1U))
        return BTB_SV39_INVALID_ADDRESS;
    BtbSv39Space staged = {0};
    staged.root[Index(virtualFrame, 30U)] =
        (MIDDLE_PPN << PTE_PPN_SHIFT) | PTE_VALID;
    staged.middle[Index(virtualFrame, 21U)] =
        (LEAF_PPN << PTE_PPN_SHIFT) | PTE_VALID;
    staged.leaf[Index(virtualFrame, 12U)] =
        ((physicalFrame >> 12U) << PTE_PPN_SHIFT) |
        permissions | PTE_VALID | PTE_ACCESSED | PTE_DIRTY;
    /* A map succeeds as one operation; its existing contents are not exposed
     * until the complete validation and PTE plan has succeeded. */
    memcpy(space, &staged, sizeof staged);
    return BTB_SV39_OK;
}

BtbSv39Result BtbSv39Translate(const BtbSv39Space *space, uint64_t virtualAddress,
                               uint64_t requestedAccess, uint64_t *outPhysical)
{
    if (space == NULL || outPhysical == NULL || requestedAccess == 0U ||
        (requestedAccess & ~(BTB_SV39_READ | BTB_SV39_WRITE | BTB_SV39_EXEC)) != 0U)
        return BTB_SV39_BAD_ARGUMENT;
    if (!CanonicalSv39(virtualAddress)) return BTB_SV39_INVALID_ADDRESS;
    const uint64_t top = space->root[Index(virtualAddress, 30U)];
    if ((top & PTE_VALID) == 0U || (top >> PTE_PPN_SHIFT) != MIDDLE_PPN ||
        (top & (BTB_SV39_READ | BTB_SV39_WRITE | BTB_SV39_EXEC)) != 0U)
        return BTB_SV39_UNMAPPED;
    const uint64_t middle = space->middle[Index(virtualAddress, 21U)];
    if ((middle & PTE_VALID) == 0U || (middle >> PTE_PPN_SHIFT) != LEAF_PPN ||
        (middle & (BTB_SV39_READ | BTB_SV39_WRITE | BTB_SV39_EXEC)) != 0U)
        return BTB_SV39_UNMAPPED;
    const uint64_t entry = space->leaf[Index(virtualAddress, 12U)];
    if ((entry & PTE_VALID) == 0U ||
        (entry & (BTB_SV39_READ | BTB_SV39_WRITE | BTB_SV39_EXEC)) == 0U)
        return BTB_SV39_UNMAPPED;
    if ((entry & BTB_SV39_WRITE) != 0U && (entry & BTB_SV39_READ) == 0U)
        return BTB_SV39_PERMISSION_DENIED;
    if ((entry & requestedAccess) != requestedAccess ||
        (entry & PTE_ACCESSED) == 0U ||
        ((requestedAccess & BTB_SV39_WRITE) != 0U && (entry & PTE_DIRTY) == 0U))
        return BTB_SV39_PERMISSION_DENIED;
    const uint64_t physicalFrame = (entry >> PTE_PPN_SHIFT) &
        ((UINT64_C(1) << 44U) - 1U);
    *outPhysical = (physicalFrame << 12U) |
        (virtualAddress & (BTB_SV39_PAGE_BYTES - 1U));
    return BTB_SV39_OK;
}
