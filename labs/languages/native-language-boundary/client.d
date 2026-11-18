/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/client.d
 *
 * PURPOSE:
 *   Teach and verify a fixed-width C ABI without transferring allocation ownership.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import std.stdio : writeln;
extern(C) int bounded_progress(int completed, int total, int* percent) nothrow @nogc;
static assert(int.sizeof == 4);
int main()
{
    int percent = -1;
    if (bounded_progress(2, 8, &percent) != 0 || percent != 25)
        return 1;
    writeln(percent);
    if (bounded_progress(1, 0, &percent) != 1 || percent != 25)
        return 2;
    writeln("D boundary checks passed");
    return 0;
}
