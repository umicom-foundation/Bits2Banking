<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/programming-across-languages/05-visit-a-list-and-skip-a-row.md

PURPOSE:
Trace a result through a collection of receipts using continue, and compare how each language visits a collection.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Visit a list and skip a row

[Course contents](index.md) · [Previous · Compare one for loop in six languages](04-repeat-the-same-for-loop.md) · [Next · Give a task a name and a result](06-give-a-task-a-name-and-a-result.md) · [Browser edition](../../../courses/programming-across-languages/lessons/05-visit-a-list-and-skip-a-row.html)

Trace a result through a collection of receipts using continue, and compare how each language visits a collection.

## Visit each stored amount

A collection holds several values together. A three-value collection holds 200, −50 and 75 cents in that order. For this practice report, include positive deposits and skip all other rows.

```text
SET total TO 0
FOR EACH amount IN [200, -50, 75]
    IF amount is less than or equal to zero
        CONTINUE with the next amount
    ADD amount TO total
SHOW total
```

## Compare the collection syntax

- C uses an index to visit an array. With the array declared in the same scope, a header can be `for (size_t i = 0; i < sizeof amounts / sizeof amounts[0]; ++i)`. A pointer passed into a function needs its length supplied separately.
- C++ has a range-based loop: `for (int amount : amounts)`. Java has an enhanced loop with the same text when `amounts` is an int array or a suitable iterable.
- D can use `foreach (amount; amounts)`. Here the keyword is `foreach` although a counting loop uses `for`.
- Go can use `for _, amount := range amounts` with an array or slice. The blank identifier `_` discards the index.
- Python can use `for amount in amounts:`. It receives the next element through the list iterator.

In all six versions, `continue` finishes the current pass early and lets iteration proceed. `break` ends the loop soon after that point instead of visiting the remaining elements.

## Check the trace

After 200, the total is 200. The −50 is skipped. Adding 75 gives 275 cents. Try replacing “continue” with “break” at that same step. The result then stays at 200 cents.

A report in Trader or TMS can use two training files that differ in one row to show whether it skipped a row or stopped the whole import. Keep test data separate from production records.

## Continue in another course

- [Computing from the Beginning](../../../courses/computing-from-the-beginning/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python keyword reference](../../../courses/python-keyword-reference/index.html)
- [Go keyword reference](../../../courses/go-keyword-reference/index.html)
- [Go statement tools](../../../courses/go-statement-tools/index.html)
- [Umicom C and C23 statement calculations](../../../courses/native-statement-calculations/index.html)

[Course contents](index.md) · [Previous · Compare one for loop in six languages](04-repeat-the-same-for-loop.md) · [Next · Give a task a name and a result](06-give-a-task-a-name-and-a-result.md) · [Browser edition](../../../courses/programming-across-languages/lessons/05-visit-a-list-and-skip-a-row.html)
