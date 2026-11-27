/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/packaged-defaults/PackagedReportDefaults.java
 *
 * PURPOSE:
 *   Read the report defaults packaged beside the Java class in an archive.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package training.report;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.Properties;

public final class PackagedReportDefaults {
    public static void main(String[] args) throws IOException {
        // Resolve packaged data with the class so the launch folder can vary.
        InputStream resource = PackagedReportDefaults.class.getResourceAsStream("defaults.properties");
        if (resource == null) {
            System.err.println("Missing packaged resource training/report/defaults.properties.");
            System.exit(2);
            return;
        }

        Properties defaults = new Properties();
        try (InputStreamReader reader = new InputStreamReader(resource, StandardCharsets.UTF_8)) {
            defaults.load(reader);
        }

        String title = defaults.getProperty("title", "");
        String period = defaults.getProperty("period", "");
        if (title.isBlank() || period.isBlank()) {
            System.err.println("Packaged defaults must give a title and period.");
            System.exit(3);
            return;
        }

        System.out.println("Title " + title);
        System.out.println("Period " + period);
    }
}
