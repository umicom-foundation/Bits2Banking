/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/d-activity/main.d
 *
 * PURPOSE:
 *   Use the existing C activity contract from D BetterC without a managed runtime.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import core.stdc.stdio : printf;
extern(C) int BtbActivityNext(int current) nothrow @nogc;
extern(C) int main() nothrow @nogc
{
    immutable int[5] inputs = [-1, 0, 41, 999, 1000];
    immutable int[5] expected = [-1, 1, 42, 1000, -1];
    foreach (index, current; inputs) {
        const int next = BtbActivityNext(current);
        // Explicit checks remain active even if the compiler disables assertions.
        if (next != expected[index]) return 1;
        printf("%d -> %d\n", current, next);
    }
    return 0;
}
