/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/umicom-c-brew-time/brew-time-heap.c
 *
 * PURPOSE:
 * Compare reachability and actual collection for a small host-owned graph.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <umicom_c/managed_heap.h>

int main(void)
{
    static UmcManagedHeap heap;
    UmcHandle recipe = 0U;
    UmcHandle brew_time = 0U;
    UmcHandle discarded_draft = 0U;
    UmcHeapReport report = {0};
    size_t collected = 0;
    const uint8_t expected_time = 4U;
    uint8_t observed_time = 0U;

    umc_heap_init(&heap);
    /* A recipe links to its accepted time. The draft has its own handle but
       has no edge from the recipe and is outside the roots used below. */
    if (umc_heap_allocate(&heap, 0U, &recipe) != UMC_HEAP_OK ||
        umc_heap_allocate(&heap, 1U, &brew_time) != UMC_HEAP_OK ||
        umc_heap_allocate(&heap, 1U, &discarded_draft) != UMC_HEAP_OK ||
        umc_heap_write(&heap, brew_time, 0U, &expected_time, 1U) != UMC_HEAP_OK ||
        umc_heap_set_edge(&heap, recipe, 0U, brew_time) != UMC_HEAP_OK) {
        fputs("Could not prepare the practice objects.\n", stderr);
        return 1;
    }

    if (umc_heap_inspect(&heap, &recipe, 1U, &report) != UMC_HEAP_OK ||
        report.live_objects != 3U || report.reachable_objects != 2U || report.collectable_objects != 1U) {
        fputs("The preview did not identify the two reachable objects.\n", stderr);
        return 1;
    }
    printf("Before collection: %zu reachable, %zu collectable.\n",
        report.reachable_objects, report.collectable_objects);

    /* Use the same root for collection and compare the saved time afterward. */
    if (umc_heap_collect(&heap, &recipe, 1U, &collected) != UMC_HEAP_OK || collected != 1U ||
        umc_heap_read(&heap, brew_time, 0U, &observed_time, 1U) != UMC_HEAP_OK || observed_time != expected_time ||
        umc_heap_read(&heap, discarded_draft, 0U, &observed_time, 1U) == UMC_HEAP_OK) {
        fputs("Collection did not preserve the accepted time and refuse the old draft.\n", stderr);
        return 1;
    }
    printf("After collection: %zu reclaimed, time remains %u minutes.\n", collected, (unsigned)observed_time);
    return 0;
}
