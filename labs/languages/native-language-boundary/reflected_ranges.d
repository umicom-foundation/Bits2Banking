/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/reflected_ranges.d
 *
 * PURPOSE:
 *   Teach compile-time metadata inspection and runtime validation as separate operations.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module reflected_ranges;
import std.stdio : writeln;
import std.traits : FieldNameTuple, FieldTypeTuple, getUDAs;

struct InclusiveRange { long minimum; long maximum; }
struct PreviewOptions
{
    @InclusiveRange(1, 8192) uint width;
    @InclusiveRange(1, 8192) uint height;
    @InclusiveRange(1, 1000) uint steps;
}

/* An annotation describes a rule; it does not enforce the rule by itself.
 * Reflection selects fields at compilation. The generated comparisons check
 * the particular object's values each time the function is called. */
string firstInvalidField(T)(ref const T value)
{
    static foreach (index, name; FieldNameTuple!T) {
        {
            alias Field = FieldTypeTuple!T[index];
            static assert(is(Field == uint) || is(Field == long),
                "This teaching policy accepts only uint and long fields");
            enum rules = getUDAs!(__traits(getMember, T, name), InclusiveRange);
            static assert(rules.length == 1,
                "Each field must have exactly one InclusiveRange annotation");
            static assert(rules[0].minimum <= rules[0].maximum,
                "The inclusive minimum must not exceed the maximum");
            /* Every uint and long value fits in D's signed 64-bit long.
             * Do not extend this cast to ulong without another range policy. */
            const long number = cast(long)__traits(getMember, value, name);
            if (number < rules[0].minimum || number > rules[0].maximum)
                return name;
        }
    }
    return "";
}

unittest
{
    auto good = PreviewOptions(640, 360, 20);
    assert(firstInvalidField(good) == "");
    auto low = PreviewOptions(0, 360, 20);
    assert(firstInvalidField(low) == "width");
    auto high = PreviewOptions(640, 8193, 20);
    assert(firstInvalidField(high) == "height");
    auto last = PreviewOptions(640, 360, 1001);
    assert(firstInvalidField(last) == "steps");
    auto boundaries = PreviewOptions(8192, 1, 1000);
    assert(firstInvalidField(boundaries) == "");
    auto twoErrors = PreviewOptions(0, 0, 20);
    assert(firstInvalidField(twoErrors) == "width");
    assert(good.width == 640 && good.height == 360 && good.steps == 20);
}

void main()
{
    auto good = PreviewOptions(640, 360, 20);
    auto bad = PreviewOptions(0, 360, 20);
    writeln("Valid object: ", firstInvalidField(good).length == 0);
    writeln("First invalid field: ", firstInvalidField(bad));
    writeln("Original values remain: ", good.width, " x ", good.height,
        ", steps ", good.steps);
    writeln("Field ranges do not establish total memory cost or permission to run.");
}
