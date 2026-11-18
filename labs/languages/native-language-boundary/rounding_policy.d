/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/rounding_policy.d
 *
 * PURPOSE:
 *   Compare D numeric rounding policies and preserve caller state when an integer conversion is refused.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module rounding_policy;
import std.math.rounding : trunc, floor, ceil, round;
import std.math.traits : isFinite;
import std.stdio : writeln;

bool tryTruncateInt(double value, ref int destination) @safe pure nothrow @nogc
{
    // Admit the original value, not merely its later truncated result.
    // This conservative contract is explicit and avoids an unchecked cast.
    if (!isFinite(value) || value < int.min || value > int.max) return false;
    destination = cast(int)value;
    return true;
}
void require(bool condition, string description)
{
    if (!condition) throw new Exception(description);
}
void checkRounding()
{
    immutable double[6] values = [2.5, 3.5, -2.5, -3.5, 1.75, -1.75];
    immutable int[6] towardZero = [2, 3, -2, -3, 1, -1];
    immutable int[6] downward = [2, 3, -3, -4, 1, -2];
    immutable int[6] upward = [3, 4, -2, -3, 2, -1];
    immutable int[6] nearestAway = [3, 4, -3, -4, 2, -2];
    foreach (i, value; values) {
        require(cast(int)value == towardZero[i], "bounded cast truncates");
        require(trunc(value) == towardZero[i], "explicit truncation");
        require(floor(value) == downward[i], "floor");
        require(ceil(value) == upward[i], "ceiling");
        require(round(value) == nearestAway[i], "halfway rounds away from zero");
    }
    int destination = 77;
    bool accepted = tryTruncateInt(-3.5, destination);
    require(accepted && destination == -3, "small finite input");
    foreach (bad; [double.nan, double.infinity, -double.infinity, 1.0e100,
            2147483647.5, -2147483648.5]) {
        destination = 77;
        accepted = tryTruncateInt(bad, destination);
        require(!accepted && destination == 77, "refusal preserves caller state");
    }
    accepted = tryTruncateInt(cast(double)int.max, destination);
    require(accepted && destination == int.max, "upper endpoint");
    accepted = tryTruncateInt(cast(double)int.min, destination);
    require(accepted && destination == int.min, "lower endpoint");
}
unittest { checkRounding(); }
void main()
{
    checkRounding();
    writeln("Umicom D rounding: six rows checked.");
    writeln("Refused conversions preserve the caller's integer.");
}
