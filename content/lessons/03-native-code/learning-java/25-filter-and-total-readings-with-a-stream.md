# Filter and total readings with a stream

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Choose the readings from one site that meet a minimum. Add their units with a loop, then check that a Java stream gives the same answer. Read [Group deliveries with collections](15-group-deliveries-with-collections.md) first if working with a list is unfamiliar.

## Run the example

1. Save [FilteredReadingTotal.java](../../../labs/java-path/FilteredReadingTotal.java) in a practice folder.
2. Open your terminal in that folder. Compile and run it with the JDK from the course.
3. Compare both totals with the expected output.

```powershell
javac --release 21 FilteredReadingTotal.java
java FilteredReadingTotal
```

Expected output

```text
North total: 32
West total: 0
```

## First read the loop

```text
Set total to zero
For each reading
    If the site matches and the units meet the minimum
        Add the units to total
Return total
```

The north readings are 12, 7 and 20. At a minimum of 10, the loop keeps 12 and 20. The list has no west readings, so the west total starts and ends at zero.

## Then read the stream

1. `stream()` starts a series of operations on the list.
2. Each `filter` keeps the items for which its rule returns `true`. Read `reading -> ...` as “for this reading, check the rule after the arrow”.
3. `mapToInt(Reading::units)` takes the units from each remaining reading. The method reference `Reading::units` means “call the `units` accessor”.
4. `sum()` adds those values. It uses zero when no reading matched. It finishes this stream, and the original list stays available for another calculation.

## Practise and recover

1. Change `minimum` from `10` to `7`. Compile and run again. The north total becomes 39 and the west total stays zero.
2. Change only the stream cutoff to `>` for this trial. Compile and run. The existing comparison reports a difference because the two methods now disagree about the reading at exactly 7. Restore `>=` and rerun.
3. Use the loop as a second check when changing a report rule. Small examples near the cutoff make it easier to see what each implementation is doing.

A native Umicom report can keep the same two rules in C23 or Umicom C. The loop and the stream printout give you values to compare when verifying the new implementation.

[Return to Learning Java](index.md) · [Test a local Java HTTP route](24-test-a-local-java-http-route.md) · [Java Stream API](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/util/stream/Stream.html)
