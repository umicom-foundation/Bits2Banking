/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/collections/search_trace.c
 *
 * PURPOSE:
 *   Compare first-match search contracts over a sorted catalogue.
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
    BtbList catalog = {.values = {-4, 0, 0, 7, 9}, .count = 5};
    for (int target = -5; target <= 10; ++target) {
        size_t linear = 99, binary = 99;
        BtbResult left = BtbListFind(&catalog, target, &linear);
        BtbResult right = BtbListFindSorted(&catalog, target, &binary);
        if (left != right || linear != binary) return 1;
        if (left == BTB_OK) printf("%d: first index %zu\n", target, binary);
        else if (left == BTB_NOT_FOUND) printf("%d: absent\n", target);
        else return 2;
    }
    size_t first_zero = 99;
    if (BtbListFindSorted(&catalog, 0, &first_zero) != BTB_OK || first_zero != 1)
        return 3;
    return 0;
}
