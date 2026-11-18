/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/conditional_wire.d
 *
 * PURPOSE:
 *   Use compile-time type admission to encode explicit unsigned wire bytes without serializing struct layout.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module conditional_wire;
import std.stdio : writeln;

/* An eponymous template exposes its same-named value directly. Unsupported
 * types fail during compilation instead of acquiring an accidental encoding. */
template wireWidth(T)
{
    static if (is(T == uint)) enum wireWidth = 4;
    else static if (is(T == ulong)) enum wireWidth = 8;
    else static assert(false, "Only uint and ulong have this teaching encoding");
}

ubyte[wireWidth!T] encodeLittleEndian(T)(T value)
    if (is(T == uint) || is(T == ulong))
{
    ubyte[wireWidth!T] result;
    static foreach (position; 0 .. wireWidth!T)
        result[position] = cast(ubyte)(value >> (8 * position));
    return result;
}

static assert(uint.sizeof == 4 && ulong.sizeof == 8);
static assert(wireWidth!uint == 4 && wireWidth!ulong == 8);
static assert(!__traits(compiles, encodeLittleEndian(1.5)));

unittest
{
    ubyte[4] expected32 = [0x78, 0x56, 0x34, 0x12];
    ubyte[8] expected64 = [8, 7, 6, 5, 4, 3, 2, 1];
    assert(encodeLittleEndian(0x12345678u) == expected32);
    assert(encodeLittleEndian(0x0102030405060708UL) == expected64);
    assert(encodeLittleEndian(uint.max) == [255, 255, 255, 255]);
}

void main()
{
    version (Windows) writeln("Host family: Windows");
    else version (Posix) writeln("Host family: POSIX");
    else writeln("Host family: another D target");
    debug (TraceEncoding) writeln("Compile-time TraceEncoding diagnostic enabled");
    auto bytes = encodeLittleEndian(0x12345678u);
    foreach (value; bytes) writeln(value);
    writeln("Expected decimal bytes: 120, 86, 52, 18");
}
