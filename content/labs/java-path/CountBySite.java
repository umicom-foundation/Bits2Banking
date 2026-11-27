/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/CountBySite.java
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

import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class CountBySite {
    record Delivery(String site, int boxes) {}

    public static void main(String[] args) {
        List<Delivery> rows = List.of(new Delivery("North", 4),
            new Delivery("South", 3), new Delivery("North", 2));

        // TreeMap orders the site names, so the displayed report is repeatable.
        Map<String, Integer> totals = new TreeMap<>();
        for (Delivery row : rows) {
            totals.merge(row.site(), row.boxes(), Integer::sum);
        }
        totals.forEach((site, count) -> System.out.println(site + ": " + count));
        // Each delivery contributes once to this independent overall total.
        int total = rows.stream().mapToInt(Delivery::boxes).sum();
        System.out.println("Total: " + total);
    }
}
