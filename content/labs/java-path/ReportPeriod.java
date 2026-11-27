/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReportPeriod.java
 *
 * PURPOSE:
 *   Select a report heading from one command-line choice.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public class ReportPeriod {
    public static void main(String[] args) {
        String heading = "";

        // Read the first argument only when the person supplied exactly one.
        if (args.length == 1) {
            // Each recognised choice supplies the same type of value.
            heading = switch (args[0]) {
                case "daily" -> "Daily report.";
                case "weekly" -> "Weekly report.";
                default -> "";
            };
        }

        // Give missing and unknown choices the same usage message.
        if (heading.isEmpty()) {
            System.err.println("Choose daily or weekly.");
            System.exit(2);
            return;
        }
        System.out.println(heading);
    }
}
