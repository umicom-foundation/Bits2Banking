/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-ledger/DecimalChecks.java
 *
 * PURPOSE:
 *   Explain decimal representation, numeric equality and explicit rounding through checked examples.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


import java.math.BigDecimal;
import java.math.RoundingMode;

public final class DecimalChecks {
    private static void require(boolean condition, String description) {
        if (!condition) {
            throw new AssertionError(description);
        }
    }

    public static void main(String[] args) {
        BigDecimal amount = new BigDecimal("25.10");
        BigDecimal shorter = new BigDecimal("25.1");
        require(amount.compareTo(shorter) == 0, "Numeric comparison");
        require(!amount.equals(shorter), "Scale is part of equals");
        require(amount.add(new BigDecimal("0.20")).compareTo(new BigDecimal("25.30")) == 0,
                "Exact addition");
        require(amount.toPlainString().equals("25.10"), "The original immutable value remains");

        boolean rejected = false;
        try {
            BigDecimal.ONE.divide(new BigDecimal("3"));
        } catch (ArithmeticException expected) {
            rejected = true;
        }
        require(rejected, "An exact nonterminating division needs a rounding decision");
        require(BigDecimal.ONE.divide(new BigDecimal("3"), 2, RoundingMode.HALF_EVEN)
                .equals(new BigDecimal("0.33")), "Explicit two-place result");
        require(new BigDecimal("1.005").setScale(2, RoundingMode.HALF_EVEN)
                .equals(new BigDecimal("1.00")), "Even tie");
        require(new BigDecimal("1.015").setScale(2, RoundingMode.HALF_EVEN)
                .equals(new BigDecimal("1.02")), "Odd tie");
        System.out.println("Decimal representation and rounding checks passed.");
    }
}

