/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/qualifier_preserving_views.d
 *
 * PURPOSE:
 *   Demonstrate qualifier-preserving borrowed slices without allocating a copied byte buffer.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module qualifier_preserving_views;
import std.stdio : writeln;

// inout ties the element qualifier of the result to the input. This function
// returns a view, not new storage; its caller keeps the backing array alive.
inout(ubyte)[] prefixView(inout(ubyte)[] source, size_t wanted)
    @safe pure nothrow @nogc
{
    const count = wanted < source.length ? wanted : source.length;
    return source[0 .. count];
}

unittest
{
    ubyte[3] owner = [1, 2, 3];
    auto mutableView = prefixView(owner[], 2);
    static assert(is(typeof(mutableView) == ubyte[]));
    mutableView[0] = 7;
    assert(owner[0] == 7 && mutableView.length == 2);
    const(ubyte)[] readOnly = owner[];
    auto readView = prefixView(readOnly, 99);
    static assert(is(typeof(readView) == const(ubyte)[]));
    static assert(!__traits(compiles, readView[0] = 1));
    owner[0] = 8;
    assert(readView[0] == 8 && readView.length == 3);
    immutable ubyte[3] frozen = [3, 4, 5];
    auto frozenView = prefixView(frozen[], 2);
    static assert(is(typeof(frozenView) == immutable(ubyte)[]));
    static assert(!__traits(compiles, frozenView[0] = 1));
    assert(frozenView[0] == 3 && frozenView.length == 2);
    assert(prefixView(owner[], 0).length == 0);
    assert(prefixView(cast(ubyte[])null, size_t.max).length == 0);
}

int main()
{
    ubyte[3] owner = [1, 2, 3];
    auto mutableView = prefixView(owner[], 2);
    mutableView[0] = 7;
    const(ubyte)[] readOnly = owner[];
    auto readView = prefixView(readOnly, 99);
    owner[0] = 8;
    immutable ubyte[3] frozen = [3, 4, 5];
    auto frozenView = prefixView(frozen[], 2);
    if (mutableView.length != 2 || readView.length != 3 || frozenView.length != 2 ||
        mutableView[0] != 8 || readView[0] != 8 || frozenView[0] != 3)
        return 1;
    auto empty = prefixView(owner[], 0);
    if (empty.length != 0) return 2;
    writeln("mutable=", mutableView[0], " const=", readView[0], " frozen=", frozenView[0]);
    writeln("lengths=", mutableView.length, ",", readView.length, ",", frozenView.length);
    writeln("empty length=", empty.length);
    return 0;
}
