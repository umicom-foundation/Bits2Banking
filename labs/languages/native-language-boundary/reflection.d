/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/reflection.d
 *
 * PURPOSE:
 *   Inspect an original media-options record using D compile-time field reflection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import std.stdio : writeln;
import std.traits : FieldNameTuple;
struct MediaOptions
{
    uint width = 640;
    uint height = 360;
    bool preview = true;
}
void main()
{
    MediaOptions options;
    static foreach (name; FieldNameTuple!MediaOptions)
        writeln(name, " = ", __traits(getMember, options, name));
}
