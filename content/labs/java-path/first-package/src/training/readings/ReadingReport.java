/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/first-package/src/training/readings/ReadingReport.java
 *
 * PURPOSE:
 *   Run a Java entry point that uses a second type from the same package.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package training.readings;

public class ReadingReport {
    public static void main(String[] args) {
        // A fixed practice reading keeps this example about file and package names.
        Reading reading = new Reading("North Office", 8);
        System.out.println(reading.site() + " read " + reading.units());
    }
}
