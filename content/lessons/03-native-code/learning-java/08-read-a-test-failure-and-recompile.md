<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/08-read-a-test-failure-and-recompile.md

PURPOSE:
Explain the lesson: Read a test failure and recompile the changed source.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a test failure and recompile the changed source

A failed check is useful when it shows which assumption no longer holds. This exercise deliberately changes a prediction, observes the failure, and restores the correct assertion in a private practice copy.

## Setup recap

Copy the java-ledger laboratory to a writable exercise folder. Use Java 17 or later, check both java and javac versions, and create an out directory. Keep the original repository sources intact.

## 1. Establish a reference result

Compile LedgerDemo.java, LedgerChecks.java and DecimalChecks.java together with `javac -d out`. Run `java -cp out LedgerChecks`. Save the command and the expected final success message in your notes.

A source file is the human-readable program. A class file is compiler output. Editing the source does not automatically update the class file.

## 2. Introduce a known wrong prediction

In the practice copy, find the requirement described as “One unmatched debit”. Remove the negation before the call, so the assertion wrongly expects a single debit to balance. Keep the descriptive text unchanged.

Compile again and run the check. Expect AssertionError identifying that requirement. In PowerShell, inspect `$LASTEXITCODE` immediately after java returns. In bash, use `echo $?`. A failure status is different from the ordinary success message.

## 3. Trace cause and repair

The test input contains a debit and no credit. The implementation sums both sides; the credit sum remains zero. Restore the negation, recompile, and rerun. The repair belongs in the incorrect expectation, not in the balancing function.

For an unknown failure, do not assume the test is wrong. Compare the contract, input, actual value and expected value first.

## Exercise and explanation

Run the previously built class file before recompiling an edit. Explain why it still shows the old result. Then deliberately misspell the main class name and distinguish that launch error from AssertionError.

This workflow also applies when reading Umicom build logs: identify the failing stage before changing code. A compiler error, an incorrect command and a failed behavioral assertion need different investigations.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/java-ledger/LedgerChecks.java). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-test-a-journal-without-overclaiming.md)

