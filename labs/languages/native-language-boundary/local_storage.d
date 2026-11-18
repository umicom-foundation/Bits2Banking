/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/local_storage.d
 *
 * PURPOSE:
 *   Distinguish automatic, thread-local static and explicit caller-owned counter state.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module local_storage;
import std.stdio : writeln;
struct Counter { uint value; }

bool nextOwned(ref Counter state, ref uint outputValue) @safe nothrow @nogc
{
    if(state.value >= 3) return false;
    uint candidate = state.value + 1;
    state.value = candidate;
    outputValue = candidate;
    return true;
}
bool nextAutomatic(ref uint outputValue) @safe nothrow @nogc
{
    Counter state;
    return nextOwned(state, outputValue);
}
bool nextHidden(ref uint outputValue) @safe nothrow @nogc
{
    // Mutable static storage is thread-local by default in D. A local name
    // still shares this retained state among callers on the current thread.
    static Counter state;
    return nextOwned(state, outputValue);
}
// Preserve the initial assertion-based exercise for review. Assertions can be
// disabled in release builds, including calls inside their expressions. The
// active checked helper below keeps all demonstrations and failures observable.
version (none) {
void checkOwners() @safe
{
    Counter left, right;
    uint a = 99, b = 99;
    assert(nextOwned(left, a) && a == 1);
    assert(nextOwned(right, b) && b == 1);
    assert(nextOwned(left, a) && a == 2);
    assert(left.value == 2 && right.value == 1);
    assert(nextOwned(left, a) && a == 3);
    a = 99;
    assert(!nextOwned(left, a));
    assert(a == 99 && left.value == 3 && right.value == 1);
}
unittest { checkOwners(); }
void main() @safe
{
    uint a = 99, b = 99;
    assert(nextAutomatic(a) && nextAutomatic(b));
    assert(a == 1 && b == 1);
    writeln("Automatic calls: 1, 1");
    assert(nextHidden(a) && nextHidden(b));
    assert(a == 1 && b == 2);
    writeln("Static calls: 1, 2");
    checkOwners();
    writeln("Owned counters: left 3, right 1; refusal preserved 99");
}
}

private void require(bool condition) @safe
{
    if (!condition) throw new Exception("Local storage ownership check failed");
}
void checkOwners() @safe
{
    Counter left, right;
    uint a = 99, b = 99;
    require(nextOwned(left, a) && a == 1);
    require(nextOwned(right, b) && b == 1);
    require(nextOwned(left, a) && a == 2);
    require(left.value == 2 && right.value == 1);
    require(nextOwned(left, a) && a == 3);
    a = 99;
    require(!nextOwned(left, a));
    require(a == 99 && left.value == 3 && right.value == 1);
}
unittest { checkOwners(); }
void main() @safe
{
    uint a = 99, b = 99;
    require(nextAutomatic(a) && nextAutomatic(b));
    require(a == 1 && b == 1);
    writeln("Automatic calls: 1, 1");
    require(nextHidden(a) && nextHidden(b));
    require(a == 1 && b == 2);
    writeln("Static calls: 1, 2");
    checkOwners();
    writeln("Owned counters: left 3, right 1; refusal preserved 99");
}
