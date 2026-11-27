/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReadingArgument.java
 *
 * PURPOSE:
 *   Read a whole-number argument and show whether it reaches a minimum.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public class ReadingArgument {
    public static void main(String[] args) {
        // Refuse a missing value before trying to read the first argument.
        if (args.length != 1) {
            System.err.println("Enter one reading, for example 8.");
            System.exit(2);
            return;
        }

        final int reading;
        try {
            // An argument is text until it has been converted to a number.
            reading = Integer.parseInt(args[0]);
        } catch (NumberFormatException failure) {
            System.err.println("Enter a whole number that fits in an int.");
            System.exit(2);
            return;
        }

        // Reuse the decision from the first if lesson with the value just read.
        if (reading < 10) {
            System.out.println("Review the reading.");
        } else {
            System.out.println("Minimum reached.");
        }
    }
}
