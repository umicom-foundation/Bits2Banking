<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/umicom-c-keyword-reference/05-guard-calculations-with-and-or.md

PURPOSE:
  Teach short-circuit evaluation through a guarded integer exercise in Umicom pseudocode and C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Guard calculations with AND and OR

[Course contents](index.md) · [Previous lesson](04-call-the-checked-input-profile.md) · [Earlier lesson on if and else](02-choose-with-if-and-literals.md)

## Use both checks or either check

A condition asks a question. The answer is true or false. Use `AND` when two questions must both have a true answer. Use `OR` when one true answer is enough.

| Left answer | Right answer | AND | OR |
| --- | --- | --- | --- |
| false | false | false | false |
| false | true | false | true |
| true | false | false | true |
| true | true | true | true |

The checked Umicom pseudocode profile starts each combined condition with the left expression. If it already knows the answer, it skips the right expression. This is called **short-circuit evaluation**. With `AND`, a false left side settles the answer. With `OR`, a true left side settles it.

## Trace a guarded division

Imagine an Umicom Bank training screen that reviews a batch of pretend entries. There are zero entries, and you want to avoid dividing by the count. Save the following as `guarded-review.ump`.

~~~text
BEGIN
    LET entries = 0;
    LET total = 12;
    LET review = 0;
    IF (entries != 0 AND total / entries > 3) THEN BEGIN
        review = 1;
    END
    IF (entries == 0 OR total / entries > 3) THEN BEGIN
        review = review + 2;
    END
    RETURN review;
END
~~~

First trace it on paper. The first comparison is false, so the interpreter skips the division and leaves `review` at zero. The second comparison is true, so it skips that division too and adds two. It returns 2.

Run `umicom-c pseudocode guarded-review.ump` with an Umicom C build containing the checked logical words. The command prints the returned integer. Then change `entries` to 3 and run again. Both divisions are now reached safely. Each yields 4, and the review value becomes 3.

To see a real error, go back to zero entries and change `entries != 0` to `entries >= 0` in the first condition. The left side is true and the division is evaluated. Expect the checked interpreter to report division by zero. Restore the first comparison afterwards.

## Compare the C form

C uses `&&` for AND and `||` for OR. The same decisions in plain C read as follows.

~~~c
int main(void)
{
    int entries = 0;
    int total = 12;
    int review = 0;
    if (entries != 0 && total / entries > 3) {
        review = 1;
    }
    if (entries == 0 || total / entries > 3) {
        review = review + 2;
    }
    return review;
}
~~~

Save this as `guarded-review.c`. Use `umicom-c interpret guarded-review.c` to see the same result. The checked `pseudocode` command recognises `AND` and `OR` in expressions. Keep the symbolic forms in a C source file.

## Decide which operation groups first

When you write `1 OR 0 AND 0`, the interpreter groups AND first. It reads the expression as `1 OR (0 AND 0)`, which returns 1. Writing `(1 OR 0) AND 0` gives 0 because the parentheses change the grouping.

~~~text
BEGIN
    RETURN 1 OR 0 AND 0;
END
~~~

Save that example as `group-the-checks.ump`. Run it as written. Then add the parentheses from the second form and run it again. When you read a longer condition in Studio, add parentheses where they make your intended grouping easier to see. Keep a guard on the left when evaluating the right side would fail for some inputs.

In an application, identify the required data check before evaluating values that depend on it. Follow that rule in paper examples and in the corresponding C tests. These exercises use synthetic integer counts and pass no real banking data to the interpreter.

[HTML edition](../../../courses/umicom-c-keyword-reference/lessons/05-guard-calculations-with-and-or.html) · [Related C23 keywords](../c23-keyword-reference/index.md)

[Next lesson](06-choose-an-action-and-classify-source.md)
