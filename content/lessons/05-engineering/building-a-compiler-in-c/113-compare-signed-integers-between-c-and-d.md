<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/113-compare-signed-integers-between-c-and-d.md

PURPOSE:
Compare signed integers between C and D

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Compare signed integers between C and D

A comparison asks a question about two values. In this exercise, the question is whether a fictional count of 38 has reached a threshold of 32. Start with paper and a pencil. You can follow the result without installing any software.

## Read the symbols as questions

A **signed integer** is a whole number that can be below zero, zero or above zero. On a number line, `-2 < 1` is true. The number −2 is to the left of 1.

| Symbol | Question |
| --- | --- |
| `<` | Is the left value smaller? |
| `<=` | Is it smaller or equal? |
| `>` | Is it larger? |
| `>=` | Is it larger or equal? |
| `==` | Are the values equal? |
| `!=` | Are the values different? |

A single `=` assigns a value in this exercise. The double sign `==` asks whether two values match. The computer answers a comparison with one of two outcomes. C produces an integer, with 1 for true and 0 for false. D produces a **Boolean**, which is a value that can be true or false. D can convert true to 1 or false to 0 when a Boolean goes into the integer local used here.

## Trace the threshold by hand

The earlier shift rule turns `1 << 5` into 32 by doubling 1 five times. The parentheses around that shift show which number to compare with `units`. The variable `admitted` then holds the integer version of the comparison result.

~~~text
SET units TO 38
SET threshold TO 32
ASK whether units is at least threshold
IF the answer is true, SET admitted TO 1
OTHERWISE, SET admitted TO 0
RETURN units plus admitted times 4
~~~

The answer is true because 38 is at least 32. Calculate `38 + (1 × 4)` and check for 42. Now predict the result if the count starts at 31. The comparison then produces 0 in the integer local, so the result is 31.

## Translate one signed comparison between C and D

### 1. Save the C23 input

Save this program as `with-comparisons.c` in a new practice folder. Use an Umicom C CLI that supports signed comparisons in the C and D directions.

~~~c
int answer(void) {
    int units = 38;
    int admitted = (units >= (1 << 5));
    return units + (admitted * 4);
}
~~~

### 2. Compare the generated D and C text

Run the following commands from that folder in PowerShell. Choose fresh output names. Stop if a command reports a diagnostic.

~~~powershell
umicom-c translate c-to-d with-comparisons.c with-comparisons.d
umicom-c translate d-to-c with-comparisons.d with-comparisons-roundtrip.c
~~~

The expected D file has an empty parameter list and the same statements inside its braces.

~~~d
int answer() {
    int units = 38;
    int admitted = (units >= (1 << 5));
    return units + (admitted * 4);
}
~~~

The D comparison produces a Boolean, which the declaration stores as an integer. Open `with-comparisons-roundtrip.c` and compare it with the original C program. Check the comparison, the parentheses and the final arithmetic.

### 3. Check the regenerated C result

A **caller** is a small program that asks this function for its result. If GCC with C23 support is available, save this as `verify-comparisons.c` beside the regenerated C file.

~~~c
#include <stdio.h>
int answer(void);
int main(void) { const int value=answer(); printf("%d\n",value); return value==42?0:1; }
~~~

~~~powershell
gcc -std=c23 -Wall -Wextra -Werror verify-comparisons.c with-comparisons-roundtrip.c -o verify-comparisons.exe
if ($LASTEXITCODE -ne 0) { throw 'C compilation failed.' }
.\verify-comparisons.exe
$LASTEXITCODE
~~~

Expect `42` followed by exit code `0`. Include both source files in the compile command so the caller can find the function. This exercise compares the generated D text and runs the regenerated C program. A D program run requires a separate D compiler check.

## Show your intended order with parentheses

The checked translator allows one comparison at each parenthesis level. When a comparison and a bitwise operator work together, put the operation you intend to complete first inside its own parentheses. Here `&` keeps the bits that are set in both integer values. The mask `0x3F` is decimal 63 and keeps the lowest six bits.

| Expression | First operation | Result |
| --- | --- | --- |
| `(42 & 0x3F) == 42` | The mask keeps 42, then the comparison asks whether it equals 42. | 1 in an integer context |
| `42 & (0x3F == 42)` | The comparison of 63 and 42 is false, then the mask keeps the bits shared with zero. | 0 |

Circle the inner pair of parentheses in each row. A pair creates a separate expression level. The two rows have the same symbols and a different order of work.

For a refusal exercise, save `int answer(void) { return 1 < 2 < 3; }` as `comparison-chain.c`. Translate it with a fresh destination.

~~~powershell
umicom-c translate c-to-d comparison-chain.c refused-comparison.d
~~~

Expect a syntax diagnostic for the chain. Check that the fresh destination remains absent. If you want to ask two distinct questions, give each comparison its own step and record each result in a named local. The existing C and Java translation directions keep their previous operator rules.

A Studio exercise can put the original and generated functions beside a paper trace. Check the first operation, the stored integer result and the returned value separately.

[C23 relational and equality expressions](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf) · [D comparison grammar](https://dlang.org/spec/expression.html) · [D Boolean conversion](https://dlang.org/spec/type.html#bool)

[Course contents](index.md) · [Previous lesson · Translate grouped integer literals between C and D](112-translate-grouped-integer-literals-between-c-and-d.md) · [Related lesson · Translate checked shifts between C and D](111-translate-checked-shifts-between-c-and-d.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/113-compare-signed-integers-between-c-and-d.html) · [C23 keyword reference](../../03-native-code/c23-keyword-reference/index.md) · [D keyword reference](../../03-native-code/d-keyword-reference/index.md)

[Next lesson · Watch one integer slot](114-watch-one-integer-slot.md)
