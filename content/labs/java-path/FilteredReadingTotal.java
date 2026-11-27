/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/FilteredReadingTotal.java
 *
 * PURPOSE:
 *   Compare a loop and a sequential stream using the same ordinary readings.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import java.util.List;

public class FilteredReadingTotal {
    record Reading(String site, int units) {}

    static int loopTotal(List<Reading> readings, String site, int minimumUnits) {
        int total = 0;
        for (Reading reading : readings) {
            // Apply the two rules before adding a reading to the total.
            if (site.equals(reading.site()) && reading.units() >= minimumUnits) {
                total += reading.units();
            }
        }
        return total;
    }

    static int streamTotal(List<Reading> readings, String site, int minimumUnits) {
        // Use the same rules and start a fresh pipeline each time we calculate a total.
        return readings.stream()
                .filter(reading -> site.equals(reading.site()))
                .filter(reading -> reading.units() >= minimumUnits)
                .mapToInt(Reading::units)
                .sum();
    }

    public static void main(String[] args) {
        var readings = List.of(new Reading("north", 12), new Reading("south", 9),
                new Reading("north", 7), new Reading("north", 20));
        int minimum = 10;
        int north = streamTotal(readings, "north", minimum);
        int west = streamTotal(readings, "west", minimum);
        // The loop supplies an independent check for an ordinary and an empty result.
        if (north != loopTotal(readings, "north", minimum) || west != loopTotal(readings, "west", minimum)) {
            throw new IllegalStateException("The loop and stream totals differ");
        }
        System.out.println("North total: " + north);
        System.out.println("West total: " + west);
    }
}
