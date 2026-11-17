<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-nim/01-run-your-first-program.md

PURPOSE:
Teach run your first nim program.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Run your first Nim program

[Course contents](index.md) · [Next](02-connect-values-to-c.md)

## Start here
This is a first reading course in Nim. A source file is an ordinary text file containing instructions. A compiler reads it and reports errors before producing an executable. A terminal is a text interface where you enter commands; it is not the same thing as your source editor. If you have never created or saved a file, begin with the existing computer-architecture and C introductory courses.

## Prepare the tools
1. Read the [official Nim documentation](https://nim-lang.org/docs/tut1.html). Follow its setup instructions for your operating system. Check the compiler version in a new terminal after installation.
2. Keep C and native toolchains separate from Python environment activation. A missing compiler command is a PATH or installation issue.
3. Open the Bits2Banking repository in a terminal and create a build folder if it does not exist: New-Item -ItemType Directory -Force build.
4. Open the complete hello source linked below. Read it before running a command.

## Understand every line
let introduces a value that will not be reassigned. echo writes a line of text. Nim uses indentation to group statements when you add loops or decisions. The c command selects the C backend: Nim generates C, then the configured C compiler builds the executable.

~~~text
let completed = 41
echo "Completed: ", completed
~~~

## Compile, then execute
Run these PowerShell commands separately. Stop if the compiler reports an error; an old executable is not evidence that the new source compiled.

~~~powershell
nim c --cc:gcc --nimcache:build/nim-hello-cache --out:build/nim-hello.exe labs/languages/nim-activity/hello.nim
& .\build\nim-hello.exe
~~~

Expected output is Completed: 41. This expectation is a prediction to check on your machine, not a claim that your compiler has been installed. On Linux choose a filename without .exe and run it using ./build/nim-hello.

## Exercise and worked answer
Change 41 to 42 in the source, rebuild and rerun. Then try adding completed = 43 on another line. The compiler should reject reassignment to a let value. Remove that experimental line or deliberately use var when the lesson needs a mutable variable.

If nothing appears, check the executable path, process status and whether you compiled the file you edited. Save the first diagnostic before changing settings.

## Read the complete source

[labs/languages/nim-activity/hello.nim](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/nim-activity/hello.nim)
