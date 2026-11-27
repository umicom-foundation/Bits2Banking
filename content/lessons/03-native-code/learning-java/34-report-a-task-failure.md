# Report a task failure

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Suppose an operator types a reading as `many` instead of a number. The task that reads the entry fails. The program should explain how to correct the entry and return a status a script can check.

Use PowerShell 7 and JDK 21 or later. If executors and futures are unfamiliar, start with [Run independent checks with virtual threads](33-run-independent-checks-with-virtual-threads.md).

## 1. Save the program

Save the code as `ReadCheckedValue.java` in a new practice folder. You can also open the [source file](../../../labs/java-path/ReadCheckedValue.java).

```java
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;

public class ReadCheckedValue {
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        System.exit(run(args));
    }

    private static int run(String[] args) throws InterruptedException, ExecutionException {
        if (args.length != 1) {
            System.err.println("Give one reading.");
            return 2;
        }

        // Finish and close the executor before publishing the command's exit code.
        try (var worker = Executors.newVirtualThreadPerTaskExecutor()) {
            var reading = worker.submit(() -> Integer.parseInt(args[0]));
            try {
                System.out.println("Reading: " + reading.get());
                return 0;
            } catch (ExecutionException failure) {
                // Give an actionable message for the input error this task expects.
                if (failure.getCause() instanceof NumberFormatException) {
                    System.err.println("Enter a whole number that fits in a Java int.");
                    return 1;
                }
                throw failure;
            }
        }
    }
}
```

`Integer.parseInt` converts text to an integer. That conversion happens in the task. If the conversion throws an exception, `reading.get()` reports an `ExecutionException` in the calling code. `getCause()` retrieves the problem that the task originally reported.

`System.out` carries a successful reading. `System.err` carries the correction. The expected input mistake returns 1. An unexpected task problem still reaches Java's exception reporting so a developer can identify it.

## 2. Compile and run a successful check

```powershell
javac --release 21 ReadCheckedValue.java
java ReadCheckedValue 42
$LASTEXITCODE
```

You should see `Reading: 42` followed by `0`. Read `$LASTEXITCODE` immediately after Java so you can see that command's result.

## 3. Compare two failures

```powershell
java ReadCheckedValue many
$LASTEXITCODE
java ReadCheckedValue
$LASTEXITCODE
```

The first command prints `Enter a whole number that fits in a Java int.` and returns 1. The second prints `Give one reading.` and returns 2. It refuses to create the task because there is no input to pass to it.

Try `-5` next. It is a whole number too. The program prints `Reading: -5` and returns 0.

If the console reports that it cannot load `ReadCheckedValue`, check that the file has exactly the same spelling as the class and that you ran `javac` in this practice folder. If the task reports a different kind of error, read the final `Caused by` section before changing how the caller handles the result.

This is a good boundary for a command in Umicom Framework too. Return one result to the caller after the worker finishes, keep expected input feedback clear, and preserve unexpected task errors for diagnosis. [Java 21 Future reference](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/util/concurrent/Future.html)

[Previous lesson](33-run-independent-checks-with-virtual-threads.md) · [Next lesson](35-show-a-time-with-its-offset.md) · [Java course](index.md) · [Java in simple steps](../../../simple-steps/course-guides/learning-java.md)
