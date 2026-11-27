/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/DeliveryReport.java
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

public class DeliveryReport {
    record Delivery(String site, int boxes) {
        Delivery {
            // Validation belongs at the point where a delivery is created.
            if (site == null || site.isBlank() || boxes < 0) {
                throw new IllegalArgumentException("Invalid delivery");
            }
        }
    }

    interface LineWriter {
        void write(String line);
    }

    static final class ConsoleWriter implements LineWriter {
        public void write(String line) {
            System.out.println(line);
        }
    }

    static void report(Delivery delivery, LineWriter writer) {
        // The reporting method can use any writer that fulfils the contract.
        writer.write(delivery.site() + ": " + delivery.boxes());
    }

    public static void main(String[] args) {
        report(new Delivery("North", 4), new ConsoleWriter());
    }
}
