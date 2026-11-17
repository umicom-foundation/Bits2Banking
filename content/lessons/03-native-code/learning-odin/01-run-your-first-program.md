<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-odin/01-run-your-first-program.md

PURPOSE:
Teach run your first odin program.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Run your first Odin program

[Course contents](index.md) · [Next](02-connect-values-to-c.md)

## Start here
This is a first reading course in Odin. A source file is an ordinary text file containing instructions. A compiler reads it and reports errors before producing an executable. A terminal is a text interface where you enter commands; it is not the same thing as your source editor. If you have never created or saved a file, begin with the existing computer-architecture and C introductory courses.

## Prepare the tools
1. Read the [official Odin documentation](https://odin-lang.org/docs/overview/). Follow its setup instructions for your operating system. Check the compiler version in a new terminal after installation.
2. Keep C and native toolchains separate from Python environment activation. A missing compiler command is a PATH or installation issue.
3. Open the Bits2Banking repository in a terminal and create a build folder if it does not exist: New-Item -ItemType Directory -Force build.
4. Open the complete hello source linked below. Read it before running a command.

## Understand every line
package main names the executable package. import makes a library available under its package name. main is the starting procedure. The := form introduces a variable with an inferred type, while :: defines the named procedure here. fmt.printf presents text and replaces %d with an integer.

~~~text
package main
import "core:fmt"
main :: proc() {
    completed := 41
    fmt.printf("Completed: %d\n", completed)
}
~~~

## Compile, then execute
Run these PowerShell commands separately. Stop if the compiler reports an error; an old executable is not evidence that the new source compiled.

~~~powershell
odin build labs/languages/odin-activity/hello.odin -file -out:build/odin-hello.exe
& .\build\odin-hello.exe
~~~

Expected output is Completed: 41. This expectation is a prediction to check on your machine, not a claim that your compiler has been installed. On Linux choose a filename without .exe and run it using ./build/odin-hello.

## Exercise and worked answer
Change completed to 42, rebuild and rerun. Then replace the final use with a misspelled identifier. The compiler should identify an unknown name. Restore the name and rebuild. Keep this single-file lesson separate from the foreign-client build; both contain an entry point.

If nothing appears, check the executable path, process status and whether you compiled the file you edited. Save the first diagnostic before changing settings.

## Read the complete source

[labs/languages/odin-activity/hello.odin](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/odin-activity/hello.odin)
