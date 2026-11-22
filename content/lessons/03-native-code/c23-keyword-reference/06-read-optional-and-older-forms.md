<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/06-read-optional-and-older-forms.md

PURPOSE:
Identify an optional feature, a reserved spelling or a compatibility spelling before you try to use it.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Read optional and older forms

[Course contents](index.md) · [Previous lesson: Check types and representations](05-check-types-and-representations.md) · [Continue to Native Statement Calculations](../../../courses/native-statement-calculations/index.html)

Identify an optional feature, a reserved spelling or a compatibility spelling before you try to use it.

## Read examples in their intended environments

A reserved spelling may have an optional meaning, or may identify a form that older code used. Decimal floating types are conditional. A capable C23 implementation advertises its decimal floating support through `__STDC_IEC_60559_DFP__`. A name can remain reserved on compilers that cannot use it as a type.

## Keep preprocessing separate

`#include` is a directive. `__STDC_VERSION__` is a predefined version macro in C23. `__func__` is a predefined function-name identifier, and `[[noreturn]]` is attribute syntax. These tools can look as prominent as keywords but obey different rules. The next example prints the current function's name.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `_Complex` | `double _Complex signal = 2.0;` | Represent real and imaginary components with a complex type. This initialisation uses an imaginary component of zero. Check the implementation's complex support. |
| `_Decimal32` | `_Decimal32 rate = 1.25df;` | Use the 32-format decimal floating type where the implementation provides it. df is the matching literal suffix. |
| `_Decimal64` | `_Decimal64 rate = 1.25dd;` | Use the 64-format decimal floating type where the implementation provides it. dd is the matching literal suffix. |
| `_Decimal128` | `_Decimal128 rate = 1.25dl;` | Use the 128-format decimal floating type where the implementation provides it. dl is the matching literal suffix. |
| `_Imaginary` | `int _Imaginary = 1;` | Deliberately invalid as a variable name. The spelling is reserved. Annex G describes imaginary types where supplied. |
| `_Noreturn` | `_Noreturn void stop_now(void) { abort(); }` | An obsolescent promise that the function will not return. Include <stdlib.h> for abort. New C23 code can use [[noreturn]]. |
| `_Alignas` | `_Alignas(int) unsigned char buffer[sizeof(int)];` | Older spelling for alignas. |
| `_Alignof` | `_Alignof(int)` | Older spelling for alignof. |
| `_Bool` | `_Bool approved = 0;` | Older spelling for bool. Zero makes the value false. |
| `_Static_assert` | `_Static_assert(sizeof(char) == 1, "one C byte");` | Older spelling for static_assert. |
| `_Thread_local` | `_Thread_local int view_count;` | Older spelling for thread_local. This example belongs at file scope. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
LOOK UP the spelling
CHECK whether it is a keyword or belongs to another category
CHECK whether the target supports the feature before you rely on it
```

## Run the complete example

Save the whole program as `practice.c`. Open a terminal in that folder, then enter the command shown for your language.

Use PowerShell with a C23 GCC installation on your search path. If you already have MSYS2 UCRT64 GCC at its usual Windows location, enter `$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path` in that session.

```c
#include <stdio.h>

int main(void)
{
    puts(__func__);
    return 0;
}
```

```powershell
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror practice.c -o practice.exe
if ($LASTEXITCODE -eq 0) { .\practice.exe }
```

Expected line

```text
main
```

Use a compiler that accepts C23. A dialect diagnostic means the compiler has not accepted the selected language mode. A missing header diagnostic can mean the platform toolchain or SDK is absent. If the optional forms in the table are unavailable, try the self-contained main program instead.

## Try a change

Sort these spellings into C23 keyword, alternate spelling, preprocessing directive and attribute: constexpr, _Bool, #include, [[noreturn]].

**Check your answer**

`constexpr` is a keyword. `_Bool` is an alternate spelling. `#include` is a directive. `[[noreturn]]` is an attribute form.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [WG14 public draft N3220, section 6.4.1 and Annex A](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)
