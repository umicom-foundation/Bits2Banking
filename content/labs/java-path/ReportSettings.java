/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ReportSettings.java
 *
 * PURPOSE:
 *   Teach how to load and check local report settings before using them.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Properties;

public class ReportSettings {
    public static void main(String[] args) {
        System.exit(run(args));
    }

    private static int run(String[] args) {
        if (args.length != 1) {
            return fail("Give the path to one settings file.");
        }

        // Read with an explicit encoding and close the file on every exit path.
        Properties settings = new Properties();
        try (BufferedReader reader = Files.newBufferedReader(
                Path.of(args[0]), StandardCharsets.UTF_8)) {
            settings.load(reader);
        } catch (IOException | IllegalArgumentException problem) {
            return fail("Cannot read the settings file.");
        }

        // Check that both values are usable before printing the report heading.
        String title = settings.getProperty("title", "").strip();
        if (title.isEmpty()) {
            return fail("Give the report a title.");
        }

        int rows;
        try {
            rows = Integer.parseInt(settings.getProperty("rows", "").strip());
        } catch (NumberFormatException problem) {
            return fail("Set rows to a whole number from 1 to 20.");
        }
        if (rows < 1 || rows > 20) {
            return fail("Set rows to a whole number from 1 to 20.");
        }

        System.out.println(title);
        System.out.println("Rows to show: " + rows);
        return 0;
    }

    private static int fail(String message) {
        // A separate error stream keeps failed runs out of report output.
        System.err.println(message);
        return 1;
    }
}
