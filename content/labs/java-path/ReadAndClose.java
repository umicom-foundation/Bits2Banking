/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReadAndClose.java
 *
 * PURPOSE:
 *   Show the order and causes reported when Java closes two resources.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.io.IOException;

public class ReadAndClose {
    // A controlled stand-in lets us practise close failures without touching files.
    static final class PracticeResource implements AutoCloseable {
        private final String name;
        private final boolean failOnClose;

        PracticeResource(String name, boolean failOnClose) {
            this.name = name;
            this.failOnClose = failOnClose;
            System.out.println("Open " + name);
        }

        void check(boolean failRead) throws IOException {
            if (failRead) {
                throw new IOException("Read " + name + " failed");
            }
            System.out.println("Read " + name);
        }

        @Override
        public void close() throws IOException {
            System.out.println("Close " + name);
            if (failOnClose) {
                throw new IOException("Close " + name + " failed");
            }
        }
    }

    public static void main(String[] args) {
        String mode = args.length == 0 ? "read" : args[0];
        boolean failRead = mode.equals("read");
        boolean failClose = !mode.equals("ok");
        // Java closes in reverse order even when the read or a close throws.
        try (var input = new PracticeResource("input", false);
             var report = new PracticeResource("report", failClose)) {
            input.check(failRead);
            report.check(false);
        } catch (IOException failure) {
            System.out.println("Main cause: " + failure.getMessage());
            // Keep later close errors visible without losing the main cause.
            for (Throwable later : failure.getSuppressed()) {
                System.out.println("Later cause: " + later.getMessage());
            }
            return;
        }
        System.out.println("Finished");
    }
}
