<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/03-group-data-and-results.md

PURPOSE:
Read short functions, group related facts and distinguish a missing object from a real one.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Group data and return results

[Course contents](index.md) · [Previous lesson: Choose an action and repeat it](02-choose-and-repeat.md) · [Next lesson: Control lifetime and access](04-control-lifetime-and-access.md)

Read short functions, group related facts and distinguish a missing object from a real one.

## Give a group a name

An entry can have an amount and a posted flag. A structure keeps both facts together. A field name after a dot reaches just that part of the entry. A union gives multiple views of a shared region. It needs a separate way to tell which kind of value is currently stored.

## Recognise absence and type

A pointer is a value that can name the location of an object. Use `nullptr` when there is no object selected. `sizeof` reports storage size, while `_Generic` selects an expression by type. A C byte is the unit measured by `sizeof`, and its bit count is set by the implementation.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `void` | `void clear(void) { }` | No result value. The void inside the parentheses makes the zero-parameter form explicit. |
| `return` | `int entry_count(void) { return 3; }` | Finish a function and, when the result type permits, give a value to the caller. |
| `struct` | `struct Entry { int cents; bool posted; };` | Group named fields that each have their own storage. |
| `union` | `union Reading { int units; double ratio; };` | Provide different member views of shared storage. Track which member is in use. |
| `enum` | `enum Phase { DRAFT, POSTED };` | Give a controlled family of integer constants meaningful names. |
| `typedef` | `typedef int WholeCents;` | Make another name for an existing type. This does not itself create a distinct integer type. |
| `const` | `const int opening_cents = 500;` | Prevent writes through an object of this const-qualified type. |
| `nullptr` | `struct Entry *selected = nullptr;` | Represent a null pointer, which points to no object. Check it before accessing a field. |
| `sizeof` | `sizeof(char)` | Ask how many C bytes the type or expression occupies. sizeof(char) is always 1. |
| `_Generic` | `_Generic(42, int: 1, default: 0)` | Select an expression by a compatible type. This example selects 1. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
GROUP an amount and a posting flag into one entry
IF the entry is posted, give its amount back
OTHERWISE give zero back
```

## Run the complete example

Save the whole program as `practice.c`. Open a terminal in that folder, then enter the command shown for your language.

Use PowerShell with a C23 GCC installation on your search path. If you already have MSYS2 UCRT64 GCC at its usual Windows location, enter `$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path` in that session.

```c
#include <stdio.h>

typedef int WholeCents;

struct Entry {
    WholeCents cents;
    bool posted;
};

static WholeCents posted_cents(struct Entry entry)
{
    return entry.posted ? entry.cents : 0;
}

int main(void)
{
    const struct Entry credit = {425, true};
    printf("%d\n", posted_cents(credit));
    return 0;
}
```

```powershell
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror practice.c -o practice.exe
if ($LASTEXITCODE -eq 0) { .\practice.exe }
```

Expected line

```text
425
```

Use a compiler that accepts C23. A dialect diagnostic means the compiler has not accepted the selected language mode. A missing header diagnostic can mean the platform toolchain or SDK is absent. If the optional forms in the table are unavailable, try the self-contained main program instead.

## Try a change

Set the posted field to false. Does that erase cents from the structure, or change only what the function returns?

**Check your answer**

The structure still stores 425. The filter function returns `0` for an entry that has not posted.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [WG14 public draft N3220, section 6.4.1 and Annex A](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)
