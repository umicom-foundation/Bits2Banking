/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/SortReadings.java
 *
 * PURPOSE:
 *   Sort practice readings by value, using the sequence number to break ties.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public final class SortReadings {
    record Reading(int sequence, int value) {
    }

    static List<Reading> sortedCopy(List<Reading> readings) {
        // The report orders its own list so the original input keeps its order.
        List<Reading> ordered = new ArrayList<>(readings);
        Comparator<Reading> byValueThenSequence = Comparator.comparingInt(Reading::value)
                .thenComparingInt(Reading::sequence);
        ordered.sort(byValueThenSequence);
        return ordered;
    }

    public static void main(String[] args) {
        List<Reading> readings = List.of(
                new Reading(11, 7),
                new Reading(4, 3),
                new Reading(2, 7));

        System.out.println("Value Sequence");
        for (Reading reading : sortedCopy(readings)) {
            System.out.println(reading.value() + " " + reading.sequence());
        }
    }
}
