/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReadingPeriodReport.java
 *
 * PURPOSE:
 *   Turn a named report period and ordered practice readings into plain text.
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

public final class ReadingPeriodReport {
    private enum Period {
        DAILY,
        WEEKLY
    }

    private record Reading(int sequence, int value) {
    }

    private static Period parsePeriod(String[] args) {
        if (args.length != 1) {
            return null;
        }

        return switch (args[0]) {
            case "daily" -> Period.DAILY;
            case "weekly" -> Period.WEEKLY;
            default -> null;
        };
    }

    private static String buildReport(Period period) {
        // The report owns this list, so it can add and order the selected rows.
        List<Reading> readings = new ArrayList<>(List.of(
                new Reading(11, 7),
                new Reading(4, 3),
                new Reading(2, 7)));
        if (period == Period.WEEKLY) {
            readings.add(new Reading(21, 7));
            readings.add(new Reading(18, 1));
        }

        readings.sort(Comparator.comparingInt(Reading::value)
                .thenComparingInt(Reading::sequence));

        // Assemble the heading and sorted rows before writing to the terminal.
        StringBuilder report = new StringBuilder();
        report.append(period.name()).append(" readings\n");
        report.append("Value Sequence\n");
        for (Reading reading : readings) {
            report.append(reading.value()).append(' ').append(reading.sequence()).append('\n');
        }
        return report.toString();
    }

    public static void main(String[] args) {
        Period period = parsePeriod(args);
        if (period == null) {
            System.err.println("Enter exactly one report period, daily or weekly.");
            System.exit(2);
            return;
        }

        System.out.print(buildReport(period));
    }
}
