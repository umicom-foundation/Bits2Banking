/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ShiftTotal.java
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

public class ShiftTotal {
    public static void main(String[] args) {
        int total = 0;
        // Each shift adds two units. Printing happens after all three shifts.
        for (int shift = 1; shift <= 3; shift++) {
            total += 2;
        }
        if (total >= 6) {
            System.out.println("Batch complete");
        }
        System.out.println("Units: " + total);
    }
}
