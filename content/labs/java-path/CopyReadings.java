/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/CopyReadings.java
 *
 * PURPOSE:
 *   Demonstrate generic copy bounds with a typed source and destination.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import java.util.ArrayList;
import java.util.List;

public class CopyReadings {
    static <T> void appendAll(List<? extends T> source, List<? super T> destination) {
        // The upper bound lets us read a T, and the lower bound lets us add it.
        for (T reading : source) {
            destination.add(reading);
        }
    }

    public static void main(String[] args) {
        // Keep the source separate from the destination so the loop can append safely.
        List<Integer> newReadings = List.of(12, 8);
        List<Number> report = new ArrayList<>();
        report.add(2.5);
        appendAll(newReadings, report);
        System.out.println(report);
        System.out.println(newReadings);
    }
}
