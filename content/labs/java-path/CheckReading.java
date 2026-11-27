/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/CheckReading.java
 *
 * PURPOSE:
 *   Decide whether a meter reading reaches a minimum.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public class CheckReading {
    public static void main(String[] args) {
        int reading = 8;
        int minimum = 10;

        // A value equal to the minimum has already reached it.
        if (reading < minimum) {
            System.out.println("Review the reading.");
        } else {
            System.out.println("Minimum reached.");
        }
    }
}
