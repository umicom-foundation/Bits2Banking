<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/05-check-types-and-representations.md

PURPOSE:
Inspect memory requirements and types, then make a build reject a broken assumption.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Check types and representations

[Course contents](index.md) · [Previous lesson: Control lifetime and access](04-control-lifetime-and-access.md) · [Next lesson: Read optional and older forms](06-read-optional-and-older-forms.md)

Inspect memory requirements and types, then make a build reject a broken assumption.

## Separate size from placement

Size tells you how much space a type needs. Alignment tells you which memory positions are acceptable for storing it. Imagine a shelf grid where a container must begin at every second square. Its width is a different question from the set of places at which you may start it.

## State a promise that the tool checks

A static assertion is checked during translation, before the program can run. Use one to explain a requirement. During exploration let a failed assertion tell you which assumption needs review. In the example `typeof_unqual` copies the type of a read-only int without making the copy read-only.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `alignas` | `alignas(int) unsigned char buffer[sizeof(int)];` | Request storage that meets the alignment needed by int. Matching alignment alone does not turn this array into an int. |
| `alignof` | `alignof(int)` | Ask the implementation which alignment an int needs. |
| `static_assert` | `static_assert(sizeof(char) == 1, "one C byte");` | Stop translation if a constant assumption is false. |
| `typeof` | `const int rate = 3; typeof(rate) copy = 4;` | Use the type of rate, retaining its const qualification in this example. |
| `typeof_unqual` | `const int rate = 3; typeof_unqual(rate) copy = 4;` | Use the unqualified version of the type. The new copy can be assigned another value. |
| `_Atomic` | `_Atomic(int) work_count = 0;` | Use an atomic integer object when individually atomic operations are needed. A sequence of operations may still need coordination. |
| `_BitInt` | `unsigned _BitInt(9) flags = 257;` | Declare a 9-bit unsigned integer. A storage byte count can exceed the bit width's minimum size. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
CHECK the size assumption before running
COPY the type of source without its read-only label
COPY the value and add 3 to the editable copy
```

## Run the complete example

Save the whole program as `practice.c`. Open a terminal in that folder, then enter the command shown for your language.

Use PowerShell with a C23 GCC installation on your search path. If you already have MSYS2 UCRT64 GCC at its usual Windows location, enter `$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path` in that session.

```c
#include <stdio.h>

static_assert(sizeof(char) == 1, "one C byte");

int main(void)
{
    const int source = 4;
    typeof_unqual(source) editable = source;
    editable += 3;
    printf("%d\n", editable);
    return 0;
}
```

```powershell
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror practice.c -o practice.exe
if ($LASTEXITCODE -eq 0) { .\practice.exe }
```

Expected line

```text
7
```

Use a compiler that accepts C23. A dialect diagnostic means the compiler has not accepted the selected language mode. A missing header diagnostic can mean the platform toolchain or SDK is absent. If the optional forms in the table are unavailable, try the self-contained main program instead.

## Try a change

Change typeof_unqual to typeof in the small program. Predict which line the compiler should reject, then restore the working form.

**Check your answer**

The declaration selects a const type after the change. `editable += 3;` attempts to change the const object, so translation should report an error.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [WG14 public draft N3220, section 6.4.1 and Annex A](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)
