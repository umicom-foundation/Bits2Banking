<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/15-group-deliveries-with-collections.md

PURPOSE:
  Teach group deliveries with collections with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Group deliveries with collections

Once several deliveries share a site, a count for each site is easier to read than a list of every row. This exercise introduces lists, maps, generics and streams without changing the source delivery rows.

Complete the previous lesson before trying this one. Use the same JDK and a writable practice folder.

## Try it

1. Save `CountBySite.java` and read the three `Delivery` values in `List.of`.
2. Use `List<Delivery>` to read the generic type aloud as ‘a list of deliveries’. `Map<String, Integer>` pairs site names with totals.
3. Trace the calls to `merge`. The second North delivery adds to the existing North total.
4. Compile and run. Compare the grouped results with the separate overall sum calculated by the stream.

## Example files

### CountBySite.java

[Open CountBySite.java](../../../labs/java-path/CountBySite.java)

~~~java
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
~~~

## Run it

~~~text
javac CountBySite.java
java -cp . CountBySite
~~~

The program output to check is shown below.

~~~text
North: 6
South: 3
Total: 9
~~~

## Read the result

A `TreeMap` keeps the keys in sorted order. The stream visits the original list, takes each box count and adds them. `Delivery::boxes` means ‘call the boxes accessor for this delivery’. A stream pipeline has an output here when `sum()` runs.

## Practise

Add a second South record with two boxes. Expect North 6, South 5 and total 11. Keep the result order the same.

## Fix a problem

If the overall total and grouped rows disagree, list the three deliveries and inspect where the repeated site is combined. `put` would replace a total when the key repeats.

## Reference

- [Collections and streams](https://dev.java/learn/api/collections-and-streams/)

[Previous · Separate a record and its writer](14-separate-a-record-and-its-writer.md) · [Next · Read a file and explain errors](16-read-a-file-and-explain-errors.md)
