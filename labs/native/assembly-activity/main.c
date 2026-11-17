/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/assembly-activity/main.c
 *
 * PURPOSE:
 *   Compare an assembly forwarding call with the shared C activity contract at boundary values.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "../activity-adapters/bridge.h"
#include <limits.h>
#include <stdio.h>
extern int BtbAssemblyActivityNext(int current);
int main(void)
{
    const int inputs[] = {INT_MIN, -1, 0, 41, 999, 1000, INT_MAX};
    const int expected[] = {-1, -1, 1, 42, 1000, -1, -1};
    for (size_t i = 0; i < sizeof inputs / sizeof inputs[0]; ++i) {
        int next = BtbAssemblyActivityNext(inputs[i]);
        if (next != expected[i] || next != BtbActivityNext(inputs[i])) return 1;
        printf("%d -> %d\n", inputs[i], next);
    }
    return 0;
}
