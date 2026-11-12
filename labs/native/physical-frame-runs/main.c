/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/physical-frame-runs/main.c
 *
 * PURPOSE:
 *   Demonstrate alignment, fragmentation and complete release through the production Kernel allocator.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/kernel/physical_memory.h"
#include <stdio.h>
#include <string.h>

#define REQUIRE(condition) do { if (!(condition)) {     fprintf(stderr, "Requirement failed at line %d: %s\n", __LINE__, #condition);     return 1; } } while (0)
#define OK UMICOM_KERNEL_MEMORY_OK
#define PAGE UMICOM_KERNEL_PAGE_SIZE
#define BASE ((UmicomAddress)0x1000U)

/* These are synthetic physical addresses. The program never dereferences them,
 * writes a device, maps memory or changes the host operating system's allocator. */
static int Counts(UmicomSize reserved, UmicomSize allocated)
{
    UmicomKernelPhysicalMemorySnapshot view;
    REQUIRE(UmicomKernelPhysicalMemorySnapshotRead(&view) == OK);
    REQUIRE(view.reservedFrames == reserved && view.allocatedFrames == allocated);
    REQUIRE(view.freeFrames == view.totalFrames - reserved - allocated);
    REQUIRE(UmicomKernelPhysicalMemoryValidate() == OK);
    printf("reserved=%llu allocated=%llu free=%llu\n",
        (unsigned long long)view.reservedFrames,
        (unsigned long long)view.allocatedFrames,
        (unsigned long long)view.freeFrames);
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: physical-frame-runs alignment|fragmentation|release|coexist\n");
        return 2;
    }
    /* Reset only an isolated teaching allocator. Real boot initializes once,
     * then reserves its image, metadata and firmware-owned storage. */
    REQUIRE(UmicomKernelPhysicalMemoryInitialize(BASE, 16U * PAGE) == OK);
    const char *scenario = argv[1];
    UmicomAddress first = (UmicomAddress)0xdeadbeefU;
    if (strcmp(scenario, "alignment") == 0) {
        REQUIRE(UmicomKernelPhysicalMemoryAllocateFrames(3U, 4U, &first) == OK);
        REQUIRE(first == (UmicomAddress)0x4000U);
        printf("first=0x%llx count=3 alignment=4 pages\n", (unsigned long long)first);
        REQUIRE(Counts(0U, 3U) == 0);
        REQUIRE(UmicomKernelPhysicalMemoryFreeFrames(first, 3U) == OK);
    } else if (strcmp(scenario, "fragmentation") == 0) {
        for (UmicomSize index = 1U; index < 16U; index += 2U)
            REQUIRE(UmicomKernelPhysicalMemoryReserveRange(BASE + (UmicomAddress)(index * PAGE), PAGE) == OK);
        REQUIRE(Counts(8U, 0U) == 0);
        REQUIRE(UmicomKernelPhysicalMemoryAllocateFrames(2U, 1U, &first) == UMICOM_KERNEL_MEMORY_OUT_OF_MEMORY);
        REQUIRE(first == (UmicomAddress)0xdeadbeefU);
        puts("Eight free pages do not form a two-page run.");
        /* Release only a reservation this example owns, then retry once after
         * an actual state change. A firmware reservation must not be discarded
         * just to make an allocation succeed. */
        REQUIRE(UmicomKernelPhysicalMemoryReleaseReservedRange(BASE + (UmicomAddress)PAGE, PAGE) == OK);
        REQUIRE(UmicomKernelPhysicalMemoryAllocateFrames(2U, 1U, &first) == OK);
        REQUIRE(first == BASE);
        REQUIRE(UmicomKernelPhysicalMemoryFreeFrames(first, 2U) == OK);
        return Counts(7U, 0U);
    } else if (strcmp(scenario, "release") == 0) {
        REQUIRE(UmicomKernelPhysicalMemoryAllocateFrames(4U, 1U, &first) == OK);
        REQUIRE(UmicomKernelPhysicalMemoryFreeFrame(first + (UmicomAddress)(2U * PAGE)) == OK);
        REQUIRE(UmicomKernelPhysicalMemoryFreeFrames(first, 4U) == UMICOM_KERNEL_MEMORY_NOT_ALLOCATED);
        REQUIRE(Counts(0U, 3U) == 0);
        UmicomKernelPhysicalFrameState state;
        REQUIRE(UmicomKernelPhysicalMemoryFrameQuery(first, &state) == OK);
        REQUIRE(state == UMICOM_PHYSICAL_FRAME_ALLOCATED);
        REQUIRE(UmicomKernelPhysicalMemoryFreeFrames(first, 2U) == OK);
        REQUIRE(UmicomKernelPhysicalMemoryFreeFrame(first + (UmicomAddress)(3U * PAGE)) == OK);
        puts("The refused release left its earlier pages allocated.");
    } else if (strcmp(scenario, "coexist") == 0) {
        REQUIRE(UmicomKernelPhysicalMemoryAllocateFrame(&first) == OK && first == BASE);
        UmicomAddress run = 0U;
        REQUIRE(UmicomKernelPhysicalMemoryAllocateFrames(3U, 2U, &run) == OK);
        REQUIRE(run == (UmicomAddress)0x2000U);
        REQUIRE(Counts(0U, 4U) == 0);
        REQUIRE(UmicomKernelPhysicalMemoryFreeFrames(run, 3U) == OK);
        REQUIRE(UmicomKernelPhysicalMemoryFreeFrame(first) == OK);
        puts("Single pages and runs share one ownership inventory.");
    } else {
        fprintf(stderr, "Unknown scenario: %s\n", scenario);
        return 2;
    }
    return Counts(0U, 0U);
}
