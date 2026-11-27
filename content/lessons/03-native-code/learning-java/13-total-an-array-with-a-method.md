<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/13-total-an-array-with-a-method.md

PURPOSE:
  Teach total an array with a method with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Total an array with a method

A schedule has three blocks of 15, 25 and 20 minutes. An array holds these values together. A method gives the calculation a name so it can be reused and checked.

Complete the previous lesson before trying this one. Use the same JDK and a writable practice folder.

## Try it

1. Save `MinutesReport.java` and read the values between braces in `durations`.
2. Read `totalMinutes(int[] durations)`. The method accepts an array of whole numbers and returns a `long`, a wider whole number.
3. Trace the enhanced loop. `duration` receives the next item. When there are no items the total stays zero.
4. Compile and run. The two checks compare the normal total and the empty case before printing.

## Example files

### MinutesReport.java

[Open MinutesReport.java](../../../labs/java-path/MinutesReport.java)

~~~java
public class MinutesReport {
    static long totalMinutes(int[] durations) {
        long total = 0;
        // Visit each supplied duration once, including when the array is empty.
        for (int duration : durations) {
            total += duration;
        }
        return total;
    }

    public static void main(String[] args) {
        int[] durations = {15, 25, 20};
        long actual = totalMinutes(durations);
        if (actual != 60 || totalMinutes(new int[0]) != 0) {
            throw new IllegalStateException("Unexpected duration total");
        }
        System.out.println("Minutes: " + actual);
    }
}
~~~

## Run it

~~~text
javac MinutesReport.java
java -cp . MinutesReport
~~~

The program output to check is shown below.

~~~text
Minutes: 60
~~~

## Read the result

`return total` gives the caller a value. The checks throw an exception and stop the program if either result differs. In a C function, an ordinary array parameter alone carries no length. Pass the element count as a separate argument. Java’s array object already knows its length.

## Practise

Add a 10-minute block. Keep the expected value at 60 once and observe the failure. Change the expected value to 70, compile again and confirm the report displays `Minutes: 70`.

## Fix a problem

If you get `Unexpected duration total`, add the original values by hand and check whether the expected total reflects a change to the array.

## Reference

- [Java arrays and methods](https://dev.java/learn/language/constructs/)

[Previous · Add values in a loop](12-add-values-in-a-loop.md) · [Next · Separate a record and its writer](14-separate-a-record-and-its-writer.md)
