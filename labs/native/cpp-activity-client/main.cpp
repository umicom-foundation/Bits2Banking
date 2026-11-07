/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/cpp-activity-client/main.cpp
 *
 * PURPOSE:
 *   Call the existing C activity boundary from a minimal C++ client.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "../activity-adapters/bridge.h"
#include <cstdio>

int main()
{
    const int next = BtbActivityNext(0);
    if (next < 0) {
        std::fputs("Unable to advance activity.\n", stderr);
        return 1;
    }
    if (std::printf("Completed exercises: %d\n", next) < 0) return 1;
    return std::fflush(stdout) == 0 ? 0 : 1;
}
