<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/48-set-a-deadline-for-a-virtual-thread-task.md

PURPOSE:
Set a deadline for a virtual-thread task

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Set a deadline for a virtual-thread task

A report window may need to stop waiting before an unfinished task produces a result. This exercise gives a Java task a short time to return its report, requests cancellation when that time expires, and verifies the worker received the request.

## 1. Compile and run the example

1. Save [ReportTaskDeadline.java](../../../labs/java-path/ReportTaskDeadline.java) in your practice folder.
2. Open PowerShell in that folder. Check that `javac -version` reports a JDK with Java 21 support.
3. Run the two commands in order.

```powershell
javac --release 21 .\ReportTaskDeadline.java
java -cp . ReportTaskDeadline
```

Expect these three lines.

```text
Timed out waiting for report
Worker acknowledged interruption
Normal work returned report ready
```

## 2. Follow the three events

1. The first task runs on a virtual thread. It tells the program it has started, then waits at a gate. A `CountDownLatch` is a gate that opens when its count reaches zero. The exercise keeps the report gate closed during the wait.
2. `waiting.get(200, TimeUnit.MILLISECONDS)` gives the caller a 200-millisecond limit. A `TimeoutException` means the caller reached that limit while waiting.
3. `waiting.cancel(true)` asks Java to interrupt the worker. The worker receives `InterruptedException` at the gate and signals that it saw the interruption. The program waits for that signal before printing the second line.
4. The second task supplies a result immediately. Its result shows the ordinary completion path using the same executor.

The `finally` block opens the report gate even if an earlier check fails. The executor can finish closing after its blocking task leaves.

## 3. Try another deadline

1. Change `200` to `400` in the call to `waiting.get`. Keep the units as `MILLISECONDS`.
2. Save the file and run the compile and launch commands again.
3. Confirm you still see all three lines. The first task still waits at the closed gate, so either wait limit expires.

If the Java launcher cannot find the class, run the compile command again from the folder containing `ReportTaskDeadline.java`. Check that `ReportTaskDeadline.class` appears before launching it.

## Apply it to Umicom

For a build or report action, keep the waiting deadline, cancellation request and worker completion as separate observations. A progress view can then tell an operator whether the work reached its deadline or whether the worker has acknowledged the request.

Read [Report a task failure](../../../courses/learning-java/lessons/34-report-a-task-failure.html) to see how a worker’s own error reaches the caller.

- [Java 21 Future API for waits and cancellation](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/util/concurrent/Future.html)
- [Java 21 Executors API for virtual threads](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/util/concurrent/Executors.html)

[Previous lesson](47-load-defaults-from-a-jar.md) · [Java course](index.md) · [Browser edition](../../../courses/learning-java/lessons/48-set-a-deadline-for-a-virtual-thread-task.html)
