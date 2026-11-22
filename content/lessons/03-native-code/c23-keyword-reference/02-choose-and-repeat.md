<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/02-choose-and-repeat.md

PURPOSE:
Make one decision, then repeat safe actions over a short list of pretend entries.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Choose an action and repeat it

[Course contents](index.md) · [Previous lesson: Name values and choose their types](01-name-values-and-types.md) · [Next lesson: Group data and return results](03-group-data-and-results.md)

Make one decision, then repeat safe actions over a short list of pretend entries.

## Follow the loop by hand

A loop repeats a set of steps. Start at position zero, and keep going while the position is smaller than three. First write 0, then 1, then 2. When the test sees 3, stop before printing it. C, C++ and Java have a closely related three-part for form. Go omits the parentheses. Python normally asks for each item from a range or list.

## Trace a branch

The program below skips the second row. The statement `continue;` takes you directly to the loop update. The third row is still considered. The array is a list of three values, and `amounts[row]` selects one value by its position.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `if` | `if (count > 0) total += 5;` | Run the next statement only when the condition is true. |
| `else` | `if (count > 0) total++; else total = 0;` | Choose a fallback when if does not run. Braces make either branch easier to read. |
| `for` | `for (int i = 0; i < 3; ++i) total += i;` | Start once, test before each turn, and update after each completed turn. |
| `while` | `while (count > 0) --count;` | Test first and repeat as long as the condition remains true. |
| `do` | `do { --count; } while (count > 0);` | Run the body once before the first test. This form ends with a semicolon. |
| `break` | `while (true) { break; }` | Leave the nearest enclosing loop or switch. |
| `continue` | `for (int i = 0; i < 3; ++i) { if (i == 1) continue; total += i; }` | Skip the rest of this turn. In this for loop the update still runs. |
| `switch` | `switch (code) { case 1: total += 5; break; default: break; }` | Choose a label based on an integer expression. |
| `case` | `case 1: total += 5; break;` | Marks a constant selection within a switch. Without a jump such as break, execution can proceed into the next block. |
| `default` | `default: total = 0; break;` | Marks the fallback case when no explicit case matches. |
| `goto` | `if (failed) goto finished; total++; finished: return total;` | Jump to a label inside the same function. Prefer ordinary branches and loops for simple flow. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
START total at 0
FOR each position from 0 through 2
    IF position is 1, skip this turn
    ADD the entry to total
SHOW total
```

## Run the complete example

Save the whole program as `practice.c`. Open a terminal in that folder, then enter the command shown for your language.

Use PowerShell with a C23 GCC installation on your search path. If you already have MSYS2 UCRT64 GCC at its usual Windows location, enter `$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path` in that session.

```c
#include <stdio.h>

int main(void)
{
    const int amounts[] = {425, -25, 100};
    int total = 0;
    for (int row = 0; row < 3; ++row) {
        if (row == 1) {
            continue;
        }
        total += amounts[row];
    }
    printf("%d\n", total);
    return 0;
}
```

```powershell
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror practice.c -o practice.exe
if ($LASTEXITCODE -eq 0) { .\practice.exe }
```

Expected line

```text
525
```

Use a compiler that accepts C23. A dialect diagnostic means the compiler has not accepted the selected language mode. A missing header diagnostic can mean the platform toolchain or SDK is absent. If the optional forms in the table are unavailable, try the self-contained main program instead.

## Try a change

Change the condition to skip row 2. Write down which two numbers will be added. Work this out on paper first.

**Check your answer**

Positions 0 and 1 contribute 425 and -25. The result is `400`.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [WG14 public draft N3220, section 6.4.1 and Annex A](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)
