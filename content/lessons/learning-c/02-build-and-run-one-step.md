# Prepare, build and run without mixing the steps

Understand what each tool does and stop at the stage that reports an error.

**Before you begin:** Read [Read a C program before running it](01-read-your-first-program.md), or return to it for a refresher.

## Use a reading route or a practical route

You may continue on paper if this is a shared computer, you cannot install software or you prefer to read first. The practical route needs a text editor, a C23-capable compiler, CMake and a build tool. An installation guide is different from a programming lesson: it must match your operating system and its current supported software.

The laboratory README gives exact commands for a prepared Windows UCRT64 environment and a prepared Linux environment. UCRT64 is an MSYS2 toolchain environment used by Umicom. These commands do not install it. If the prerequisites are unfamiliar, use the linked development-setup chapter with someone who can help, or remain on the reading route. Administrator rights are not needed to read or trace the examples.

## Choose a folder you can find

A working folder is the folder that a terminal currently uses to interpret relative paths. A terminal is a window that connects your keyboard and screen to a command interpreter, often called a shell. PowerShell and Bash are different shells; use the command block written for yours.

The source folder is labs/native/first-c-programs inside the Bits2Banking checkout. A checkout is a local copy of a repository's files. The separate build/first-c-programs folder holds generated files. Keeping them apart helps you see which files you wrote and which the tools produced. Do not move another project's build cache here: it can contain paths to a different checkout.

## Configure before building

CMake reads CMakeLists.txt, the project's description of source files and targets. A target is a named result the build system can prepare, such as btb-first-greeting. Configuration checks the selected tools and writes build instructions. It does not mean that every program has compiled.

In the configure command, -S names the source folder and -B names the build folder. -G Ninja asks CMake to generate instructions for Ninja, a build tool. -D introduces a CMake setting, such as the compiler's path. Read each path before running it. Use your actual checkout path if it differs from the documented example.

## Build a target, then launch it

The build command asks CMake to use the generated build system. Compilation translates each C source file into an object file. Linking combines the necessary objects and library code into an executable program. An error at either step means that the requested executable has not been freshly produced.

The greeting example is small enough to build by target name. Building it does not run it. The next command launches the resulting executable. On PowerShell, .\ at the start of a path means 'from the current folder'. On Linux, ./ has that role. Copy only the command, not the prompt shown by a terminal.

## Keep results attached to the right step

After a successful launch, the expected line is Hello, learner. The expected completion result is zero. If the terminal cannot find the program, check that configuration and building succeeded and that the executable path matches the chosen build folder. Do not type random installation commands to hide the first error.

If you edit greeting.c, the old executable remains old until rebuilt. Save the text, build the greeting target again, then launch it again. A successful build is evidence about compilation and linking. A successful test checks a specified behaviour. Neither by itself demonstrates that a whole OS or application is complete.

## Ask for help with useful evidence

Record the command, its working folder and the first relevant error. Record whether you were configuring, building or launching. A filename and line number can identify where the compiler became confused; the cause can be a missing symbol on the preceding line.

Never share personal paths, account details or unrelated terminal history unnecessarily. A small excerpt around the first error is usually easier to understand than a screenshot of hundreds of lines. Keep your source copy so you can compare before and after a correction.

## Try it step by step

1. Label four boxes Configure, Compile and link, Launch, and Check.
2. Connect CMakeLists.txt to Configure and greeting.c to Compile and link.
3. Explain why changing source text does not automatically change an already-built executable.
4. If using the practical route, follow the lab README's greeting-only sequence and record each result.

## Check your understanding

Configuration succeeds but compilation reports a missing semicolon. Should you launch an executable left from yesterday?

**Explanation:** No. Correct the source and rebuild successfully first. An older executable cannot demonstrate whether the new source works. Keep the failure evidence tied to the stage and source you actually used.

## Before you continue

You can identify the stage that failed and distinguish an expected result from an observed result.

[Course contents](index.md) · [Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Read a C program before running it](01-read-your-first-program.md).

**Next:** [Give values names and calculate a result](03-values-and-calculations.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
