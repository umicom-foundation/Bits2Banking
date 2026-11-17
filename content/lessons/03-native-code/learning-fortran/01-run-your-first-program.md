<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-fortran/01-run-your-first-program.md

PURPOSE:
Teach run your first fortran program.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Run your first Fortran program

[Course contents](index.md) · [Next](02-connect-values-to-c.md)

## Start here
This is a first reading course in Fortran. A source file is an ordinary text file containing instructions. A compiler reads it and reports errors before producing an executable. A terminal is a text interface where you enter commands; it is not the same thing as your source editor. If you have never created or saved a file, begin with the existing computer-architecture and C introductory courses.

## Prepare the tools
1. Read the [official Fortran documentation](https://gcc.gnu.org/onlinedocs/gfortran/). Follow its setup instructions for your operating system. Check the compiler version in a new terminal after installation.
2. Keep C and native toolchains separate from Python environment activation. A missing compiler command is a PATH or installation issue.
3. Open the Bits2Banking repository in a terminal and create a build folder if it does not exist: New-Item -ItemType Directory -Force build.
4. Open the complete hello source linked below. Read it before running a command.

## Understand every line
program and end program enclose the executable statements. implicit none requires each variable to be declared, so a misspelled name becomes a compiler diagnostic instead of silently creating another variable. integer declares a whole number. The formatted print uses A for text and I0 for an integer without padding.

~~~text
program first_value
  implicit none
  integer :: completed
  completed = 41
  print '(A,I0)', 'Completed: ', completed
end program first_value
~~~

## Compile, then execute
Run these PowerShell commands separately. Stop if the compiler reports an error; an old executable is not evidence that the new source compiled.

~~~powershell
gfortran -Wall -Wextra -fcheck=all labs/languages/fortran-activity/hello.f90 -o build/fortran-hello.exe
& .\build\fortran-hello.exe
~~~

Expected output is Completed: 41. This expectation is a prediction to check on your machine, not a claim that your compiler has been installed. On Linux choose a filename without .exe and run it using ./build/fortran-hello.

## Exercise and worked answer
Change completed to 42, rebuild, then run again. Next misspell completed as completde in the assignment. With implicit none, the compiler should reject the undeclared name. Restore the spelling. A compiler error is useful feedback; do not remove implicit none to hide it.

If nothing appears, check the executable path, process status and whether you compiled the file you edited. Save the first diagnostic before changing settings.

## Read the complete source

[labs/languages/fortran-activity/hello.f90](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/fortran-activity/hello.f90)
