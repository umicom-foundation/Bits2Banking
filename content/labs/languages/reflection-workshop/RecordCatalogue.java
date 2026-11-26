/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/RecordCatalogue.java
 *
 * PURPOSE:
 *   Read Java record components and accessor names through runtime reflection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.lang.reflect.RecordComponent;

public final class RecordCatalogue {
    record Reading(String station, int degreesC) {}

    public static void main(String[] args) {
        // The record's Class object carries its component names and types.
        // No Reading instance or accessor call is needed for these facts.
        for (RecordComponent component : Reading.class.getRecordComponents()) {
            System.out.println(component.getName() + ": "
                    + component.getType().getSimpleName() + ", accessor "
                    + component.getAccessor().getName());
        }

        // An ordinary class demonstrates a different metadata category.
        System.out.println("String is a record: " + String.class.isRecord());
    }
}
