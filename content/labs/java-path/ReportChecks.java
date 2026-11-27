/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: content/labs/java-path/ReportChecks.java
 *
 * PURPOSE:
 *   Run independent report checks on virtual threads and print ordered results.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.util.concurrent.Executors;

public class ReportChecks {
    public static void main(String[] args) throws Exception {
        // Each submitted check is independent and returns its own result.
        try (var workers = Executors.newVirtualThreadPerTaskExecutor()) {
            var readings = workers.submit(() -> "Readings: " + (12 + 8));
            var heading = workers.submit(() -> "Heading: Daily report");

            // The report's order belongs to the caller, even if tasks finish out of order.
            System.out.println(heading.get());
            System.out.println(readings.get());
        }
    }
}
