/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/boolean_wire.d
 *
 * PURPOSE:
 *   Separate D Boolean conversion from strict binary flag validation and caller-owned output.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module boolean_wire;
import std.stdio : writeln;

// Value conversion is explicit; no bool pointer is overlaid on untrusted bytes.
ubyte encodeFlag(bool value) @safe pure nothrow @nogc
{
    return value ? 1 : 0;
}
bool decodeFlag(ubyte raw, ref bool value) @safe pure nothrow @nogc
{
    if (raw > 1) return false;
    value = raw == 1;
    return true;
}
static assert(encodeFlag(false) == 0 && encodeFlag(true) == 1);
static assert(is(typeof(true) == bool));

void require(bool condition, string description)
{
    if (!condition) throw new Exception(description);
}
void checkFlags()
{
    require(cast(int)true == 1 && cast(int)false == 0, "D numeric conversion");
    require(cast(bool)2, "conversion tests nonzero; it is not strict wire admission");
    for (uint raw = 0; raw <= 255; ++raw) {
        bool destination = true;
        bool accepted = decodeFlag(cast(ubyte)raw, destination);
        if (raw <= 1) {
            require(accepted && destination == (raw == 1), "canonical flag");
        } else {
            require(!accepted && destination, "refusal preserves true");
            destination = false;
            accepted = decodeFlag(cast(ubyte)raw, destination);
            require(!accepted && !destination, "refusal preserves false");
        }
    }
}
unittest { checkFlags(); }
void main()
{
    checkFlags();
    writeln("Umicom Boolean wire: all 256 bytes checked.");
    writeln("Explicit encoding: false=0, true=1.");
}
