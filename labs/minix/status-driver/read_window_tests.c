/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: read_window_tests.c
 *
 * PURPOSE:
 *   Define and check the original bounded read-window teaching contract.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "read_window.h"
#include <stdint.h>
#include <stdio.h>
#define CHECK(condition) do { if (!(condition)) { fputs(#condition "\n", stderr); return 1; } } while (0)
int main(void)
{
    size_t offset = 99, count = 98;
    CHECK(umi_learning_read_window(3, 4, 10, &offset, &count));
    CHECK(offset == 3 && count == 4);
    CHECK(umi_learning_read_window(9, SIZE_MAX, 10, &offset, &count));
    CHECK(offset == 9 && count == 1);
    CHECK(umi_learning_read_window(UINT64_MAX, SIZE_MAX, 10, &offset, &count));
    CHECK(offset == 10 && count == 0);
    CHECK(umi_learning_read_window(0, 0, 0, &offset, &count));
    CHECK(offset == 0 && count == 0);
    CHECK(umi_learning_read_window(5, 0, 10, &offset, &count));
    CHECK(offset == 5 && count == 0);
    CHECK(!umi_learning_read_window(0, 1, 10, 0, &count) && count == 0);
    CHECK(!umi_learning_read_window(0, 1, 10, &offset, &offset) && offset == 5);
    return 0;
}
