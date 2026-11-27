/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReadShiftLog.java
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
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class ReadShiftLog {
    static void report(Path file) throws IOException {
        long total = 0;
        // The language closes the reader even when parsing or reading fails.
        try (var input = Files.newBufferedReader(file, StandardCharsets.UTF_8)) {
            for (String line; (line = input.readLine()) != null;) {
                total += Integer.parseInt(line.strip());
            }
        }
        System.out.println("Total: " + total);
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java ReadShiftLog FILE");
            System.exit(2);
        }
        try {
            report(Path.of(args[0]));
        } catch (NumberFormatException error) {
            System.err.println("Input must contain one integer on each line.");
            System.exit(1);
        } catch (IOException error) {
            System.err.println("Could not read the input file.");
            System.exit(1);
        }
    }
}
