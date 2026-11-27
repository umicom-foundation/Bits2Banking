# Record a Java program run

![Umicom](../../../assets/branding/umicom-wordmark.svg)

Watch what happens during a Java run. Java Flight Recorder collects events from the Java Virtual Machine while your program runs. The recording can help you investigate slow code or compare two runs. Start with an addition program whose result you already know.

Use JDK 21 or later and PowerShell. Open the Bits2Banking checkout, where you can see the `content` folder. This example uses the same program as [Read a method in bytecode](26-read-a-method-in-bytecode.md).

## 1. Build and run the example

```powershell
javac --release 21 -d build/java-flight-classes content/labs/java-path/AddReadings.java
java -cp build/java-flight-classes AddReadings
```

The program prints `20`. Keep that number in mind when you turn on recording.

## 2. Start recording with the program

```powershell
java "-XX:StartFlightRecording=filename=build/readings.jfr,settings=default,dumponexit=true" -cp build/java-flight-classes AddReadings
Get-Item -LiteralPath build/readings.jfr
```

The first command starts recording when Java runs. The program still prints `20`. Java writes the recording to `build/readings.jfr` when it exits. The second command should show a file whose length is greater than zero.

## 3. Read the event summary

```powershell
jfr summary build/readings.jfr
```

Find the event type `jdk.JVMInformation` and its count. This entry shows that the recording captured information about the virtual machine. Short runs may have few or no events of other types. A later lab with a longer workload may show a different set.

## 4. Keep one useful observation

Write down the program output and an event count. When you compare runs, keep the same program, inputs and JDK first. Change one part of the program and record another file using a different name. A single short recording shows the steps work. Measuring a real performance change takes a representative workload and several comparable runs.

If `jfr` is missing, run `Get-Command java, javac, jfr` and check that your terminal finds all three tools from the intended JDK. If the recording file is missing, read Java's message and check that the output directory is writable. Recordings can contain machine and process details. For this exercise, keep the file on your own machine and share your written observation.

[Previous lesson](27-read-the-modules-a-java-app-needs.md) · [Java course](index.md) · [JDK Flight Recorder reference](https://docs.oracle.com/en/java/javase/21/docs/specs/man/jfr.html)
