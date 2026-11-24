<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/111-translate-checked-shifts-between-c-and-d.md

PURPOSE:
Translate checked shifts between C and D

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Translate checked shifts between C and D

Start with four pieces of paper. Write `1`, `32`, `42` and `21` on them. They are the values stored in one variable as the program runs. Follow the changes before reading the syntax. The final calculation returns `42` to the caller.

## Move a bit one place at a time

A bit is a digit that can be zero or one. A whole number written in binary uses bits in places worth 1, 2, 4, 8 and so on, starting at the right. The binary digits `000001` represent 1. Moving that one bit five places left gives `100000`, which represents 32. The operator `<<` moves left and `>>` moves right. The number on the right of the operator is the number of places to move.

In this exercise, the input to a shift is nonnegative and the result fits in a signed 32-bit integer. Each left move doubles the value. Each right move halves it and discards any remainder. For example, `43 >> 1` gives 21. The assignment forms `<<=` and `>>=` store the new result in the same variable.

~~~text
SET total TO 1
SHIFT total LEFT BY 5 AND STORE IT    total is 32
ADD 10 TO total                       total is 42
SHIFT total RIGHT BY 1 AND STORE IT   total is 21
RETURN total TIMES 2                  answer is 42
~~~

This pseudocode describes the steps in plain language. The column on the right is a paper trace of the value. The final line calculates the returned value. At that line the local `total` still contains 21.

## Translate the C23 function and read the D output

### 1. Save the C23 source

Open a fresh practice folder. Save the example as `with-shifts.c`. Use a version of the Umicom C CLI that supports checked shifts in both translation directions.

~~~c
int answer(void) {
    int total = 1;
    total <<= 5;
    total += 10;
    total >>= 1;
    return total * 2;
}
~~~

### 2. Translate in both directions

Open PowerShell in the practice folder. Run these commands with fresh output names. Stop if the first command reports an error.

~~~powershell
umicom-c translate c-to-d with-shifts.c with-shifts.d
umicom-c translate d-to-c with-shifts.d with-shifts-roundtrip.c
~~~

### 3. Read the generated D file

Open `with-shifts.d`. Compare it with the expected D output below. The two function headers both describe a function with no parameters. The C example spells it with `(void)`. The D output has empty parentheses. Each statement inside the braces is the same.

~~~d
int answer() {
    int total = 1;
    total <<= 5;
    total += 10;
    total >>= 1;
    return total * 2;
}
~~~

### 4. Compare the regenerated C file

Open `with-shifts-roundtrip.c`. Check that the function header uses `(void)` again and that all five statements match the first example. A round trip means translating to D and back to C. The generated file can have a different line-ending convention from a file saved in your editor.

## Check the regenerated C function

A caller is a small program that asks the function for its result. If you have GCC with C23 support, save this caller as `verify-shifts.c` in the same practice folder. It prints the result and uses exit code 0 for a match.

~~~c
#include <stdio.h>
int answer(void);
int main(void) { const int value=answer(); printf("%d\n",value); return value==42?0:1; }
~~~

~~~powershell
gcc -std=c23 -Wall -Wextra -Werror verify-shifts.c with-shifts-roundtrip.c -o verify-shifts.exe
if ($LASTEXITCODE -ne 0) { throw 'C compilation failed.' }
.\verify-shifts.exe
$LASTEXITCODE
~~~

Expect `42` on the first line, followed by exit code `0`. If the compiler cannot find `answer`, check that both source files appear in the command. The comparison here verifies the generated D text, then compiles and runs the C copy made from it. Executing the D program requires a separate D compiler check.

## Predict which shifts the translator refuses

Use this paper check before trying a new shift. A signed 32-bit integer stores whole numbers through `2147483647` on the positive side. The checked translator accepts a count from 0 through 31, including both endpoints.

~~~text
IF the left value is below zero, REFUSE
IF the count is below zero or above 31, REFUSE
FIND the exact result of the move before storing it
IF the result exceeds 2147483647, REFUSE
RETURN the result
~~~

| D return expression | Expected result from this translation profile | Why |
| --- | --- | --- |
| `-1 >> 1` | Arithmetic refusal | The checked profile requires a nonnegative left value. |
| `1 << -1` | Arithmetic refusal | A shift count cannot be negative here. |
| `1 << 32` | Arithmetic refusal | The largest allowed count is 31. |
| `1 << 31` | Arithmetic refusal | The count fits, and the result `2147483648` exceeds the positive limit. |
| `42 >>> 1` | Syntax refusal | D has an unsigned right shift, and this checked profile accepts `<<` and `>>`. |
| `1 < < 5` | Syntax refusal | A space inside `<<` splits the shift into two tokens. A token is one meaningful piece of source text. |

For a refusal you can try, save `int answer() { return 1 << 31; }` as `too-large.d` and run `umicom-c translate d-to-c too-large.d refused.c`. Expect an arithmetic diagnostic. With a fresh destination name, check that `refused.c` was left absent. Restore `with-shifts.d` as your input when checking the original example again.

These are the rules of Umicom C’s checked C and D translation profile. D has other valid expressions and can be used outside this exercise. An editor such as Umicom Studio IDE can present the two translated files side by side and show a diagnostic for a refused expression. Compare the earlier shift lesson for more practice checking the arithmetic one step at a time.

[D shift expressions](https://dlang.org/spec/expression.html#shiftexpression)

[Course contents](index.md) · [Previous lesson · Inspect paused integer slots](110-inspect-paused-integer-slots.md) · [Related lesson · Check bit shifts before publishing a result](86-check-bit-shifts-before-publishing-a-result.md) · [Related lesson · Translate an initialized local between C and D](109-translate-an-initialized-local-between-c-and-d.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/111-translate-checked-shifts-between-c-and-d.html) · [D keyword reference](../../03-native-code/d-keyword-reference/index.md)

[Next lesson · Translate grouped integer literals between C and D](112-translate-grouped-integer-literals-between-c-and-d.md)
