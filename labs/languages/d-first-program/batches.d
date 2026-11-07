/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/d-first-program/batches.d
 *
 * PURPOSE:
 *   Apply the existing D progress rule to equal-length input sequences and check rejection boundaries.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module batches;
import progress : remainingLessons;
import std.exception : enforce, assertThrown;

// A new result array belongs to the caller. Input slices are read-only through
// this function. An invalid pair throws before any result is returned.
int[] remainingBatch(const(int)[] totals, const(int)[] completed) @safe {
    enforce(totals.length == completed.length, "Progress lists must have equal lengths");
    auto result = new int[totals.length];
    foreach (index; 0 .. totals.length) {
        result[index] = remainingLessons(totals[index], completed[index]);
    }
    return result;
}

unittest {
    int[] totals = [4, 0, 6];
    int[] completed = [1, 0, 6];
    auto result = remainingBatch(totals, completed);
    assert(result == [3, 0, 0]);
    result[0] = 2;
    assert(totals == [4, 0, 6] && completed == [1, 0, 6]);
    assert(remainingBatch([], []).length == 0);
    assertThrown!Exception(remainingBatch([4], []));
    assertThrown!Exception(remainingBatch([4, 2], [1, 3]));
    assertThrown!Exception(remainingBatch([-1], [0]));
    assertThrown!Exception(remainingBatch([4], [-1]));
}

