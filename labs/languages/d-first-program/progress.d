/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/d-first-program/progress.d
 *
 * PURPOSE:
 *   Teach checked progress calculations and D unit tests in one source file.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import std.stdio : writeln;
import std.exception : enforce, assertThrown;

int remainingLessons(int total, int completed) @safe {
    enforce(total >= 0, "Total must not be negative");
    enforce(completed >= 0 && completed <= total,
            "Completed must be between zero and total");
    return total - completed;
}

unittest {
    assert(remainingLessons(4, 1) == 3);
    assert(remainingLessons(0, 0) == 0);
    assert(remainingLessons(4, 4) == 0);
    assertThrown!Exception(remainingLessons(4, 5));
    assertThrown!Exception(remainingLessons(-1, 0));
    assertThrown!Exception(remainingLessons(4, -1));
}

void main() {
    writeln("Remaining lessons: ", remainingLessons(4, 1));
}
