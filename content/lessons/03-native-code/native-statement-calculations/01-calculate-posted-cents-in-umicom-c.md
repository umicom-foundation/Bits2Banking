<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-statement-calculations/01-calculate-posted-cents-in-umicom-c.md

PURPOSE:
Teach Calculate posted cents in Umicom C through original worked exercises.

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

# Calculate posted cents in Umicom C

[Course contents](index.md) · [Next: Keep the last valid total in C23](02-keep-the-last-valid-total-in-c23.md)

## What you will learn

Return the posted total for a three-entry training statement and explain which entry was excluded.

## Read the training statement

An amount in cents is a whole number. Record a credit as positive and a debit as negative. A posted entry contributes to this example’s balance movement. A pending entry is visible for review and stays out of that movement.

| Reference | Amount in cents | State |
| --- | --- | --- |
| 101 | 2600 | Posted |
| 102 | -850 | Posted |
| 103 | 500 | Pending |

## Write and run the program

Save the program below as reserve.uc in a practice folder. The example uses Umicom C’s checked integer profile. The integer returned by main is displayed by the run command.

```c
int main(void) {
    int posted = 2600;
    posted -= 850;
    int pending = 500;
    int include_pending = 0;
    if (include_pending == 1) {
        posted += pending;
    }
    return posted;
}
```

```text
umicom-c check reserve.uc
umicom-c run reserve.uc
```

Expect a successful check and a result of 1750. Follow the values 2600, then 1750, then 1750 again. The comparison returns a false value, so the addition in braces does not run.

## Practice and check your answer

Change include_pending to 1, predict the result and run the check again. Then restore it to 0.

**Worked answer**

The modified program returns 2250. Restoring the original setting returns 1750. A report should label what is included so a reader can tell which result they are looking at.

## If the check fails

If the shell cannot find umicom-c, use its full path from your build or use the paper trace above. If the checker rejects source, read the reported line and column. Keep main and all braces, and end declarations, assignments and return with a semicolon.

[Read this lesson as HTML](../../../courses/native-statement-calculations/lessons/01-calculate-posted-cents-in-umicom-c.html)

## Continue learning

- [Learning C](../../../courses/learning-c/index.html)
- [Building a Compiler in C](../../../courses/building-a-compiler-in-c/index.html)

## Further reading

- [Tech Sustainify course catalogue](https://techsustainify.com/)
- [W3Schools C tutorial](https://www.w3schools.com/c/index.php)


[Course contents](index.md) · [Next: Keep the last valid total in C23](02-keep-the-last-valid-total-in-c23.md)
