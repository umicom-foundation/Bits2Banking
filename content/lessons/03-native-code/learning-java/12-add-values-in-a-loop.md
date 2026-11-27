<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/12-add-values-in-a-loop.md

PURPOSE:
  Teach add values in a loop with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Add values in a loop

A coordinator adds two units after each of three shifts. You will give the total a name, repeat the addition and check whether the batch is complete.

Complete the previous lesson before trying this one. Use the same JDK and a writable practice folder.

## Try it

1. Save `ShiftTotal.java` and point to the `total` variable. `int` stores a whole number. The first assignment gives it the value zero.
2. Read the `for` line from left to right. Start `shift` at 1, continue while it is at most 3, and increase it by 1 after each pass.
3. Write 2, 4 and 6 on paper to trace the three values of `total`. The `if` body runs when the final total reaches 6.
4. Compile, then run the program. The batch message appears once, above the final count.

## Example files

### ShiftTotal.java

[Open ShiftTotal.java](../../../labs/java-path/ShiftTotal.java)

~~~java
public class ShiftTotal {
    public static void main(String[] args) {
        int total = 0;
        // Each shift adds two units. Printing happens after all three shifts.
        for (int shift = 1; shift <= 3; shift++) {
            total += 2;
        }
        if (total >= 6) {
            System.out.println("Batch complete");
        }
        System.out.println("Units: " + total);
    }
}
~~~

## Run it

~~~text
javac ShiftTotal.java
java -cp . ShiftTotal
~~~

The program output to check is shown below.

~~~text
Batch complete
Units: 6
~~~

## Read the result

`total += 2` adds two to the value already stored. The braces mark which lines belong to the loop and the `if` body. C uses the same three-part `for` shape and the same `>=` comparison. In Java the condition evaluates to `true` or `false`; C uses a scalar zero or non-zero value in a condition.

Choose a type for the kind of value you need. `int` stores a 32-bit whole number and `long` stores a 64-bit whole number. `double` suits approximate quantities such as a measured length. `boolean` holds `true` or `false`, and `String` represents text. Use the later ledger lessons when you need exact decimal calculations.

## Practise

Change the loop to stop after two shifts. Compile and run again. The only output should be `Units: 4`.

## Fix a problem

If the complete message prints three times, check that the `if` is below the loop’s closing brace. If the total is 8, trace whether the loop began at zero while still allowing shift 3.

## Reference

- [Java language basics](https://dev.java/learn/language/constructs/)

[Previous · Install the JDK and run a class](11-install-the-jdk-and-run-a-class.md) · [Next · Total an array with a method](13-total-an-array-with-a-method.md)
