<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/programming-across-languages/02-give-values-names-and-units.md

PURPOSE:
Name a whole-cents amount and compare a declaration in six languages.

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

# Give values names and units

[Course contents](index.md) · [Previous · Follow instructions on paper](01-follow-instructions-on-paper.md) · [Next · Make a decision with if](03-decide-with-an-if.md) · [Browser edition](../../../courses/programming-across-languages/lessons/02-give-values-names-and-units.html)

Name a whole-cents amount and compare a declaration in six languages.

## Read a name

A value is a piece of information such as the number 200. A variable gives a place in the program a name such as `amount_cents`. A type describes the kind of value expected there.

```text
SET amount cents TO the whole number 200
SHOW amount cents
```

## Compare the declarations

- C, C++ and D can say `int amount_cents = 200;` inside a function. In this example, `int` is the name of a whole-number type.
- Java can write `int amountCents = 200;`. The different spelling of the variable follows a Java naming convention.
- Go can write `amountCents := 200` inside a function. The compiler infers the type from the starting value.
- Python can write `amount_cents = 200`. The name refers to a whole-number object. It can later refer to a different kind of object, so keep the unit stable by convention.

## Keep the unit with the number

Whole cents preserve the exact amounts in this example. A type such as `int` has a finite range in C, C++, Java, Go and D. A real sum must validate that its result fits. Python integers grow as needed within available resources.

## Try it

Name a 375-cent donation. Name a 375-month duration. Which two names would help someone catch a unit mix-up?

One answer is `donation_cents` and `duration_months`. Use that same explicit unit in your Studio IDE project tests and on your synthetic Bank screen.

## Continue in another course

- [Computing from the Beginning](../../../courses/computing-from-the-beginning/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python keyword reference](../../../courses/python-keyword-reference/index.html)
- [Go keyword reference](../../../courses/go-keyword-reference/index.html)
- [Go statement tools](../../../courses/go-statement-tools/index.html)
- [Umicom C and C23 statement calculations](../../../courses/native-statement-calculations/index.html)

[Course contents](index.md) · [Previous · Follow instructions on paper](01-follow-instructions-on-paper.md) · [Next · Make a decision with if](03-decide-with-an-if.md) · [Browser edition](../../../courses/programming-across-languages/lessons/02-give-values-names-and-units.html)
