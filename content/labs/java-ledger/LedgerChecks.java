/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-ledger/LedgerChecks.java
 *
 * PURPOSE:
 *   Check the numeric invariant of the existing Java journal example and expose its limits.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


import java.math.BigDecimal;
import java.util.List;

public final class LedgerChecks {
    private static void require(boolean condition, String description) {
        if (!condition) {
            throw new AssertionError(description);
        }
    }

    public static void main(String[] args) {
        var debit = new LedgerDemo.Posting("Cash", new BigDecimal("25.10"), BigDecimal.ZERO);
        var credit = new LedgerDemo.Posting("Income", BigDecimal.ZERO, new BigDecimal("25.1"));
        require(LedgerDemo.IsBalanced(List.of(debit, credit)), "Equal values with different scales");
        require(!LedgerDemo.IsBalanced(List.of(debit)), "One unmatched debit");
        require(!LedgerDemo.IsBalanced(List.of(debit, credit, debit)), "Duplicated debit");
        require(LedgerDemo.IsBalanced(List.of(credit, debit)), "Order must not change totals");

        // This is deliberately a narrow numeric example. Empty and negative
        // journals expose the difference between balancing and business validity.
        require(LedgerDemo.IsBalanced(List.of()), "An empty sum is numerically balanced");
        require(LedgerDemo.IsBalanced(List.of(
            new LedgerDemo.Posting("Cash", new BigDecimal("-2.00"), BigDecimal.ZERO),
            new LedgerDemo.Posting("Income", BigDecimal.ZERO, new BigDecimal("-2.00")))),
            "Negative equal totals are still equal");
        System.out.println("Journal arithmetic checks passed; business validation is outside this example.");
    }
}

