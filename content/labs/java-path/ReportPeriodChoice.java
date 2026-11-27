/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReportPeriodChoice.java
 *
 * PURPOSE:
 *   Translate a command-line word into one of two named report periods.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public final class ReportPeriodChoice {
    private enum Period {
        DAILY,
        WEEKLY
    }

    private static Period parsePeriod(String[] args) {
        if (args.length != 1) {
            return null;
        }

        // Translate input text at the boundary so the report receives a Period.
        return switch (args[0]) {
            case "daily" -> Period.DAILY;
            case "weekly" -> Period.WEEKLY;
            default -> null;
        };
    }

    public static void main(String[] args) {
        Period period = parsePeriod(args);
        if (period != null) {
            System.out.println(period.name());
            return;
        }

        System.err.println("Enter exactly one report period, daily or weekly.");
        System.exit(2);
    }
}
