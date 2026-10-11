/*-----------------------------------------------------------------------------
 * Bits to Banking — Cache and Memory Access Laboratory
 * File: labs/native/cache-memory/main.c
 * PURPOSE: Read an identical array in two orders and compare their checksums.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_COUNT 1024U
#define COLUMN_COUNT 1024U

/* The program owns the allocated array from malloc until free. Both passes
 * read exactly the same values; changing the access order changes locality,
 * not the desired result. Timing is illustrative, not a hardware benchmark. */
int main(void)
{
    const size_t itemCount = (size_t)ROW_COUNT * (size_t)COLUMN_COUNT;
    if (itemCount > SIZE_MAX / sizeof(uint32_t)) {
        fputs("Array would be too large for this machine.\n", stderr);
        return EXIT_FAILURE;
    }
    uint32_t *numbers = malloc(itemCount * sizeof(*numbers));
    if (numbers == NULL) {
        fputs("Could not allocate the training array.\n", stderr);
        return EXIT_FAILURE;
    }
    for (size_t i = 0U; i < itemCount; ++i)
        numbers[i] = (uint32_t)(i % 1000U);

    uint64_t rowSum = 0U;
    clock_t rowStart = clock();
    for (size_t row = 0U; row < ROW_COUNT; ++row)
        for (size_t column = 0U; column < COLUMN_COUNT; ++column)
            rowSum += numbers[row * COLUMN_COUNT + column];
    clock_t rowEnd = clock();

    uint64_t columnSum = 0U;
    clock_t columnStart = clock();
    for (size_t column = 0U; column < COLUMN_COUNT; ++column)
        for (size_t row = 0U; row < ROW_COUNT; ++row)
            columnSum += numbers[row * COLUMN_COUNT + column];
    clock_t columnEnd = clock();

    if (rowSum != columnSum) {
        fputs("The two access patterns produced different totals.\n", stderr);
        free(numbers);
        return EXIT_FAILURE;
    }
    double rowMs = rowStart != (clock_t)-1 && rowEnd != (clock_t)-1
                   ? 1000.0 * (double)(rowEnd - rowStart) / (double)CLOCKS_PER_SEC : -1.0;
    double columnMs = columnStart != (clock_t)-1 && columnEnd != (clock_t)-1
                      ? 1000.0 * (double)(columnEnd - columnStart) / (double)CLOCKS_PER_SEC : -1.0;
    (void)printf("Array elements: %zu\n", itemCount);
    (void)printf("Row-first checksum: %" PRIu64 "\n", rowSum);
    (void)printf("Column-first checksum: %" PRIu64 "\n", columnSum);
    (void)printf("Row-first CPU time (ms): %.3f\n", rowMs);
    (void)printf("Column-first CPU time (ms): %.3f\n", columnMs);
    (void)puts("Checksums agree. Timing varies with compiler, machine and CPU caches.");
    free(numbers);
    return EXIT_SUCCESS;
}
