<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/04-control-lifetime-and-access.md

PURPOSE:
Tell apart where a name can be seen, how long data survives and which code can use it.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Control lifetime and access

[Course contents](index.md) · [Previous lesson: Group data and return results](03-group-data-and-results.md) · [Next lesson: Check types and representations](05-check-types-and-representations.md)

Tell apart where a name can be seen, how long data survives and which code can use it.

## Observe a value across two calls

Normally a local variable belongs to one call. The static example below stores the count beyond a single call. Call the function twice and ask how the second call differs from the first. Use separate calls so statement order is clear.

## Separate access from synchronization

Use one worker at first. The meanings of `volatile`, `restrict` and `thread_local` solve different problems. A volatile read can be useful at an approved device boundary. A restrict-qualified pointer carries obligations about accesses during execution. A thread-local variable gives each worker a separate count. None of these choices alone coordinates shared access.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `auto` | `auto cents = 425;` | In this C23 declaration, an initializer supplies the inferred type. Older C used auto as a storage-class marker. |
| `static` | `static int visits;` | Inside a function the value survives later calls. At file scope static limits the name's linkage to that source unit. |
| `extern` | `extern int shared_count;` | Declare an object whose definition is found elsewhere, such as in another source unit. |
| `register` | `register int slot = 0;` | Historical storage class for a local object. C does not guarantee a hardware register, and taking this object's address is prohibited. |
| `thread_local` | `thread_local int view_count;` | Each thread gets its own object. Use this form at file scope, or use the required storage-class combination at block scope. |
| `inline` | `static inline int square(int n) { return n * n; }` | Prefer inline expansion where beneficial, without requiring an optimizer to substitute the body. |
| `constexpr` | `constexpr int max_rows = 3;` | Define a named C23 constant object suitable for constant expressions. C++ also uses constexpr on certain functions. |
| `volatile` | `int read_status(const volatile int *status) { return *status; }` | Access the pointed-to value with volatile semantics. It is not a way to synchronize threads. |
| `restrict` | `void copy(int *restrict out, const int *restrict in) { *out = *in; }` | Promise the required access relationship for the pointed-to data. For this example, keep the input and output as separate objects. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
KEEP one count between calls
EACH time a view is requested, increase the count and give it back
```

## Run the complete example

Save the whole program as `practice.c`. Open a terminal in that folder, then enter the command shown for your language.

Use PowerShell with a C23 GCC installation on your search path. If you already have MSYS2 UCRT64 GCC at its usual Windows location, enter `$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path` in that session.

```c
#include <stdio.h>

static int next_view(void)
{
    static int views = 0;
    return ++views;
}

int main(void)
{
    int first = next_view();
    int second = next_view();
    printf("%d %d\n", first, second);
    return 0;
}
```

```powershell
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror practice.c -o practice.exe
if ($LASTEXITCODE -eq 0) { .\practice.exe }
```

Expected line

```text
1 2
```

Use a compiler that accepts C23. A dialect diagnostic means the compiler has not accepted the selected language mode. A missing header diagnostic can mean the platform toolchain or SDK is absent. If the optional forms in the table are unavailable, try the self-contained main program instead.

## Try a change

Change static int views to int views. Predict both numbers. Ask which value format would suit a counter that deliberately restarts on each call.

**Check your answer**

A fresh local variable starts at zero each time, so the new line is `1 1`.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [WG14 public draft N3220, section 6.4.1 and Annex A](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)
