<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/07-connect-source-files-at-link-time.md

PURPOSE:
Explain the lesson: Connect source files at link time.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Connect source files at link time

A program can be built from several source files. This lets a rule have one implementation while many callers use it.

## Prepare the tools

The first-c-programs README gives complete PowerShell and Bash commands. You need a C23 compiler, CMake and Ninja. Keep generated files in the separate build folder so source remains easy to inspect.

This lesson uses functions.c, counts.h and counts.c. You can follow the file relationships without executing a build.

## 1. Follow the declaration

functions.c includes counts.h. The header tells the compiler that BtbRemainingCount exists and describes its parameter and return types.

Including a declaration lets the compiler check a call's shape. It does not insert the function's implementation.

## 2. Follow the implementation

counts.c defines BtbRemainingCount. CMake builds it into btb-first-counts, a static library containing compiled code.

The executable target btb-first-functions links that library. The linker joins the caller's reference with the compiled definition.

```text
functions.c + counts.h -> caller object
counts.c    + counts.h -> library object
caller object + library -> executable
```

An object file contains compiled pieces that may still need other pieces before a complete program can run.

## 3. Read the failure stage

A spelling error in a type may fail compilation. A correctly declared function with no linked definition may fail linking. A program that builds but calculates the wrong result has a behavior problem.

The remedy depends on the stage. Rewriting the function declaration does not supply a missing library.

## Exercise

Find target_link_libraries for btb-first-functions. Explain the three names: the consuming target, PRIVATE and the dependency target.

In your notes, trace the borrowing example in the same way. It uses a different library but follows the same relationship.

## Make a controlled change

Change a valid count input in a personal copy, save and rebuild the named executable. The build tool uses dependencies to identify needed work. It does not need every unrelated project rebuilt.

If the executable appears unchanged, verify its path and that the build succeeded. An old executable can still exist after a failed build.

This structure prepares you to call Framework libraries through their documented targets rather than copying their source into each application.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/first-c-programs/CMakeLists.txt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-pass-an-array-with-its-length.md) · [Next lesson](08-observe-output-and-completion.md)

