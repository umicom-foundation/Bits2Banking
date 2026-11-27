/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReadingTotal.java
 *
 * PURPOSE:
 *   Teach how one Java class keeps a reading total valid after each update.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public final class ReadingTotal {
    // This class controls updates to the total through add.
    private int total = 0;

    public boolean add(int reading) {
        // Keep the old total if the reading is invalid or the result will not fit.
        if (reading < 0 || reading > Integer.MAX_VALUE - total) {
            return false;
        }
        total += reading;
        return true;
    }

    public int value() {
        // Callers can read the current result without changing it.
        return total;
    }

    public static void main(String[] args) {
        // Start a new total and check both a routine update and a refusal.
        ReadingTotal report = new ReadingTotal();
        report.add(12);
        report.add(8);
        System.out.println("Total: " + report.value());
        System.out.println("Accepted negative reading: " + report.add(-3));
        System.out.println("Total after refusal: " + report.value());
    }
}
