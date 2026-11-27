/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/service-loader/ReportSample.java
 *
 * PURPOSE:
 *   Run the report example with or without an installed provider.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package learning.readings;

import java.util.ServiceLoader;

public final class ReportSample {
    public static void main(String[] args) {
        // Look for a provider through the service contract shared at build time.
        var reporter = ServiceLoader.load(ReadingReporter.class).findFirst();
        if (reporter.isEmpty()) {
            System.out.println("No reading reporter is installed.");
            return;
        }

        // The provider formats the total that the application already knows.
        System.out.println(reporter.get().summarize(20));
    }
}
