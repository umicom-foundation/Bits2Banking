/*-----------------------------------------------------------------------------
 * Bits2Banking · Umicom Foundation
 * File: labs/native/page-fault-model/page_map.h
 * PURPOSE: Explain page mappings and access faults without privileged code.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_PAGE_MAP_H
#define BTB_PAGE_MAP_H
#include <stddef.h>
#include <stdint.h>

#define BTB_PAGE_BYTES UINT64_C(4096)
#define BTB_MAX_PAGE_MAPPINGS 32U
#define BTB_PAGE_READ 1U
#define BTB_PAGE_WRITE 2U
#define BTB_PAGE_EXECUTE 4U

typedef enum BtbPageStatus {
    BTB_PAGE_OK = 0,
    BTB_PAGE_INVALID_ARGUMENT,
    BTB_PAGE_NON_CANONICAL,
    BTB_PAGE_ALREADY_MAPPED,
    BTB_PAGE_OUT_OF_SPACE,
    BTB_PAGE_NOT_MAPPED,
    BTB_PAGE_PROTECTION_FAULT
} BtbPageStatus;

typedef enum BtbPageAccess {
    BTB_ACCESS_READ = 1,
    BTB_ACCESS_WRITE = 2,
    BTB_ACCESS_EXECUTE = 4
} BtbPageAccess;

typedef struct BtbPageMapping {
    uint64_t virtualPage;
    uint64_t physicalFrame;
    unsigned rights;
} BtbPageMapping;

typedef struct BtbAddressSpace {
    BtbPageMapping mappings[BTB_MAX_PAGE_MAPPINGS];
    size_t mappingCount;
} BtbAddressSpace;

/* Models 4 KiB pages and canonical Sv39 address syntax. These functions do
 * NOT allocate real RAM, install CPU page tables, issue satp or handle traps. */
void BtbAddressSpaceInit(BtbAddressSpace *space);
BtbPageStatus BtbPageMap(BtbAddressSpace *space, uint64_t virtualPage,
                         uint64_t physicalFrame, unsigned rights);
BtbPageStatus BtbPageAccessAddress(const BtbAddressSpace *space,
                                   uint64_t virtualAddress, BtbPageAccess action,
                                   uint64_t *outPhysicalAddress);
BtbPageStatus BtbPageUnmap(BtbAddressSpace *space, uint64_t virtualPage);
const char *BtbPageStatusText(BtbPageStatus status);
#endif
