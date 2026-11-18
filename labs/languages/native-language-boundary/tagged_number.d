/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/tagged_number.d
 *
 * PURPOSE:
 *   Separate compile-time field reflection from runtime union selection and output ownership.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

module tagged_number;
import std.stdio : writeln;

enum NumberKind : ubyte { invalid = 0, whole = 1, fractional = 2 }
private union NumberPayload
{
    long wholeValue;
    double fractionalValue;
}
struct TaggedNumber
{
    private NumberKind kind = NumberKind.invalid;
    private NumberPayload payload;

    static TaggedNumber fromWhole(long value) nothrow @nogc
    {
        TaggedNumber candidate;
        candidate.payload.wholeValue = value;
        candidate.kind = NumberKind.whole;
        return candidate;
    }
    static TaggedNumber fromFractional(double value) nothrow @nogc
    {
        TaggedNumber candidate;
        candidate.payload.fractionalValue = value;
        candidate.kind = NumberKind.fractional;
        return candidate;
    }
    bool tryWhole(ref long result) const nothrow @nogc
    {
        if (kind != NumberKind.whole) return false;
        result = payload.wholeValue;
        return true;
    }
    bool tryFractional(ref double result) const nothrow @nogc
    {
        if (kind != NumberKind.fractional) return false;
        result = payload.fractionalValue;
        return true;
    }
}

/* Reflection describes declarations. These checks do not prove which member
 * a particular runtime value contains; only the construction/tag protocol does.
 * No inactive member is evaluated by these compile-time expressions. */
static assert(__traits(hasMember, NumberPayload, "wholeValue"));
static assert(__traits(hasMember, NumberPayload, "fractionalValue"));
static assert(NumberPayload.wholeValue.offsetof == NumberPayload.fractionalValue.offsetof);
static assert(NumberPayload.sizeof >= long.sizeof && NumberPayload.sizeof >= double.sizeof);

private bool exercise() nothrow @nogc
{
    auto value = TaggedNumber.fromWhole(42);
    long wholeResult = -7;
    double fractionalResult = -8.5;
    if (!value.tryWhole(wholeResult) || wholeResult != 42) return false;
    if (value.tryFractional(fractionalResult) || fractionalResult != -8.5) return false;
    value = TaggedNumber.fromFractional(12.5);
    if (!value.tryFractional(fractionalResult) || fractionalResult != 12.5) return false;
    if (value.tryWhole(wholeResult) || wholeResult != 42) return false;

    // D private is module-scoped. This same-module test deliberately forges an
    // unknown tag; normal clients construct values through the static methods.
    value.kind = cast(NumberKind)99;
    if (value.tryWhole(wholeResult) || value.tryFractional(fractionalResult)) return false;
    if (wholeResult != 42 || fractionalResult != 12.5) return false;
    TaggedNumber unselected;
    return !unselected.tryWhole(wholeResult) && !unselected.tryFractional(fractionalResult);
}
unittest { assert(exercise()); }
int main()
{
    if (!exercise()) return 1;
    writeln("Umicom tagged-number checks passed.");
    writeln("Wrong and unknown tags preserved both output values.");
    writeln("Reflection checked fields and overlap, not runtime variant selection.");
    return 0;
}
