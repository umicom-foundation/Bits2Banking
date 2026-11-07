<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/06-make-rounding-an-explicit-decision.md

PURPOSE:
Explain the lesson: Make rounding an explicit decision.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Make rounding an explicit decision

Dividing one into three equal parts gives a decimal expansion that does not end. A finite output needs a rule for the digits it cannot retain. This chapter follows that decision in a small Java program.

## Setup recap

Use a JDK version 17 or later. Confirm `javac --version`, open the java-ledger laboratory, and compile the three Java files into an out directory as described in its README. Reading the source on paper needs no installation.

## 1. Observe the rejected exact operation

In DecimalChecks.java, find the try block containing `BigDecimal.ONE.divide(new BigDecimal("3"))`. No rounding choice is supplied. The example expects ArithmeticException and records that the exception happened.

An exception is a separate control-flow path. The catch block handles this particular exception. It does not turn every failure into a successful result.

## 2. Supply the output rule

The next calculation requests two digits after the decimal point and HALF_EVEN rounding. The expected result is 0.33. Read the arguments from left to right: the divisor, the number of decimal places, and the rounding rule.

The tie examples make the rule visible:

~~~text
1.005 -> two decimal places -> 1.00
1.015 -> two decimal places -> 1.02
~~~

At an exact halfway point, the retained final digit is chosen to be even. This is an arithmetic exercise. A real financial product must use its documented currency, instrument and reporting rules.

## 3. Run and extend

~~~text
java -cp out DecimalChecks
~~~

Expected: the final success message. Add 1.025 as another tie case, expecting 1.02, and recompile before running again. Running an old class file does not test an edited source file.

## Exercise and explanation

Would rounding each of three values separately always equal rounding their total once? No. The position of the rounding step is part of the algorithm. Draw both sequences with small decimal inputs and compare them. Record the rule with the code rather than hiding it in an unexplained numeric constant.

If the exact division does not reach the expected catch block, verify that the denominator is 3 and no scale argument has been added.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/java-ledger/DecimalChecks.java). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-compare-value-and-representation.md) · [Next lesson](07-test-a-journal-without-overclaiming.md)

