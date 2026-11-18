/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/flag_operators.d
 *
 * PURPOSE:
 *   Constrain D operator templates while keeping reflected syntax separate from runtime authorization.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

module flag_operators;
import std.stdio : writeln;

struct FlagSet
{
    uint bits;
    // A compile-time constraint exposes only the operations this domain defines.
    // No string mixin or runtime source evaluation is needed for two operators.
    FlagSet opBinary(string op)(FlagSet rhs) const @safe pure nothrow @nogc
        if (op == "|" || op == "&")
    {
        static if (op == "|") return FlagSet(bits | rhs.bits);
        else return FlagSet(bits & rhs.bits);
    }
}
bool tryAdmitFlags(uint raw, ref FlagSet destination) @safe pure nothrow @nogc
{
    if ((raw & ~7u) != 0) return false;
    destination = FlagSet(raw);
    return true;
}
static assert(__traits(hasMember, FlagSet, "opBinary"));
static assert(__traits(compiles, FlagSet(1) | FlagSet(2)));
static assert(!__traits(compiles, FlagSet(1) + FlagSet(2)));

void require(bool condition, string message)
{
    if (!condition) throw new Exception(message);
}
void exercise()
{
    const readFlag = FlagSet(1);
    const inspectFlag = FlagSet(4);
    const combined = readFlag | inspectFlag;
    const common = combined & readFlag;
    const repeated = readFlag | readFlag;
    require(combined.bits == 5 && common.bits == 1 && repeated.bits == 1,
        "bit-set result differs from its domain contract");
    require(readFlag.bits == 1 && inspectFlag.bits == 4, "operands changed");
    auto saved = FlagSet(2);
    const refused = tryAdmitFlags(8, saved);
    require(!refused && saved.bits == 2, "refusal changed caller state");
    const accepted = tryAdmitFlags(7, saved);
    require(accepted && saved.bits == 7, "accepted value was not published");
}
unittest { exercise(); }
void main()
{
    exercise();
    writeln("Umicom D flags: union 5, intersection 1, repeated flag 1.");
    writeln("Unknown input refused; reflection does not grant permission.");
}
