/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/practice/overload_probe.d
 *
 * PURPOSE:
 *   Inspect a declared overload group and check the shape of two proposed calls.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import std.stdio : writeln;

struct Measurement
{
    int degreesC;
}

struct DisplayCheck
{
    static int prepare(int value)
    {
        return value;
    }

    static size_t prepare(string label)
    {
        return label.length;
    }
}

/* Discover named overloads, then ask the compiler to resolve hypothetical
 * calls. __traits(compiles) does not call prepare at runtime. */
alias PrepareOverloads = __traits(getOverloads, DisplayCheck, "prepare");
enum acceptsInteger = __traits(compiles, DisplayCheck.prepare(68));
enum acceptsReading = __traits(compiles, DisplayCheck.prepare(Measurement(68)));

static assert(PrepareOverloads.length == 2);
static assert(acceptsInteger && !acceptsReading);

void main()
{
    writeln("prepare overloads: ", PrepareOverloads.length);
    writeln("integer argument: ", acceptsInteger ? "admitted" : "refused");
    writeln("whole measurement: ", acceptsReading ? "admitted" : "refused");
}
