/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/LimitChecks.java
 *
 * PURPOSE:
 *   Run the referenced Learning Java exercise.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public class LimitChecks {
    static boolean withinLimit(int value, int limit) {
        // Name the two comparisons so the debugger can show each decision.
        boolean nonNegative = value >= 0;
        boolean atOrBelow = value <= limit;
        return nonNegative && atOrBelow;
    }

    static void check(boolean actual, boolean expected, String name) {
        if (actual != expected) {
            throw new IllegalStateException(name + ": expected " + expected + ", got " + actual);
        }
    }

    public static void main(String[] args) {
        check(withinLimit(5, 5), true, "upper boundary");
        check(withinLimit(6, 5), false, "above boundary");
        check(withinLimit(-1, 5), false, "negative value");
        System.out.println("3 checks passed");
    }
}
