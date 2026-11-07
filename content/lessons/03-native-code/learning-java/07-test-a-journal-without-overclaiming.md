<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/07-test-a-journal-without-overclaiming.md

PURPOSE:
Explain the lesson: Test a journal without overclaiming its validity.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test a journal without overclaiming its validity

A useful test has a precise claim. LedgerDemo.IsBalanced answers whether total debits equal total credits. It does not answer every question needed before a financial system accepts an entry.

## Setup recap

Use Java 17 or later and the three files in content/labs/java-ledger. In a terminal in that directory, run `javac -d out LedgerDemo.java LedgerChecks.java DecimalChecks.java`, then `java -cp out LedgerChecks`. Create out first if necessary. These commands work in PowerShell and bash.

## 1. Read one record

A Posting groups an account label, a debit value and a credit value. LedgerChecks creates a debit of 25.10 and a credit of 25.1. It passes a list containing both records to the existing function.

The word list means an ordered collection. `List.of(debit, credit)` constructs the collection used for this call; it does not send a transaction anywhere.

## 2. Change one fact at a time

Read the checks in order and make a prediction table:

~~~text
debit, credit        -> balanced
debit alone          -> unbalanced
debit, credit, debit -> unbalanced
credit, debit        -> balanced
~~~

Removing an entry and duplicating an entry should change the result. Reordering valid entries should not change their sum. These are different properties, not four versions of the same successful example.

## 3. Examine the boundary of the claim

The last cases use an empty list and equal negative totals. Both are numerically balanced. That observation exposes the function's scope. Separate rules would be needed for valid account identifiers, accepted signs, currency and authorisation.

Do not change the teaching function to conceal that distinction. When developing a real Umicom application, find and use the relevant Framework financial service and its contract.

## Exercise and explanation

Create a debit of 25.10 and credit of 25.09. Predict false, add a requirement, compile and run. If it unexpectedly passes, inspect which objects were actually put in the list.

The test prints an arithmetic success message with its limitation. This evidence supports numeric balancing only; it is not proof that a bank or general ledger is ready for use.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/java-ledger/LedgerChecks.java). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-make-rounding-an-explicit-decision.md) · [Next lesson](08-read-a-test-failure-and-recompile.md)

