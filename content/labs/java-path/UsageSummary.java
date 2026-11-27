/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/UsageSummary.java
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

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class UsageSummary {
    static int summarize(Path file) throws IOException {
        byte[] bytes;
        // Read one byte past the teaching limit so a full prefix cannot pass.
        try (var input = Files.newInputStream(file)) {
            bytes = input.readNBytes(65);
        }
        if (bytes.length == 0 || bytes.length > 64) {
            throw new IllegalArgumentException("Invalid usage data");
        }
        int total = 0;
        int value = 0;
        int digits = 0;
        // Define the portable file format with ASCII bytes and LF line breaks.
        for (byte current : bytes) {
            if (current >= '0' && current <= '9' && digits < 2) {
                value = value * 10 + current - '0';
                digits++;
            } else if (current == '\n' && digits != 0) {
                total += value;
                value = 0;
                digits = 0;
            } else {
                throw new IllegalArgumentException("Invalid usage data");
            }
        }
        if (digits != 0) {
            throw new IllegalArgumentException("Invalid usage data");
        }
        return total;
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: provide one input file");
            System.exit(2);
        }
        try {
            System.out.println("Total: " + summarize(Path.of(args[0])));
        } catch (IllegalArgumentException error) {
            System.err.println("Invalid usage data");
            System.exit(1);
        } catch (IOException error) {
            System.err.println("Could not read usage data");
            System.exit(1);
        }
    }
}
