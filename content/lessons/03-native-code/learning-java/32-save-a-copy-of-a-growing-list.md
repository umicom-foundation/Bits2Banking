# Save a copy of a growing list

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Suppose you record two meter readings in the morning and add another at noon. You want the morning report to keep its original readings while the current list continues to grow.

Open PowerShell 7 in a practice folder with JDK 21 or later. If you are setting up Java for the first time, follow [Install the JDK and run a class](11-install-the-jdk-and-run-a-class.md).

## 1. Save the program

Save this code as `ReadingHistory.java`. You can also open the [source file](../../../labs/java-path/ReadingHistory.java).

```java
import java.util.ArrayList;
import java.util.List;

public class ReadingHistory {
    public static void main(String[] args) {
        // Keep routine additions in arrival order.
        List<Integer> readings = new ArrayList<>();
        readings.add(12);
        readings.add(8);

        // A report holds the readings available when it was taken.
        List<Integer> morningReport = List.copyOf(readings);
        readings.add(15);

        System.out.println("Morning report: " + morningReport);
        System.out.println("Current readings: " + readings);
    }
}
```

`List<Integer>` describes an ordered list of whole numbers. `new ArrayList<>()` creates an empty list you can grow. Each call to `add` appends one reading. `List.copyOf` saves the current sequence in a list whose entries cannot be added, removed or replaced.

## 2. Compile and check both lists

```powershell
javac --release 21 ReadingHistory.java
java ReadingHistory
```

You should see these two lines.

```text
Morning report: [12, 8]
Current readings: [12, 8, 15]
```

The brackets show the contents of each list. Both lists started with the same readings. Changing the current list later leaves the morning sequence intact.

## 3. Take the copy one line later

Move `readings.add(15);` above the line that creates `morningReport`. Compile and run again. Both lines should now contain `[12, 8, 15]`. The time you take the copy determines which readings it includes.

If Java reports that it cannot find `ReadingHistory`, run `Get-ChildItem -Name ReadingHistory*` and check that the source filename is exactly `ReadingHistory.java`. Keep the class name in the run command and compile again after each source edit.

`Integer` values cannot change in place. If you later store objects with fields that can change, a list copy keeps the same objects. If the report needs stable field values too, store immutable values or make a separate copy of those fields. [Java 21 List reference](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/util/List.html#copyOf(java.util.Collection))

A Umicom Trader chart can use the same idea when a user exports a historical report. Capture the readings at the chosen cutoff so a live update cannot change the exported sequence.

[Previous lesson](31-keep-a-valid-total-in-a-class.md) · [Next lesson](33-run-independent-checks-with-virtual-threads.md) · [Java course](index.md) · [Java in simple steps](../../../simple-steps/course-guides/learning-java.md)
