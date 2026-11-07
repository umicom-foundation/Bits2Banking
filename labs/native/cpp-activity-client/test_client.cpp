/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/cpp-activity-client/test_client.cpp
 *
 * PURPOSE:
 *   Verify the C++ caller reaches the shared C boundary and retains its semantics.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "../activity-adapters/bridge.h"
#include <climits>
#include <cstdio>

int main()
{
    struct Case { int current; int expected; };
    const Case cases[] = {
        {0, 1}, {999, 1000}, {1000, -1}, {-1, -1},
        {INT_MIN, -1}, {INT_MAX, -1}
    };
    for (const Case& item : cases) {
        const int actual = BtbActivityNext(item.current);
        if (actual != item.expected) {
            std::fprintf(stderr, "Input %d: expected %d, received %d\n",
                         item.current, item.expected, actual);
            return 1;
        }
    }
    return 0;
}
