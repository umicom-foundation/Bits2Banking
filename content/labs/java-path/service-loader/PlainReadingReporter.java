/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/service-loader/PlainReadingReporter.java
 *
 * PURPOSE:
 *   Provide one concrete formatter for the service-loader lesson.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package learning.readings;

public final class PlainReadingReporter implements ReadingReporter {
    @Override
    public String summarize(int total) {
        // Keep formatting in the replaceable provider where it can evolve.
        return "Total readings: " + total;
    }
}
