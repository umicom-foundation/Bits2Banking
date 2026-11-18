/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/output_publication.d
 *
 * PURPOSE:
 *   Teach by-value, ref and out publication semantics using checked unsigned arithmetic.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module output_publication;
import std.stdio : writeln;

/* Reject overflow before evaluating the sum. Publication happens only after
 * admission. This is a small language exercise, not a replacement math service. */
bool trySum(uint left, uint right, ref uint result) @safe pure nothrow @nogc
{
    if (right > uint.max - left)
        return false;
    const uint candidate = left + right;
    result = candidate;
    return true;
}

/* out initializes the caller's variable before the body starts. Even though
 * trySum preserves its ref argument on refusal, this wrapper has already
 * discarded the caller's old value. Its different contract is deliberate. */
bool sumWithOut(uint left, uint right, out uint result) @safe pure nothrow @nogc
{
    return trySum(left, right, result);
}

/* A by-value parameter is local storage. Assigning it cannot publish a new
 * scalar to the caller; the return value is the explicit publication route. */
uint changedLocal(uint value) @safe pure nothrow @nogc
{
    value = 9;
    return value;
}

unittest
{
    uint result = 71;
    assert(trySum(20, 22, result) && result == 42);
    result = 71;
    assert(!trySum(uint.max, 1, result) && result == 71);
    assert(trySum(uint.max, 0, result) && result == uint.max);
    result = 71;
    assert(!sumWithOut(uint.max, 1, result) && result == uint.init);
    assert(sumWithOut(20, 22, result) && result == 42);
    uint original = 5;
    assert(changedLocal(original) == 9 && original == 5);
    // Inputs are by value, so this alias is admitted without changing them.
    result = 7;
    assert(trySum(result, result, result) && result == 14);
}

void main()
{
    uint retained = 71, reset = 71;
    const bool retainedStatus = trySum(uint.max, 1, retained);
    const bool resetStatus = sumWithOut(uint.max, 1, reset);
    assert(!retainedStatus && !resetStatus && retained == 71 && reset == uint.init);
    writeln("Umicom output publication");
    writeln("ref refusal preserves: ", retained);
    writeln("out refusal starts from: ", reset);
}
