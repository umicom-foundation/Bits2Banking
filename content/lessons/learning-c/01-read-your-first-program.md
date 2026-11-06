First programs · Lesson 1 of 7

# Your first C program

This lesson explains what a C program is and how to read a very small one. You do not need to install anything yet. By the end, you will be able to point to the instruction that displays a message and say what that message will be.

## 1. Start with a text file

A computer program is a set of instructions. C is a language for writing those instructions. It has rules about words and punctuation, just as a spoken language has rules about sentences. A **source file** holds the instructions as ordinary text. The name `hello.c` has two parts: `hello` is the name chosen for the file, and `.c` tells people and tools that it contains C source.

A text editor lets you read and change that text. Umicom Studio IDE includes a text editor. Opening a source file does not run the program, just as opening a recipe does not prepare a meal. We will learn how to run it in the next lesson.

## 2. Read this complete program

```c
#include <stdio.h>

int main(void)
{
    puts("Hello from Bits2Banking.");
    return 0;
}
```

The program asks the computer to display one line:

```text
Hello from Bits2Banking.
```

## 3. Understand each line

| Source text | Meaning |
| --- | --- |
| `#include <stdio.h>` | Make the names for standard input and output operations available. A **library** is a collection of reusable operations. `stdio.h` is a **header**: a file that describes those operations to the compiler. |
| `int main(void)` | Define the function named `main`. A **function** is a named group of instructions. For this kind of program, execution starts in `main`. `int` means it returns a whole number. `void` here means it receives no input values. |
| `{` and `}` | The braces mark the beginning and end of the function's instructions. |
| `puts("Hello from Bits2Banking.");` | Call the library function `puts`. Calling a function means asking it to do its work. The text between double quotation marks is a **string**. `puts` displays that text and moves to a new line. The quotation marks are not displayed. |
| `return 0;` | Finish the function and report success to the program that started it. This does not print the number zero. |

The semicolon `;` ends each of the two instructions inside `main`. Spaces at the beginning of those lines make the grouping easier to see. They are called **indentation**.

## 4. Trace the order

```text
Start main
    ↓
Display Hello from Bits2Banking.
    ↓
Finish with success
```

Read the two instructions from top to bottom. The program does not ask for a name or open a window because neither instruction asks it to do so.

## 5. Try a small change

1. Copy the program onto paper or into your own text file.
2. Change only the text inside the quotation marks to `I am learning C.`
3. Write the exact output you expect. Do not include the quotation marks.
4. Find the semicolon after the closing parenthesis. Leave it in place.

### Answer

```text
I am learning C.
```

The change affects the message, not the starting function or the success result.

## Where this example lives

The complete example is `labs/native/first-c-programs/hello.c` in Bits2Banking. Its opening comment records its purpose, author and licence. Comments explain code to people and are not instructions to execute. This first example concentrates on displaying a line; later examples check whether output succeeded.

## Before moving on

You are ready when you can explain the difference between the source text, the displayed message and `return 0`. You do not need to memorise every line.

---

[Read this lesson in HTML](../../courses/learning-c/lessons/01-read-your-first-program.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

First programs · Lesson 1 of 7.

[Next: Build and run your first C program](02-build-and-run-one-step.md)

## Complete laboratory source

The short example above introduces the instructions. This is the complete source file, including its purpose and licence comment, for comparison with your local laboratory.

```c
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/hello.c
 *
 * PURPOSE:
 *   Introduce a first complete C program with one line of output.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdio.h>

int main(void)
{
    /* Keep the first example focused on sequence and text. The neighbouring
     * greeting example introduces checked output after decisions are taught. */
    puts("Hello from Bits2Banking.");
    return 0;
}
```
