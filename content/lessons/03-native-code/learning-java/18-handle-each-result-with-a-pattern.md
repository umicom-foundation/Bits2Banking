<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/18-handle-each-result-with-a-pattern.md

PURPOSE:
  Teach handle each result with a pattern with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Handle each result with a pattern

A reading can be accepted with a number or rejected with a reason. Store those outcomes as separate types and handle each one where the report is printed.

Complete the previous lesson before trying this one. Use the same JDK and a writable practice folder.

## Try it

1. Save `ReadingResult.java`. Read the `permits` list. It says which record types can implement `Result` here.
2. Trace `classify(4)` and `classify(-1)`. The method creates an accepted value for the first input, and a reason for the second.
3. Read the two cases in `show`. Each pattern names both the chosen type and a variable that exposes its fields.
4. Compile using Java 21 or later and run the program. Compare the two lines.

## Example files

### ReadingResult.java

[Open ReadingResult.java](../../../labs/java-path/ReadingResult.java)

~~~java
public class ReadingResult {
    sealed interface Result permits Accepted, Rejected {}
    record Accepted(int units) implements Result {}
    record Rejected(String reason) implements Result {}

    static Result classify(int units) {
        return units >= 0 ? new Accepted(units) : new Rejected("negative reading");
    }

    static String show(Result result) {
        // Java checks both permitted result types are handled by the switch.
        return switch (result) {
            case Accepted accepted -> "Accepted: " + accepted.units();
            case Rejected rejected -> "Rejected: " + rejected.reason();
        };
    }

    public static void main(String[] args) {
        System.out.println(show(classify(4)));
        System.out.println(show(classify(-1)));
    }
}
~~~

## Run it

~~~text
javac --release 21 ReadingResult.java
java -cp . ReadingResult
~~~

The program output to check is shown below.

~~~text
Accepted: 4
Rejected: negative reading
~~~

## Read the result

The switch gives back a string for either permitted subtype. Java can check that the listed patterns cover the sealed set. A native C design may store an enum for the outcome and a struct or union for the corresponding data; the C code still has to interpret the right member for the chosen tag.

## Practise

Add an `Unavailable` record with a reason, include it in `permits` and compile. The compiler identifies the missing switch case. Add the case and print a sample outcome to check it.

## Fix a problem

Use `javac -version` if the compiler rejects the pattern syntax. This version uses standard Java 21 features and needs no preview flags.

## Reference

- [Java 21 switch expressions and patterns](https://docs.oracle.com/javase/specs/jls/se21/html/jls-15.html#jls-15.28)

[Previous · Test and debug a boundary](17-test-and-debug-a-boundary.md) · [Next · Collect results from virtual threads](19-collect-results-from-virtual-threads.md)
