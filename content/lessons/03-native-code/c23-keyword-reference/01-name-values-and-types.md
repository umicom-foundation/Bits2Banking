<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/01-name-values-and-types.md

PURPOSE:
Read a first C declaration, then choose between whole numbers, truth values, characters and measurements.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Name values and choose their types

[Course contents](index.md) · [Next lesson: Choose an action and repeat it](02-choose-and-repeat.md)

Read a first C declaration, then choose between whole numbers, truth values, characters and measurements.

## Read a declaration aloud

A declaration introduces a name and tells the computer what kind of value belongs there. In `int cents = 425;`, read `int` as whole number, `cents` as the name, `=` as start with this value, `425` as the value, and `;` as the end. A character constant uses single quotes. Double quotes delimit a string, which stores text.

## Try this before opening a tool

Write `cents = 425` and `approved = false` on paper. Imagine that the computer makes a labelled space for each value. Change the amount to `-25`. A signed type can express this movement. An unsigned type models a count that never has a negative meaning.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `int` | `int cents = 425;` | A whole number. An int can represent 425 on every conforming implementation. |
| `char` | `char grade = 'A';` | A character-sized integer. Single quotes enclose a character constant. |
| `short` | `short bins = 12;` | A signed integer type with a relatively small minimum range. It need not occupy fewer bytes than int. |
| `long` | `long minutes = 100000L;` | A signed integer type with a larger guaranteed minimum range than int. L selects a long literal here. |
| `signed` | `signed int change = -25;` | Makes the signed integer choice visible when both negative and positive values are useful. |
| `unsigned` | `unsigned int count = 3u;` | An integer that cannot represent negative values. The u suffix makes this literal unsigned. Keep negative movements in a signed type. |
| `bool` | `bool accepted = false;` | The C23 truth-value type with the values false and true. |
| `false` | `bool approved = false;` | Starts a flag in the no state. |
| `true` | `bool checked = true;` | Starts a flag in the yes state. |
| `float` | `float height = 1.25f;` | A floating-point type for measurements. The f suffix gives the literal this type. |
| `double` | `double width = 1.25;` | The type of an ordinary unsuffixed floating literal. Use whole cents for the statement exercises. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
START cents at 425
ADD movement of -25 to cents
SHOW the new cents and the approval flag
```

## Run the complete example

Save the whole program as `practice.c`. Open a terminal in that folder, then enter the command shown for your language.

Use PowerShell with a C23 GCC installation on your search path. If you already have MSYS2 UCRT64 GCC at its usual Windows location, enter `$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path` in that session.

```c
#include <stdio.h>

int main(void)
{
    int cents = 425;
    signed int movement = -25;
    bool approved = false;
    printf("%d %s\n", cents + movement, approved ? "yes" : "no");
    return 0;
}
```

```powershell
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror practice.c -o practice.exe
if ($LASTEXITCODE -eq 0) { .\practice.exe }
```

Expected line

```text
400 no
```

Use a compiler that accepts C23. A dialect diagnostic means the compiler has not accepted the selected language mode. A missing header diagnostic can mean the platform toolchain or SDK is absent. If the optional forms in the table are unavailable, try the self-contained main program instead.

## Try a change

Change approval to true and predict the output before running. Explain why the count of receipts could use unsigned while a movement may need a sign.

**Check your answer**

The new line is `400 yes`. A receipt count is nonnegative. A refund or reversal can create a negative movement.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [WG14 public draft N3220, section 6.4.1 and Annex A](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)
