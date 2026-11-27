# Run independent checks with virtual threads

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

A report needs a heading and a total. The two checks can work independently. The report still needs the heading to appear first. Run the checks as separate tasks and choose the display order when you collect their results.

Open PowerShell 7 in a new practice folder. Use JDK 21 or later. If you need to set up your tools, follow [Install the JDK and run a class](11-install-the-jdk-and-run-a-class.md).

## 1. Save the program

Save the sample as `ReportChecks.java`, or open the [source file](../../../labs/java-path/ReportChecks.java).

```java
import java.util.concurrent.Executors;

public class ReportChecks {
    public static void main(String[] args) throws Exception {
        // Each submitted check is independent and returns its own result.
        try (var workers = Executors.newVirtualThreadPerTaskExecutor()) {
            var readings = workers.submit(() -> "Readings: " + (12 + 8));
            var heading = workers.submit(() -> "Heading: Daily report");

            // The report's order belongs to the caller, even if tasks finish out of order.
            System.out.println(heading.get());
            System.out.println(readings.get());
        }
    }
}
```

An executor starts work on your behalf. Each `submit` hands it one task. The `() ->` syntax is a short way to give the executor a piece of code to call later. These tasks take no arguments and return text. The two values returned by `submit` are futures. A future is a handle you can use to wait for a task's result.

`var` tells Java to infer the types from the values on the right. The `try` block owns the executor and closes it when the block ends. If a check fails, this small console example lets the exception report the failure.

## 2. Compile and run

```powershell
javac --release 21 ReportChecks.java
java ReportChecks
```

The program prints these two lines.

```text
Heading: Daily report
Readings: 20
```

The program submits the readings first. It waits for the heading result before printing anything. The `get` calls determine display order even when the tasks finish in a different order.

## 3. Change only the order of display

Swap the two `System.out.println` lines. Compile and run again. The readings should appear before the heading. Put the lines back when you finish.

If `javac` cannot find `newVirtualThreadPerTaskExecutor`, run `javac -version` in the same shell and check that it reports 21 or later.

This tiny example demonstrates result ordering. Adding two numbers needs very little work. Virtual threads are most useful when many tasks spend time waiting, for example when reading independent data sources. Keep related output ordering in the report and give each task its own inputs. Umicom Framework workers can follow the same division of responsibilities. [Java virtual thread guide](https://docs.oracle.com/en/java/javase/21/core/virtual-threads.html)

[Previous lesson](32-save-a-copy-of-a-growing-list.md) · [Next lesson](34-report-a-task-failure.md) · [Java course](index.md) · [Java in simple steps](../../../simple-steps/course-guides/learning-java.md)
