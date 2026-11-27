# Show a time with its offset

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Suppose an overnight report shows two readings at 01:30. When the clocks go back, the same local clock time can happen twice. Store the actual moment for each reading. Show its offset when you display it.

Open PowerShell 7 in a new practice folder with JDK 21 or later. If needed, follow [Install the JDK and run a class](11-install-the-jdk-and-run-a-class.md).

## 1. Save the program

Save this code as `ShowReadingTimes.java`. You can also open the [source file](../../../labs/java-path/ShowReadingTimes.java).

```java
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
```

An `Instant` represents one moment on the timeline. The `Z` at the end of each input means the time is given in UTC. `ZoneId` selects whose clock rules to use for display. In the label pattern, `HH:mm` shows the clock time and `xxx` prints the difference from UTC, including `+00:00` when the values match.

## 2. Compile and compare the two labels

```powershell
javac --release 21 ShowReadingTimes.java
java ShowReadingTimes
```

You should see these lines.

```text
Europe/London 01:30 +01:00
Europe/London 01:30 +00:00
Elapsed minutes: 60
```

The first reading displays one hour ahead of UTC. The second aligns with UTC. Both displays show 01:30 on the local clock. `Duration.between` compares the actual moments and reports the hour that passed.

## 3. Change the display to UTC

Change `"Europe/London"` to `"UTC"`, then compile and run again. The two clock labels should now read 00:30 and 01:30. The elapsed time should still be 60 minutes.

If the labels stay the same, check that you saved the edited file and ran `javac` in its directory. Put `"Europe/London"` back when you finish.

Apply the same idea in an Umicom Trader history. Save a stable timestamp for each market event, then apply the chosen display timezone when you render the timeline. [Java Instant reference](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/time/Instant.html) · [Java format patterns](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/time/format/DateTimeFormatter.html)

[Previous lesson](34-report-a-task-failure.md) · [Next lesson](36-keep-a-reading-in-a-record.md) · [Java course](index.md) · [Java in simple steps](../../../simple-steps/course-guides/learning-java.md)
