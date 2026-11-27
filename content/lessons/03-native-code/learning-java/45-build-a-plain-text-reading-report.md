<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/45-build-a-plain-text-reading-report.md

PURPOSE:
Combine an enum and a comparator into a small text-report exercise.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Build a plain-text reading report

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Build a plain-text report with a period heading and one line for each reading. This exercise combines [a named period](43-name-the-report-periods-with-an-enum.md) with [a rule for sorting readings](42-sort-readings-with-comparator.md). The daily sample has three readings. The weekly sample adds two earlier readings.

## 1. Compile and run the daily report

Save [ReadingPeriodReport.java](../../../labs/java-path/ReadingPeriodReport.java) in your practice folder. Open PowerShell there with a JDK that supports Java 21. Run the second command after the first succeeds.

```powershell
javac --release 21 -Xlint:all -Werror ReadingPeriodReport.java
java -cp . ReadingPeriodReport daily
```

```text
DAILY readings
Value Sequence
3 4
7 2
7 11
```

The first line comes from the selected `Period` value. Below the column names, each line contains the value followed by the sequence number. The reading with value 3 comes first. The two readings with value 7 are ordered by sequence, so 2 comes before 11.

## 2. Follow the reading from the list to the report

`parsePeriod` maps the command-line word to a `Period`. `buildReport` takes that value, starts with the daily sample, and adds two more rows for `WEEKLY`. All selected rows are sorted together.

```java
readings.sort(Comparator.comparingInt(Reading::value)
        .thenComparingInt(Reading::sequence));
```

`StringBuilder` holds the text as the method appends the heading, the column names and the sorted rows. Each `\n` starts a new line. `toString()` hands the completed report to the caller, which prints it.

## 3. Check the weekly rows and a usage error

```powershell
java -cp . ReadingPeriodReport weekly
```

```text
WEEKLY readings
Value Sequence
1 18
3 4
7 2
7 11
7 21
```

The new reading with value 1 now comes first. The new reading with value 7 has sequence 21, so it follows the other two readings with that value.

```powershell
java -cp . ReadingPeriodReport monthly
$LASTEXITCODE
```

```text
Enter exactly one report period, daily or weekly.
2
```

An unknown period produces the usage message on the error stream and exit code 2. The program builds a report only after it has a known period. If PowerShell stops after the usage error, enter `$LASTEXITCODE` at the next prompt.

If Java cannot find the class, return to the folder where you compiled `ReadingPeriodReport.java`. If the rows are out of order after an edit, check that the comparator reads `value` before `sequence` and that the loop reads the list after sorting.

[Previous lesson](44-keep-related-counts-in-one-snapshot.md) · [Next lesson](46-read-record-components-at-run-time.md) · [Java course](index.md)
