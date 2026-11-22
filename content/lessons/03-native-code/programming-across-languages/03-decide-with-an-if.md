<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/programming-across-languages/03-decide-with-an-if.md

PURPOSE:
Follow the same yes-or-no decision written with braces or indentation.

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

# Make a decision with if

[Course contents](index.md) · [Previous · Give values names and units](02-give-values-names-and-units.md) · [Next · Compare one for loop in six languages](04-repeat-the-same-for-loop.md) · [Browser edition](../../../courses/programming-across-languages/lessons/03-decide-with-an-if.html)

Follow the same yes-or-no decision written with braces or indentation.

## Choose one path

A condition is a question with a true or false answer. Here, the amount passes the first check if it is greater than or equal to zero.

```text
IF amount cents is at least zero
    SHOW "amount accepted"
ELSE
    SHOW "check the amount"
```

## Compare the keywords

All six languages use `if` and `else` for the two choices. C, C++, Java, and D put this condition in parentheses and use braces to group the chosen action. Go uses braces with no required parentheses. Python uses a colon and indentation, which means spaces at the start of a line.

```c
if (amount_cents >= 0) {
    puts("amount accepted");
} else {
    puts("check the amount");
}
```

```go
if amountCents >= 0 {
    fmt.Println("amount accepted")
} else {
    fmt.Println("check the amount")
}
```

```python
if amount_cents >= 0:
    print("amount accepted")
else:
    print("check the amount")
```

## Trace the boundary

Try 1, 0 and −1 on paper. For 1 and 0, the program should accept the amount. For −1, it should ask you to check it. The point at which the answer changes is a boundary.

In a training enhancement for Umicom Bank, record those three inputs as a check before changing how a form accepts amounts. The snippets belong inside a larger program that defines the amount and supplies the output functions.

## Continue in another course

- [Computing from the Beginning](../../../courses/computing-from-the-beginning/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python keyword reference](../../../courses/python-keyword-reference/index.html)
- [Go keyword reference](../../../courses/go-keyword-reference/index.html)
- [Go statement tools](../../../courses/go-statement-tools/index.html)
- [Umicom C and C23 statement calculations](../../../courses/native-statement-calculations/index.html)

[Course contents](index.md) · [Previous · Give values names and units](02-give-values-names-and-units.md) · [Next · Compare one for loop in six languages](04-repeat-the-same-for-loop.md) · [Browser edition](../../../courses/programming-across-languages/lessons/03-decide-with-an-if.html)
