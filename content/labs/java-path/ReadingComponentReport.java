/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReadingComponentReport.java
 *
 * PURPOSE:
 *   Read the declared components of a known Java record through reflection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.lang.reflect.RecordComponent;

public final class ReadingComponentReport {
    public record Reading(int minute, int value) {
    }

    public static void main(String[] args) throws ReflectiveOperationException {
        Reading reading = new Reading(15, 42);

        // Ask the Java runtime for the components in the record's declared order.
        for (RecordComponent component : Reading.class.getRecordComponents()) {
            // The component supplies its existing public accessor, such as minute().
            Object value = component.getAccessor().invoke(reading);
            System.out.println(component.getName() + " = " + value);
        }
    }
}
