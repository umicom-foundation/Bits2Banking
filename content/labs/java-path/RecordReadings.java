/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: content/labs/java-path/RecordReadings.java
 *
 * PURPOSE:
 *   Store a validated reading in a Java record and compare its field values.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

public class RecordReadings {
    record Reading(String meter, int units) {
        Reading {
            // Reject an invalid reading before Java assigns the record fields.
            if (meter == null || meter.isBlank()) {
                throw new IllegalArgumentException("Give the meter a name.");
            }
            if (units < 0) {
                throw new IllegalArgumentException("Units must be zero or more.");
            }
        }
    }

    public static void main(String[] args) {
        // Two separate records can represent the same observation.
        Reading first = new Reading("Boiler room", 8);
        Reading second = new Reading("Boiler room", 8);
        System.out.println(first.meter() + " read " + first.units());
        System.out.println("Same reading: " + first.equals(second));

        // Show the exact constructor feedback for a refused value.
        try {
            new Reading("Boiler room", -1);
        } catch (IllegalArgumentException failure) {
            System.out.println(failure.getMessage());
        }
    }
}
