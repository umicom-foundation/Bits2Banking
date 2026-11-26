<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/umicom-c-keyword-reference/07-compare-negative-division.md

PURPOSE:
Compare negative division and remainder

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Compare negative division and remainder

When a number is divided into whole groups, the **quotient** is the
number of groups and the **remainder** is the part left over. A negative
quantity can represent a missing number of items. Imagine an inventory
exercise using a shortage of seven items and groups of three.

## Decide which whole number to use

On a number line, the exact result of dividing minus seven by three lies
between minus three and minus two. Moving towards zero gives minus two.
Moving down to the next whole number gives minus three. That second rule
is called **floor division**. The remainder changes when the quotient
changes.

| Whole-number rule | Quotient | Remainder | Check with multiplication and addition |
| --- | --- | --- | --- |
| Move towards zero | -2 | -1 | `(-2 × 3) + (-1) = -7` |
| Move down | -3 | 2 | `(-3 × 3) + 2 = -7` |

Use the same steps when reading unfamiliar source.

~~~text
START with signed quantity -7 and group size 3
CHOOSE the language's whole-number division rule
FIND the quotient using that rule
SUBTRACT quotient times group size from the original quantity
CHECK that the product plus the remainder gives the original quantity
~~~

## Run the checked Umicom C program

Save the following as `split-shortage.uc`.

~~~c
int main(void) {
    /* Keep both inputs signed so the example uses checked integer rules. */
    int quantity = -7;
    int group_size = 3;
    print(quantity / group_size);
    print(quantity % group_size);
    return 0;
}
~~~

1. Run `umicom-c run split-shortage.uc`. Expect `-2` and then `-1`.
   The command reports `Result: 0` after the displayed values.
2. Run `umicom-c compile split-shortage.uc split-shortage.umcb` and
   `umicom-c exec split-shortage.umcb`. Expect the same output and result.
3. Replace `-7` with `7` and run the source again. Predict the values
   first, then check for `2` and `1`. Restore the original quantity.

The file extension selects the Umicom C display operation. Keep the
group size positive and nonzero in this exercise. If the compiler
refuses the program, use a build that supports `print` in `.uc` files
and check the spelling and semicolons on the indicated line.

## Compare the spelling in other languages

These are expressions for small, signed integer quantities. The table
shows the language rules for the inputs used in the exercise.

| Language | Quotient expression | Remainder expression | Values |
| --- | --- | --- | --- |
| Umicom C, C23, D and Java | `(-7) / 3` | `(-7) % 3` | `-2`, `-1` |
| Python | `(-7) // 3` | `(-7) % 3` | `-3`, `2` |

Python uses `/` for a division that can keep a fractional part. Its
`//` operator chooses the floor for these integers. The `%` symbol
looks the same in the table, so make a habit of checking the chosen
quotient rule before you copy an expression.

To run the same two calculations in C23, save this complete example as
`split-shortage.c`.

~~~c
#include <stdio.h>

int main(void) {
    /* Use C's standard output library to display the same two values. */
    const int quantity = -7;
    const int group_size = 3;
    printf("%d\n%d\n", quantity / group_size, quantity % group_size);
    return 0;
}
~~~

In PowerShell run `clang -std=c23 -Wall -Wextra -Werror split-shortage.c -o split-shortage.exe`
and then `.\split-shortage.exe`. Expect the same first two lines shown
in the Umicom C exercise. The two programs use their own output spelling.

When building a small inventory exercise for an Umicom application,
decide how to represent a negative quantity. Include a negative case
and a positive case in the test data. Give both cases an expected
quotient and remainder before running the program.

[Course contents](index.md) · [Previous lesson](06-choose-an-action-and-classify-source.md) · [HTML edition](../../../courses/umicom-c-keyword-reference/lessons/07-compare-negative-division.html) · [Programming across languages](../../../courses/programming-across-languages/index.html)
