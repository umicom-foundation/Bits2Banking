/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/MinutesReport.java
 *
 * PURPOSE:
 *   Run the referenced Learning Java exercise.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public class MinutesReport {
    static long totalMinutes(int[] durations) {
        long total = 0;
        // Visit each supplied duration once, including when the array is empty.
        for (int duration : durations) {
            total += duration;
        }
        return total;
    }

    public static void main(String[] args) {
        int[] durations = {15, 25, 20};
        long actual = totalMinutes(durations);
        if (actual != 60 || totalMinutes(new int[0]) != 0) {
            throw new IllegalStateException("Unexpected duration total");
        }
        System.out.println("Minutes: " + actual);
    }
}
