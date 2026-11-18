/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/conditional_selection.d
 *
 * PURPOSE:
 *   Distinguish conditional expressions from by-value argument evaluation using bounded observable counters.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

module conditional_selection;
import std.stdio : writeln;

private int probe(int value, ref uint calls) @safe nothrow @nogc
{
    ++calls;
    return value;
}
private bool probeCondition(bool choice, ref uint calls) @safe nothrow @nogc
{
    ++calls;
    return choice;
}
private int chooseValues(bool choice, int leftValue, int rightValue) @safe nothrow @nogc
{
    return choice ? leftValue : rightValue;
}
private void checkSelection(bool choice) @safe
{
    uint leftCalls, rightCalls, conditionCalls;
    int expected;
    if (choice) expected = 11; else expected = 22;
    // Only the chosen operand executes; both operands still need valid types.
    int selected = probeCondition(choice, conditionCalls)
        ? probe(11, leftCalls) : probe(22, rightCalls);
    assert(selected == expected && conditionCalls == 1);
    if (choice) assert(leftCalls == 1 && rightCalls == 0);
    else assert(leftCalls == 0 && rightCalls == 1);

    leftCalls = rightCalls = conditionCalls = 0;
    // Ordinary parameters receive computed values. Do not confuse them with
    // lazy parameters or delegates, which have different evaluation contracts.
    selected = chooseValues(probeCondition(choice, conditionCalls),
        probe(11, leftCalls), probe(22, rightCalls));
    assert(selected == expected);
    assert(leftCalls == 1 && rightCalls == 1 && conditionCalls == 1);
}
unittest { checkSelection(true); checkSelection(false); }
void main() @safe
{
    checkSelection(true);
    checkSelection(false);
    writeln("Umicom D selective expression and eager argument checks passed.");
}
