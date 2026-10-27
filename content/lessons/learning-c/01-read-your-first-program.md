# Read a C program before running it

Recognise a program's starting point, its instructions and its result without needing a compiler.

**Before you begin:** Read the [computing foundation](../00-getting-started/index.md) if files, commands or an operating system are unfamiliar. No programming experience is assumed.

## Begin with a prediction

C is a programming language: a set of rules for writing instructions that a compiler can translate. This course uses C23, the edition published as ISO/IEC 9899:2024. The examples use a small part of that language. You can read and trace every lesson on paper before setting up tools. You do not need to memorise punctuation before beginning.

A source file is a text file containing the program. A filename ending in .c is a convention that helps tools recognise C source. Open greeting.c in a text editor, which edits plain text rather than a page layout. Opening a file to read it does not execute its instructions. Predict that this example displays the line Hello, learner. before reading how it works.

## Find the starting point

The line int main(void) begins the definition of a function named main. A function is a named piece of work. The word int says that it returns an integer, a whole number. The word void inside these parentheses says that this form of main takes no arguments. An argument is a value supplied to a function when calling it.

In a hosted program, the C environment calls main after preparing the program. Hosted means that the program runs with an operating system and a C library available. The braces { and } surround the function's body: the instructions belonging to it. The research Kernel has a different startup arrangement; do not copy this entry point into Kernel startup and expect it to boot.

## Ask the library to display a line

The line #include <stdio.h> makes declarations for standard input and output facilities available to the compiler. A declaration tells the compiler the name and type of something before it is used. It does not paste a second copy of the whole operating system into your file.

The call puts("Hello, learner.") passes a string to puts. A string represents text. The double quotes mark where that text starts and ends; they are not printed. puts writes the text followed by a newline, which moves the output to the next line. Standard output is the program's usual output stream. In a terminal you normally see it on screen; it can also be directed to a file.

## Read the check without guessing

The example checks whether puts returns EOF, the library's error marker for this operation. The symbol == compares two values. The symbol || means or, and stops once its left-hand side is true. If the first call fails, the second call in this expression is not made.

fflush(stdout) asks the library to deliver buffered output. A buffer is a temporary holding area. A successful puts may have queued text there; flushing can reveal an error while sending it onwards. stdout is the name of the standard output stream. This check does not prove that a human read the message or that a file was durably stored.

## Finish with a result

if introduces a choice. If either output operation reports an error, return 1 ends main and reports failure to the environment. Otherwise return 0 reports success. These numbers are completion results, not lines printed on screen. The semicolon ends each return statement.

The opening /* and closing */ surround a comment for people. Comments explain ownership and intent but do not execute. Keep the source's author and licence header when you copy it for study. You can change the greeting in your own working copy, rebuild it later and compare the result.

## Complete example

From the laboratory file labs/native/first-c-programs/greeting.c.

```c
/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/greeting.c
 *
 * PURPOSE:
 *   Introduce a hosted C entry point and checked text output.
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
    /* A successful call queues the greeting; flushing also checks delivery to
       the C stream. The environment decides where standard output goes. */
    if (puts("Hello, learner.") == EOF || fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
```

## Try it step by step

1. Write the line you expect the program to display, excluding the quotation marks.
2. Point to the name of the function that starts the hosted program.
3. Read the output check aloud using the word 'or' for ||.
4. Change the greeting on paper. Keep its opening and closing quotation marks.

## Check your understanding

Does opening greeting.c in an editor run main?

**Explanation:** No. The editor shows source text. A compiler and linker prepare an executable, and a separate launch starts that executable. The next lesson explains each step.

## Before you continue

You can separate source text, expected screen output and the program's completion result.

[Course contents](index.md) · [Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Next:** [Prepare, build and run without mixing the steps](02-build-and-run-one-step.md).

C edition reference: [ISO/IEC 9899:2024](https://www.iso.org/standard/82075.html).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
