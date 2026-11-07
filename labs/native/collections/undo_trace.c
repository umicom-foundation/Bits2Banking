/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/collections/undo_trace.c
 *
 * PURPOSE:
 *   Demonstrate committing an edit only after its undo record fits.
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

/* The stack stores prior values. A failed append must leave the visible
   value untouched because no matching undo record can then be retained. */
static BtbResult Change(BtbList *history, int *current, int replacement)
{
    BtbResult result = BtbListAppend(history, *current);
    if (result == BTB_OK) *current = replacement;
    return result;
}
int main(void)
{
    BtbList history = {0};
    int current = 10;
    for (int i = 1; i <= 8; ++i)
        if (Change(&history, &current, 10 + i) != BTB_OK) return 1;
    if (Change(&history, &current, 99) != BTB_FULL || current != 18) return 2;
    for (int expected = 17; expected >= 10; --expected) {
        if (BtbStackPop(&history, &current) != BTB_OK) return 3;
        if (current != expected) return 4;
        printf("restored %d\n", current);
    }
    if (BtbStackPop(&history, &current) != BTB_EMPTY || current != 10) return 5;
    return 0;
}
