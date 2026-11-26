/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/practice/RecordUnitLookup.java
 *
 * PURPOSE:
 *   Observe which record annotations remain visible through standard Java reflection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.lang.reflect.RecordComponent;

public final class RecordUnitLookup {
    @Retention(RetentionPolicy.RUNTIME)
    @Target(ElementType.RECORD_COMPONENT)
    @interface DisplayUnit {
        String value();
    }

    @Retention(RetentionPolicy.CLASS)
    @Target(ElementType.RECORD_COMPONENT)
    @interface BuildNote {
        String value();
    }

    record Reading(@DisplayUnit("Celsius") int degreesC,
                   @BuildNote("batch sample count") int samples) {}

    public static void main(String[] args) {
        for (RecordComponent component : Reading.class.getRecordComponents()) {
            // Query each component's declaration without making a Reading.
            if (component.getName().equals("degreesC")) {
                DisplayUnit unit = component.getAnnotation(DisplayUnit.class);
                System.out.println("degreesC runtime unit: "
                        + (unit == null ? "absent" : unit.value()));
            } else if (component.getName().equals("samples")) {
                BuildNote note = component.getAnnotation(BuildNote.class);
                System.out.println("samples runtime build note: "
                        + (note == null ? "absent" : note.value()));
            }
        }
    }
}
