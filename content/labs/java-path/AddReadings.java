/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/AddReadings.java
 *
 * PURPOSE:
 *   Make one Java calculation easy to find and inspect in JVM bytecode.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
public class AddReadings {
    public static int add(int first, int second) {
        // Keep the calculation separate so it has its own bytecode listing.
        return first + second;
    }

    public static void main(String[] args) {
        // Use fixed practice inputs so the output and the inspected method agree.
        System.out.println(add(12, 8));
    }
}
