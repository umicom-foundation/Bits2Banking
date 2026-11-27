<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/19-collect-results-from-virtual-threads.md

PURPOSE:
  Teach collect results from virtual threads with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Collect results from virtual threads

Two independent reports can wait at the same time. A virtual thread lets you write each small task in the familiar sequential style. This exercise models waiting with a short pause and uses no network.

Complete the previous lesson before trying this one. Use the same JDK and a writable practice folder.

## Try it

1. Save `ParallelReports.java`. The two tasks send requests for North and South.
2. Read `submit`. It starts a task and gives you a future, an object that will eventually hold its result or failure.
3. Compile and run with JDK 21 or newer. The program calls `get` on both futures before adding their counts.
4. Run it with `East` as an argument and compare the error message with the successful output.

## Example files

### ParallelReports.java

[Open ParallelReports.java](../../../labs/java-path/ParallelReports.java)

~~~java
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;

public class ParallelReports {
    static int request(String site) throws InterruptedException {
        // The pause stands in for a blocking read. This lab uses no network.
        Thread.sleep(30);
        return switch (site) {
            case "North" -> 4;
            case "South" -> 3;
            default -> throw new IllegalArgumentException("Unknown site");
        };
    }

    public static void main(String[] args) {
        try (var executor = Executors.newVirtualThreadPerTaskExecutor()) {
            var north = executor.submit(() -> request("North"));
            var south = executor.submit(() -> request(args.length == 0 ? "South" : args[0]));
            // Read results in a fixed order. Completion order can differ.
            int total = north.get() + south.get();
            System.out.println("Total: " + total);
        } catch (InterruptedException error) {
            Thread.currentThread().interrupt();
            System.err.println("Interrupted while collecting reports.");
            System.exit(1);
        } catch (ExecutionException error) {
            System.err.println("Report failed: " + error.getCause().getMessage());
            System.exit(1);
        }
    }
}
~~~

## Run it

~~~text
javac --release 21 ParallelReports.java
java -cp . ParallelReports
java -cp . ParallelReports East
~~~

The program output to check is shown below.

~~~text
Total: 7
Report failed: Unknown site
~~~

## Read the result

The `try` block owns the executor. `get` waits for its task and reports a thrown task error through `ExecutionException`. The main program re-raises its interruption flag before reporting an interrupted wait. Virtual threads help when many independent tasks spend time waiting; the sample has no performance benchmark.

## Practise

Pass `North` as the second site. The same calculation should now report `Total: 8`. Add one more known site and decide which tests would cover it.

## Fix a problem

Confirm you are compiling against Java 21 or newer if the executor method is missing. Check the site spelling for the explicit failure example.

## Reference

- [Virtual threads and futures](https://dev.java/learn/api/virtual-threads/)

[Previous · Handle each result with a pattern](18-handle-each-result-with-a-pattern.md) · [Next · Package a report as a module](20-package-a-report-as-a-module.md)
