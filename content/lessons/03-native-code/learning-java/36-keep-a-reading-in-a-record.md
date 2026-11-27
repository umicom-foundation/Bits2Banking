# Keep a reading in a record

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

A reading has two pieces of information. It has a meter name and a number. Keep the two values together, check them when you create the reading and compare two readings by their values.

Use PowerShell 7 and JDK 21 or later. If you are new to classes, start with [Keep a valid total in a class](31-keep-a-valid-total-in-a-class.md).

## 1. Save the Java program

Save this example as `RecordReadings.java` in a new practice folder. You can also open the [source file](../../../labs/java-path/RecordReadings.java).

```java
public class RecordReadings {
    record Reading(String meter, int units) {
        Reading {
            // Reject an invalid reading before Java assigns the record fields.
            if (meter == null || meter.isBlank()) {
                throw new IllegalArgumentException("Give the meter a name.");
            }
            if (units < 0) {
                throw new IllegalArgumentException("Units must be zero or more.");
            }
        }
    }

    public static void main(String[] args) {
        // Two separate records can represent the same observation.
        Reading first = new Reading("Boiler room", 8);
        Reading second = new Reading("Boiler room", 8);
        System.out.println(first.meter() + " read " + first.units());
        System.out.println("Same reading: " + first.equals(second));

        // Show the exact constructor feedback for a refused value.
        try {
            new Reading("Boiler room", -1);
        } catch (IllegalArgumentException failure) {
            System.out.println(failure.getMessage());
        }
    }
}
```

The `record` line lists the values that belong together. The short `Reading { ... }` block checks the values supplied to the constructor before Java saves them. The methods `meter()` and `units()` read the saved values.

## 2. Compile and run

```powershell
javac --release 21 RecordReadings.java
java RecordReadings
```

You should see this output.

```text
Boiler room read 8
Same reading: true
Units must be zero or more.
```

`equals` compares the record's components. The two records here have the same name and number. The third construction fails because this example admits zero and positive readings.

## 3. Compare two different readings

Change the second reading from 8 to 9. Save, compile and run again. The comparison line should change to `Same reading: false`. If it still says `true`, check that you edited the second `new Reading` call and recompiled that file.

Both components here have immutable values. When a planned record would contain a mutable value, decide whether you need to save a copy first. The [list snapshot exercise](32-save-a-copy-of-a-growing-list.md) shows how to save the current entries of a growing list.

An Umicom Framework read model can use a C structure for the same purpose. Check the proposed data before publishing the structure so later consumers receive a consistent reading. [Java record classes](https://docs.oracle.com/en/java/javase/21/language/records.html)

[Previous lesson](35-show-a-time-with-its-offset.md) · [Next lesson](37-close-resources-and-keep-the-cause.md) · [Java course](index.md) · [Java in simple steps](../../../simple-steps/course-guides/learning-java.md)
