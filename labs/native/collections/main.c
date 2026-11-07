/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/collections/main.c
 *
 * PURPOSE:
 *   Demonstrate a list, stable sorting and first-match search.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "collections.h"
#include <stdio.h>
int main(void)
{
    BtbList list = {0};
    const int input[] = {7, 2, 9, 2};
    for (size_t i = 0; i < sizeof input / sizeof input[0]; ++i)
        if (BtbListAppend(&list, input[i]) != BTB_OK) return 1;
    if (BtbListSort(&list) != BTB_OK) return 1;
    for (size_t i = 0; i < list.count; ++i)
        if (printf("%s%d", i == 0 ? "" : " ", list.values[i]) < 0) return 1;
    size_t position = 0;
    if (BtbListFindSorted(&list, 7, &position) != BTB_OK) return 1;
    if (printf("\n7 is at index %zu\n", position) < 0) return 1;
    return fflush(stdout) == EOF ? 1 : 0;
}
