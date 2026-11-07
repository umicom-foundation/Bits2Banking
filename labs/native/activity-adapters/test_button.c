/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/activity-adapters/test_button.c
 *
 * PURPOSE:
 *   Verify held buttons, release, overflow and separate device state.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "button.h"
#include <limits.h>
#include <stdio.h>
#define CHECK(c) do { if (!(c)) { fprintf(stderr, "line %d: %s\n", __LINE__, #c); return 1; } } while (0)
int main(void)
{
    BtbActivityButton first = {0}, second = {0};
    CHECK(!BtbActivityButtonSample(0, true));
    CHECK(!BtbActivityButtonSample(&first, false));
    CHECK(BtbActivityButtonSample(&first, true) && first.completed == 1U);
    CHECK(!BtbActivityButtonSample(&first, true) && first.completed == 1U);
    CHECK(BtbActivityButtonSample(&second, true) && second.completed == 1U);
    CHECK(!BtbActivityButtonSample(&first, false));
    CHECK(BtbActivityButtonSample(&first, true) && first.completed == 2U);
    first.completed = 999U;
    CHECK(!BtbActivityButtonSample(&first, false));
    CHECK(BtbActivityButtonSample(&first, true) && first.completed == 1000U);
    CHECK(!BtbActivityButtonSample(&first, false));
    CHECK(!BtbActivityButtonSample(&first, true) && first.completed == 1000U);
    first.completed = UINT_MAX;
    CHECK(!BtbActivityButtonSample(&first, false));
    CHECK(!BtbActivityButtonSample(&first, true) && first.completed == UINT_MAX);
    return 0;
}

