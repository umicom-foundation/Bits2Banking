<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/115-translate-short-circuit-conditions-across-c-and-d.md

PURPOSE:
Translate short-circuit conditions across C23 and D

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Translate short-circuit conditions across C23 and D

A condition answers a yes-or-no question. Short-circuit evaluation lets the program stop checking a condition as soon as the answer is known. In this lesson, you will predict which part runs, translate the same small function between C23 and D, and see why the function returns 42.

## 1. Start on the left

In an integer condition, zero means false and any nonzero value means true. The left and right parts of an operator are called **operands**. In C23 and D, `&&` and `||` begin with the left operand.

| Operator | Read it as | What can settle the answer early |
| --- | --- | --- |
| `!` | NOT | It reads one operand. An integer equal to zero gives true. A nonzero integer gives false. |
| `&&` | AND | A false left side settles the result as false. The right side is skipped. |
| `||` | OR | A true left side settles the result as true. The right side is skipped. |

Put a finger on the left operand before reading the right. In `0 && (2 < 3)`, the zero settles the answer. In `1 || (2 < 3)`, the one settles the answer. The comparison can be read and checked as source in both examples. The running program skips the comparison.

This matters when a later calculation needs an earlier check. Before dividing by an integer, you can arrange for the program to check that the divisor is nonzero first. Trace this idea on paper with a divisor of 0 and then a divisor of 4.

~~~text
IF the divisor is nonzero
    TEST whether 12 divided by the divisor is greater than 2
ELSE
    SET the answer TO false
~~~

When the divisor is 0, you get false without doing the division. When the divisor is 4, you calculate 3 and get true. This is the step-by-step meaning of `(divisor != 0) && (12 / divisor > 2)`.

## 2. Trace the same function before translating

Save this function as `with-logical.c` in a practice folder.

~~~c
int answer(void) {
    int ready = 0;
    int permitted = (ready != 0) || (2 < 3);
    return (permitted && !ready) * 42;
}
~~~

1. `ready` starts at 0, so the comparison `(ready != 0)` gives false. OR still needs an answer from its right side.
2. `(2 < 3)` gives true. The integer `permitted` therefore receives 1.
3. The left side of `permitted && !ready` is true. AND checks `!ready`, which is also true because `ready` is zero. The result is 1 in the multiplication, so `answer` returns 42.

Change the starting value to 1 on paper and trace the same lines. The left side of OR now gives true, so it skips `(2 < 3)`. AND then checks `!ready`, which gives false. The function would return 0. Keep the saved C file at its original value of 0 for the translation exercise.

## 3. Translate there and back

Run the two commands from your practice folder if you have a build of the Umicom C translator that supports this checked profile. Use fresh output filenames. If translation is refused, keep the source and check the first source location in the diagnostic before trying a new output name.

~~~powershell
umicom-c translate c-to-d with-logical.c with-logical.d
umicom-c translate d-to-c with-logical.d with-logical-roundtrip.c
~~~

The generated D function has empty parameter parentheses after `answer`. Compare the inner expressions with your original C file.

~~~d
int answer() {
    int ready = 0;
    int permitted = (ready != 0) || (2 < 3);
    return (permitted && !ready) * 42;
}
~~~

C23’s integer logical operators produce `int` values 0 or 1. D’s logical expressions in this example produce `bool`. D converts false to 0 and true to 1 in the integer assignment and multiplication. The result of the written calculation is the same in the two languages.

The generated C file returns to the original text. A function called `answer` does the calculation. A separate `main` function lets you run it and print its result. Save the following small driver as `driver.c`.

~~~c
#include <stdio.h>
int answer(void);
int main(void) { const int value=answer(); printf("%d\n",value); return value==42?0:1; }
~~~

Compile the driver together with the generated C file. Run the example only after the compile succeeds. You can use any C23 compiler with equivalent options. This sample command uses GCC in PowerShell.

~~~powershell
gcc -std=c23 driver.c with-logical-roundtrip.c -o logical-check.exe
if ($LASTEXITCODE -eq 0) { .\logical-check.exe }
~~~

The stored C check printed this value. The D text was checked against the expected translation. Running the D file needs a separate D compiler.

~~~text
42
~~~

## 4. Show the grouping you mean

For the checked translator, group each comparison with parentheses, as in `(ready != 0) || (2 < 3)`. Group the whole answer before using it in another calculation, as in `(permitted && !ready) * 42`. If the translator refuses an expression, check that each operand is complete and that the two characters in `&&` or `||` touch. The checked translator can require parentheses even in a C expression that ordinary C accepts.

Single `&` and `|` work on individual bits. They use both operands. For example, `2 & 1` gives 0 because the binary digits `10` and `01` have no position where both are 1. The logical expression `2 && 1` gives true because both integers are nonzero. In a Studio IDE review, put the safety check on the left when you need it to decide whether the right side can run.

[C working draft, sections 6.5.13 and 6.5.14](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf#page=107) · [D logical expressions](https://dlang.org/spec/expression.html#logical_expressions) · [D Boolean conversions](https://dlang.org/spec/type.html#bool)

[Course contents](index.md) · [Previous lesson · Watch one integer slot](114-watch-one-integer-slot.md) · [Related lesson · Compare signed integers between C and D](113-compare-signed-integers-between-c-and-d.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/115-translate-short-circuit-conditions-across-c-and-d.html) · [C23 keyword reference](../../03-native-code/c23-keyword-reference/index.md) · [D keyword reference](../../03-native-code/d-keyword-reference/index.md)

[Next lesson · Read the instruction budget at a pause](116-read-the-instruction-budget-at-a-pause.md)
