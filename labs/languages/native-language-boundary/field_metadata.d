/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/field_metadata.d
 *
 * PURPOSE:
 *   Inspect declared teaching-field labels at compile time without changing their stored values.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

module field_metadata;
import std.stdio : writeln;
import std.traits : FieldNameTuple, FieldTypeTuple, getUDAs;

struct Label { string text; }
struct AccountSnapshot {
    @Label("Account number") uint account;
    @Label("Balance in minor units") long balanceMinor;
}

/* Each generated block has its own scope because static foreach expands at
 * compile time. A missing label rejects this schema before the program runs. */
void describe(T)()
{
    static foreach (index, name; FieldNameTuple!T) {
        {
            enum labels = getUDAs!(__traits(getMember, T, name), Label);
            static assert(labels.length == 1, "Each field needs exactly one Label");
            alias Field = FieldTypeTuple!T[index];
            writeln(name, ": ", Field.stringof, " => ", labels[0].text);
        }
    }
}

unittest
{
    static assert(FieldNameTuple!AccountSnapshot.length == 2);
    static assert(getUDAs!(AccountSnapshot.account, Label)[0].text == "Account number");
    static assert(is(FieldTypeTuple!AccountSnapshot[1] == long));
}

void main()
{
    auto snapshot = AccountSnapshot(17, 1250);
    describe!AccountSnapshot();
    assert(snapshot.account == 17 && snapshot.balanceMinor == 1250);
    writeln("Values remain unchanged: ", snapshot.account, ", ", snapshot.balanceMinor);
}
