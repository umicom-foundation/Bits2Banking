/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/readonly_views.d
 *
 * PURPOSE:
 *   Distinguish a D const slice view from independent mutable and immutable copies.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module readonly_views;
import std.stdio : writeln;

void main()
{
    int[] original = [6, 7];
    const(int)[] view = original;
    int[] independent = view.dup;
    immutable(int)[] frozen = view.idup;

    // const constrains this view; it does not remove the original mutable alias.
    original[0] = 8;
    assert(view[0] == 8);
    assert(independent[0] == 6 && frozen[0] == 6);
    independent[1] = 9;
    assert(original[1] == 7 && frozen[1] == 7);

    static assert(!__traits(compiles, view[0] = 1));
    static assert(!__traits(compiles, frozen[0] = 1));
    // The slice descriptor itself is mutable; const applies to its elements.
    view = original[1 .. $];
    assert(view.length == 1 && view[0] == 7);

    writeln("Original: ", original);
    writeln("Independent mutable copy: ", independent);
    writeln("Independent immutable copy: ", frozen);
    writeln("Rebound read-only view: ", view);
}
