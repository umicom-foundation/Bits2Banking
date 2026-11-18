/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/budget_invariant.d
 *
 * PURPOSE:
 *   Separate D object invariants from runtime admission of a bounded request budget.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module budget_invariant;
import std.stdio : writeln;

struct RequestBudget
{
    private uint remaining_;
    enum uint maximum = 1024;

    // Inspect backing state directly: calling public methods here can recurse
    // through invariant checking. This assertion diagnoses programmer defects.
    invariant() { assert(remaining_ <= maximum); }

    @property uint remaining() const { return remaining_; }

    bool tryReset(uint requested)
    {
        // This branch is input admission even when contract checks are disabled.
        if (requested > maximum) return false;
        remaining_ = requested;
        return true;
    }
    bool tryConsume(uint count)
    {
        if (count > remaining_) return false;
        remaining_ -= count;
        return true;
    }
}

unittest
{
    RequestBudget budget;
    assert(budget.remaining == 0);
    assert(budget.tryReset(5));
    assert(budget.tryConsume(2));
    assert(budget.remaining == 3);
    assert(!budget.tryConsume(4));
    assert(!budget.tryReset(1025));
    assert(budget.remaining == 3);
    assert(budget.tryConsume(3));
    assert(budget.tryConsume(0));
    assert(budget.remaining == 0);
    assert(budget.tryReset(RequestBudget.maximum));
    assert(budget.tryConsume(RequestBudget.maximum));
}
int main()
{
    RequestBudget budget;
    // Do not hide required mutations inside assert: assertions may be disabled.
    if (!budget.tryReset(5) || !budget.tryConsume(2)) return 1;
    if (budget.tryConsume(4) || budget.tryReset(1025) || budget.remaining != 3) return 1;
    writeln("Checked admission preserved ", budget.remaining, "; invariant documents 0..1024.");
    return 0;
}
