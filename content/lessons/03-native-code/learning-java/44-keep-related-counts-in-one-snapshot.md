<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/44-keep-related-counts-in-one-snapshot.md

PURPOSE:
Use the same object lock to update two counts and copy both into an immutable record.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Keep related counts in one snapshot

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Two workers can record reports at the same time. In this exercise every report has two pages. Keep the report count and the page count together so that a reader always sees a pair that obeys that rule.

Use a JDK that supports Java 21 and your PowerShell practice folder. [Keep a reading in a record](36-keep-a-reading-in-a-record.md) introduces records. [Run independent checks with virtual threads](33-run-independent-checks-with-virtual-threads.md) introduces a different exercise where each task can work on its own.

## 1. Run the two workers

Save [ReportCounts.java](../../../labs/java-path/ReportCounts.java) in the practice folder. Open PowerShell there and run the compiler. After compilation succeeds, run the program.

```powershell
javac --release 21 -Xlint:all -Werror ReportCounts.java
java -cp . ReportCounts
```

```text
Sample consistent = true
Final reports = 5, pages = 10
Opening snapshot still shows 0 reports and 0 pages.
```

The first worker records two reports and the second records three. Both call the same `ReportCounts` object. That object owns both `private` counts.

## 2. Use the same lock for updates and snapshots

```java
synchronized void recordReport() {
    // The same object lock protects both changes in one operation.
    reports++;
    pages += PAGES_PER_REPORT;
}

synchronized Snapshot snapshot() {
    // Copy both values while the owner holds the lock used by writers.
    return new Snapshot(reports, pages);
}
```

A `synchronized` instance method uses the lock on the object you call it on. When one worker updates the counts, other threads calling either method on that object wait. The snapshot holds the same lock while copying both counts. The two values therefore describe the same completed updates.

A snapshot is a copy of the two numbers at one moment. Its record holds two `int` components, which keep the same values for the life of that snapshot. The opening copy still shows zero after both workers finish.

## 3. Wait for both workers before reading the final total

The first sample can capture different totals depending on how much work has finished. The program prints whether its two values agree. `join()` waits for a worker to finish. After both joins, the final snapshot always shows five reports and ten pages.

Change the first worker’s count from `2` to `0` and the second worker’s count from `3` to `1`. Compile and run again. The sample still shows `true` and the opening snapshot still shows zero. The line for completed work now reads as follows.

```text
Final reports = 1, pages = 2
```

If the sample is inconsistent after an edit, check that the update and snapshot still use `synchronized` on the same object and that one call to `recordReport()` still adds both values. If Java cannot find `ReportCounts`, check that you are in the folder where the compiler wrote the class.

## 4. Carry the design over to C

A C implementation with a thread library can keep both counters in a `struct` and protect them with one mutex. A mutex lets one thread at a time enter the code that uses the shared fields. Acquire it before changing both counts or copying both into a snapshot struct. Release it before printing the copy. The copy can be read without locking the original as long as the copy itself has no concurrent writers.

[Java locks and synchronization](https://docs.oracle.com/javase/specs/jls/se21/html/jls-17.html#jls-17.1) · [C23 working draft, mutex functions](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf#page=411)

[Previous lesson](43-name-the-report-periods-with-an-enum.md) · [Next lesson](45-build-a-plain-text-reading-report.md) · [Java course](index.md)
