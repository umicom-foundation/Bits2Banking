/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/riscv-inactive-domain/private_pages.c
 *
 * PURPOSE:
 *   Verify complete-range permission changes using the Kernel's inactive domain.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/kernel/riscv64/domain_address_space.h"
#include <stdio.h>
#include <string.h>

#define PAGE UMICOM_KERNEL_PAGE_SIZE
#define RW (UMICOM_KERNEL_VIRTUAL_MEMORY_READ | UMICOM_KERNEL_VIRTUAL_MEMORY_WRITE)
#define RX (UMICOM_KERNEL_VIRTUAL_MEMORY_READ | UMICOM_KERNEL_VIRTUAL_MEMORY_EXECUTE)

/* This ordinary process array models physical memory. Nothing installs the
 * page-table root into a processor. The Kernel accesses tables in the array. */
alignas(4096) static unsigned char ram[12U * PAGE];
static unsigned char before[sizeof ram];

#define CHECK(expression) do { \
    if (!(expression)) { \
        fprintf(stderr, "Check on line %d failed: %s\n", __LINE__, #expression); \
        return 1; \
    } \
} while (0)

static bool ReadLeaf(UmicomKernelVirtualAddressSpace *space, UmicomAddress view,
    UmicomAddress expectedPhysical, UmicomKernelVirtualMemoryPermissions expectedRights)
{
    /* Report both backing and rights. A rights change must not remap bytes. */
    UmicomAddress physical = 0U;
    UmicomKernelVirtualMemoryPermissions rights = 0U;
    return UmicomKernelVirtualMemoryTranslate(space, view, &physical, &rights) ==
        UMICOM_KERNEL_VIRTUAL_MEMORY_OK && physical == expectedPhysical && rights == expectedRights;
}

int main(int argc, char *argv[])
{
    if (argc != 2) return 2;
    const bool lateMismatch = strcmp(argv[1], "late-mismatch") == 0;
    if (!lateMismatch && strcmp(argv[1], "change-private") != 0) return 2;
    const UmicomAddress physicalBase = (UmicomAddress)ram;
    const UmicomAddress privateView = 0x10000000U;
    const UmicomAddress mailboxView = privateView + 2U * PAGE;
    const UmicomKernelRiscvDomainAddressRequest plan = {
        .bootOwner = {0U, UMICOM_BOOT_HART_FIRMWARE_ENABLED, UMICOM_TRUE},
        .target = {{9U, UMICOM_BOOT_HART_FIRMWARE_ENABLED, UMICOM_FALSE}, {physicalBase + PAGE, 2U * PAGE}},
        .mailbox = {physicalBase, PAGE},
        .privateVirtualBase = privateView,
        .mailboxVirtualBase = mailboxView
    };
    UmicomKernelVirtualAddressSpace space = {0};
    UmicomKernelRiscvDomainAddressReport owner = {0};

    /* Reserve two private frames and an independent mailbox frame through the
     * production owners. A host thread does not depend on these translations. */
    CHECK(UmicomKernelPhysicalMemoryInitialize(physicalBase, sizeof ram) == UMICOM_KERNEL_MEMORY_OK);
    CHECK(UmicomKernelRiscvPrepareDomainAddressSpace(&plan, &space, &owner) ==
        UMICOM_KERNEL_RISCV_DOMAIN_ADDRESS_PREPARED);
    CHECK(ReadLeaf(&space, privateView, physicalBase + PAGE, RW));
    CHECK(ReadLeaf(&space, privateView + PAGE, physicalBase + 2U * PAGE, RW));
    CHECK(ReadLeaf(&space, mailboxView, physicalBase, RW));

    const UmicomKernelRiscvDomainProtectionRequest change = {privateView, 2U * PAGE, RW, RX};
    if (lateMismatch) {
        /* Make only the second leaf differ from the later two-page request.
         * If the implementation changes the first leaf too early, the byte
         * comparison below exposes the partial permission update. */
        const UmicomKernelRiscvDomainProtectionRequest second = {privateView + PAGE, PAGE, RW, RX};
        CHECK(UmicomKernelRiscvProtectInactiveDomainPages(&space, &owner, &second).status ==
            UMICOM_KERNEL_RISCV_DOMAIN_PROTECTED);
        memcpy(before, ram, sizeof ram);
        CHECK(UmicomKernelRiscvProtectInactiveDomainPages(&space, &owner, &change).status ==
            UMICOM_KERNEL_RISCV_DOMAIN_PROTECTION_MAPPING_MISMATCH);
        CHECK(memcmp(before, ram, sizeof ram) == 0);
        CHECK(ReadLeaf(&space, privateView, physicalBase + PAGE, RW));
    } else {
        /* The whole private span now has read/execute rights on the same frames. */
        CHECK(UmicomKernelRiscvProtectInactiveDomainPages(&space, &owner, &change).status ==
            UMICOM_KERNEL_RISCV_DOMAIN_PROTECTED);
        CHECK(ReadLeaf(&space, privateView, physicalBase + PAGE, RX));
    }
    CHECK(ReadLeaf(&space, privateView + PAGE, physicalBase + 2U * PAGE, RX));
    CHECK(ReadLeaf(&space, mailboxView, physicalBase, RW));

    /* Retire the original space and report together. The snapshot verifies
     * that the lab returns its table frames and both reserved extents. */
    CHECK(UmicomKernelRiscvRetireDomainAddressSpace(&space, &owner).status ==
        UMICOM_KERNEL_RISCV_DOMAIN_RETIRED);
    UmicomKernelPhysicalMemorySnapshot snapshot;
    CHECK(UmicomKernelPhysicalMemorySnapshotRead(&snapshot) == UMICOM_KERNEL_MEMORY_OK);
    CHECK(snapshot.allocatedFrames == 0U && snapshot.reservedFrames == 0U &&
        snapshot.freeFrames == sizeof ram / PAGE);
    puts(lateMismatch ? "Late refusal preserved all page-table bytes." : "Both private pages changed. The mailbox stayed writable.");
    return 0;
}
