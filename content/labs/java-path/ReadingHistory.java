/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: content/labs/java-path/ReadingHistory.java
 *
 * PURPOSE:
 *   Show how a growing list and a saved report can coexist.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.util.ArrayList;
import java.util.List;

public class ReadingHistory {
    public static void main(String[] args) {
        // Keep routine additions in arrival order.
        List<Integer> readings = new ArrayList<>();
        readings.add(12);
        readings.add(8);

        // A report holds the readings available when it was taken.
        List<Integer> morningReport = List.copyOf(readings);
        readings.add(15);

        System.out.println("Morning report: " + morningReport);
        System.out.println("Current readings: " + readings);
    }
}
