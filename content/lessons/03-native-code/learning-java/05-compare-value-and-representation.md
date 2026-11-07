<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/05-compare-value-and-representation.md

PURPOSE:
Explain the lesson: Compare a decimal value and its representation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a decimal value and its representation

A number can have more than one written form. The strings 25.1 and 25.10 describe the same numeric amount, but one keeps an extra decimal place. A program must choose which question it is asking: equal value, or equal representation?

## Setup recap

Install a JDK version 17 or later and check `java --version` and `javac --version` in PowerShell or bash. Open `content/labs/java-ledger` in the Bits2Banking checkout. The course's first chapter explains installation; the laboratory README gives the complete commands. No banking account is used.

## 1. Predict two comparisons

Read the first two requirements in DecimalChecks.java. `new BigDecimal("25.10")` constructs a decimal from characters. The quotation marks matter: they pass text to the constructor. The variable `amount` refers to that decimal value.

~~~text
amount:  25.10
shorter: 25.1
numeric comparison: equal
representation comparison: different
~~~

`compareTo` returns zero for equal numeric values. `equals` also considers the scale. In this example the scales are two and one.

## 2. Run the checked example

From the laboratory directory:

~~~text
mkdir out
javac -d out LedgerDemo.java LedgerChecks.java DecimalChecks.java
java -cp out DecimalChecks
~~~

Skip mkdir if the directory already exists. Stop if compilation fails. The expected final line says the decimal representation and rounding checks passed.

## 3. Follow an immutable value

Find `amount.add(...)`. The method produces a result; it does not replace the original amount. The following requirement confirms that `amount.toPlainString()` still produces 25.10. To keep a calculated value, store the returned object in a variable.

## Exercise and explanation

Predict the numeric comparison of 2.00 and 2.000, then add a requirement. Their values compare equal, while their scales differ. A journal total uses numeric comparison, as the existing LedgerDemo demonstrates. A file format may also need a specified representation.

If the result surprises you, inspect the constructor argument and the comparison method before changing the expected result. A passing arithmetic check does not establish that a journal has valid accounts or permissions.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/java-ledger/DecimalChecks.java). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](06-make-rounding-an-explicit-decision.md)


[Previous lesson: Check a ledger invariant](04-check-a-ledger-invariant.md)
