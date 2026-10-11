/*-----------------------------------------------------------------------------
 * Bits2Banking — Sv39 Page Translation Laboratory
 * File: sv39.h
 * PURPOSE: Model exactly one Sv39 4 KiB page mapping with owned page tables.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_SV39_H
#define BTB_SV39_H
#include <stdint.h>

#define BTB_SV39_PAGE_BYTES UINT64_C(4096)
#define BTB_SV39_READ  UINT64_C(2)
#define BTB_SV39_WRITE UINT64_C(4)
#define BTB_SV39_EXEC  UINT64_C(8)

typedef enum BtbSv39Result {
    BTB_SV39_OK = 0,
    BTB_SV39_BAD_ARGUMENT,
    BTB_SV39_INVALID_ADDRESS,
    BTB_SV39_UNMAPPED,
    BTB_SV39_PERMISSION_DENIED
} BtbSv39Result;

/* Fixed arrays represent three educational page-table frames. No real
 * physical RAM is accessed or allocated, no satp is changed, and no
 * privilege-level or hardware translation occurs in this user-space lab. */
typedef struct BtbSv39Space {
    uint64_t root[512];
    uint64_t middle[512];
    uint64_t leaf[512];
} BtbSv39Space;

/* Clears the supplied caller-owned tables and installs exactly one mapping.
 * Virtual and physical frame addresses must both be aligned to 4096 bytes.
 * Denies write-only PTEs (reserved by RISC-V) and zero permissions.
 * On invalid input, the existing space is unchanged. */
BtbSv39Result BtbSv39MapOne(BtbSv39Space *space, uint64_t virtualFrame,
                             uint64_t physicalFrame, uint64_t permissions);

/* Walk three ordinary (non-superpage) entries. Checks canonical virtual
 * addresses, PTE valid and basic R/W/X permissions. A/D bits are set by the
 * map operation and checked by the walk. Deliberately omits user/supervisor,
 * SUM/MXR, global/ASID, PBMT/NAPOT and page-fault traps. The output is
 * preserved if translation fails. */
BtbSv39Result BtbSv39Translate(const BtbSv39Space *space, uint64_t virtualAddress,
                               uint64_t requestedAccess, uint64_t *outPhysical);
#endif
