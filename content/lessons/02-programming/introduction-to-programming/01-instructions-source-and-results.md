<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/01-instructions-source-and-results.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Instructions, source files and results

[Course contents](index.md) · [Next: Values, variables and decisions](02-values-and-decisions.md)

## What you will make
You will run a short program and change its greeting. A program is a set of precise instructions a computer can carry out. The source file is the text a person writes. A compiler translates that text into an executable file that the operating system can start. The terminal is a window where you type commands; it is not the program being compiled.

## Set up and open the example
Follow the setup on [the course contents page](index.md). It explains installing the C tools and getting the Bits2Banking repository. You do not need Umicom Studio to complete this lab.
1. Open PowerShell from the Windows Start menu, or a terminal on Linux.
2. Find labs/native/first-c-programs/hello.c in your Bits2Banking folder. The .c ending identifies C source; it is not an executable.
3. Open it in a plain text editor. Keep its authorship header. Read main: it is the point where this example starts.
4. Locate puts. This library function writes a line of text. The quotation marks delimit the text; they are not printed.
5. Build and run using the course commands. Compare the terminal line with the exact text inside puts.

## A small complete program
Create a separate practice file named greeting.c in a folder you choose. Save as plain text, not greeting.c.txt.
~~~c
#include <stdio.h>
int main(void)
{
    if (puts("Welcome to programming.") < 0) return 1;
    return 0;
}
~~~
The include line makes the declaration of puts available. The braces group instructions. main returns an integer result to its caller: zero means this program completed successfully; one is its chosen error result. The less-than comparison checks whether output failed. You can understand the greeting first and return to error handling later.

### Compile in PowerShell
From the folder containing your practice file:
~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc -std=c23 -Wall -Wextra greeting.c -o greeting.exe
.\greeting.exe
~~~
### Compile in Bash
~~~bash
cc -std=c23 -Wall -Wextra greeting.c -o greeting
./greeting
~~~
The -o argument names the executable. The ./ or .\ prefix asks the shell to run a file in the current directory. Expect exactly one greeting line. If compilation fails, stop; an older executable does not contain your new change.

## Trace the journey
~~~text
greeting.c -> compiler -> greeting executable -> terminal output
human text                machine program       visible result
~~~
Changing the source does not automatically change an already built executable.

## Exercise and worked answer
Change the sentence to "My first Umicom learning project." Predict the new output, rebuild, and run again. The result should contain that sentence once. If the old greeting remains, check your saved file and the executable path.

## Connect to Umicom
The neighbouring first-c-programs/greeting.c adds output error checks to the same journey. Framework applications also begin with executable entry points; their libraries are additional components linked into the program. Start with this one-file journey before reading those larger programs.

## Troubleshooting
"gcc is not recognised" means the tool is unavailable in that terminal. Revisit setup and PATH. A missing quotation mark is a source error: read the compiler's filename and line number, repair the source, then compile again.

## Source map
Read `labs/native/first-c-programs/hello.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Next: Values, variables and decisions](02-values-and-decisions.md)
