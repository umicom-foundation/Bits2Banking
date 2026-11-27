<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/17-test-and-debug-a-boundary.md

PURPOSE:
  Teach test and debug a boundary with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Test and debug a boundary

A recorded reading can be accepted at the exact limit. Test the value at the boundary, the value just beyond it and a value below zero. Then inspect one calculation in a debugger.

Complete the previous lesson before trying this one. Use the same JDK and a writable practice folder.

## Try it

1. Save `LimitChecks.java`. Run it once with the three original checks. `-g` includes information the debugger can use to show local variable names.
2. As a deliberate mistake, change `value <= limit` to `value < limit`. Recompile and run. The test at the upper boundary should identify the failing case.
3. Start `jdb -classpath . LimitChecks`. At its prompt, type `stop in LimitChecks.withinLimit`, then `run`. A breakpoint pauses the program at this method.
4. At the pause, type `locals` to see `value` and `limit`. Use `next` to step through each comparison. Type `exit` when you finish. Restore the `<=` comparison and rerun all three checks.

## Example files

### LimitChecks.java

[Open LimitChecks.java](../../../labs/java-path/LimitChecks.java)

~~~java
public class LimitChecks {
    static boolean withinLimit(int value, int limit) {
        // Name the two comparisons so the debugger can show each decision.
        boolean nonNegative = value >= 0;
        boolean atOrBelow = value <= limit;
        return nonNegative && atOrBelow;
    }

    static void check(boolean actual, boolean expected, String name) {
        if (actual != expected) {
            throw new IllegalStateException(name + ": expected " + expected + ", got " + actual);
        }
    }

    public static void main(String[] args) {
        check(withinLimit(5, 5), true, "upper boundary");
        check(withinLimit(6, 5), false, "above boundary");
        check(withinLimit(-1, 5), false, "negative value");
        System.out.println("3 checks passed");
    }
}
~~~

## Run it

~~~text
javac -g LimitChecks.java
java -cp . LimitChecks
jdb -classpath . LimitChecks
~~~

The program output to check is shown below.

~~~text
3 checks passed
~~~

## Read the result

The checks throw an exception with the name of the failed case. The method receives 5 and 5 for the first check, which makes `<` false and `<=` true. A debugger shows the inputs and state during execution; the checks can be run again after every edit.

## Practise

Add a check for value 0 with a limit of 0. Expect it to pass. Choose a name that will still describe the case when you read a failure later.

## Fix a problem

Run `javac -g` again if `locals` cannot show variable names. In the debugger call `run` after adding the breakpoint; typing that command before the breakpoint will let the short program finish.

## Reference

- [The JDK debugger commands](https://docs.oracle.com/en/java/javase/21/docs/specs/man/jdb.html)

[Previous · Read a file and explain errors](16-read-a-file-and-explain-errors.md) · [Next · Handle each result with a pattern](18-handle-each-result-with-a-pattern.md)
