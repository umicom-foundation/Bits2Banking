/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: content/labs/java-path/ShowReadingTimes.java
 *
 * PURPOSE:
 *   Show two distinct instants in a timezone while retaining their order.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.time.Duration;
import java.time.Instant;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.Locale;

public class ShowReadingTimes {
    public static void main(String[] args) {
        // Keep the recorded moments independently of the display zone.
        Instant first = Instant.parse("2025-10-26T00:30:00Z");
        Instant second = Instant.parse("2025-10-26T01:30:00Z");

        // Include the offset so a repeated local hour stays distinguishable.
        ZoneId displayZone = ZoneId.of("Europe/London");
        DateTimeFormatter label = DateTimeFormatter.ofPattern("HH:mm xxx", Locale.ROOT)
                .withZone(displayZone);
        System.out.println(displayZone.getId() + " " + label.format(first));
        System.out.println(displayZone.getId() + " " + label.format(second));
        System.out.println("Elapsed minutes: " + Duration.between(first, second).toMinutes());
    }
}
