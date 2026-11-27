<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/42-sort-readings-with-comparator.md

PURPOSE:
Teach a numeric ordering rule and a deterministic tie-break with Comparator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Sort readings with Comparator

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

A report can show the smallest reading first and still give a predictable order when values match. Each practice reading has a value and a unique sequence number. Sort by value from smallest to largest. For equal values, put the smaller sequence number first.

In the [previous lesson](41-choose-a-report-period-with-switch.md), you chose a period for a report. Here you decide how readings in a report appear. If records are new to you, start with [Keep a reading in a record](36-keep-a-reading-in-a-record.md). Use a JDK that supports Java 21 and a PowerShell practice folder.

## 1. Save and compile the example

Save [SortReadings.java](../../../labs/java-path/SortReadings.java) in the practice folder and open PowerShell there. Run these commands one at a time. Continue to `java` after `javac` succeeds.

```powershell
javac --release 21 -Xlint:all -Werror SortReadings.java
java -cp . SortReadings
```

`--release 21` checks the example against Java 21. `-Xlint:all` enables the compiler’s lint warnings, and `-Werror` makes any warning fail the build. `-cp .` tells Java to load the compiled class from the current folder.

```text
Value Sequence
3 4
7 2
7 11
```

## 2. Read the two comparisons

A `Comparator<Reading>` tells Java which of two readings should come first. `Reading::value` is a method reference. It tells `comparingInt` to take the number from each reading’s `value()` method.

```java
Comparator<Reading> byValueThenSequence = Comparator.comparingInt(Reading::value)
        .thenComparingInt(Reading::sequence);
```

`thenComparingInt` uses `sequence()` only when the values tie. Sequence 2 goes before 11 because they are numbers. The record constructor takes sequence first, so `new Reading(11, 7)` has sequence 11 and value 7.

`List.of` creates an unmodifiable list. `sortedCopy` copies its entries into an `ArrayList` before calling `sort`. The report uses the new order and the original list keeps its input order.

## 3. Check the tie and the primary rule

Change the input order to `new Reading(2, 7)`, `new Reading(4, 3)`, then `new Reading(11, 7)`. Compile and run again. The four output lines should stay the same because the sequence numbers decide the tie.

Now change the value for sequence 11 from `7` to `-2`. Compile and run again. The changed value now puts sequence 11 first.

```text
Value Sequence
-2 11
3 4
7 2
```

If the order differs, check which number each constructor argument sets, then confirm that the comparator names `value` before `sequence`. If `java` cannot find `SortReadings`, check that you are in the folder where compilation succeeded.

A C23 comparison function can use the same rule. Compare the values with `<` and `>`. If they are equal, compare the sequence numbers with those operators. Direct comparisons work across the integer range, where subtracting two values can overflow.

## 4. Check the same order in C23

Save [reading_order.c](../../../labs/java-path/reading_order.c) beside the Java example. Open the PowerShell terminal you use for C23 development and run these commands one at a time.

```powershell
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror reading_order.c -o reading_order.exe
.\reading_order.exe
```

The first command builds a local executable. The second runs it. Check the same four lines shown in step 1. The C function returns a negative number when the first reading belongs earlier, a positive number when it belongs later, and zero when both keys match. C copies its input array because `qsort` rearranges the array it receives.

[Java 21 Comparator API](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/util/Comparator.html) · [Previous lesson](41-choose-a-report-period-with-switch.md) · [Next lesson](43-name-the-report-periods-with-an-enum.md) · [Java course](index.md)
