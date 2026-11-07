<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-zig/05-build-a-mixed-language-program.md

PURPOSE:
Explain the lesson: Build a mixed-language program.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build a mixed-language program

A mixed-language program contains source written in more than one language. It still needs one compatible target and a complete set of linked implementations.

## Setup recap

Use Zig 0.15.2. Start in the Bits2Banking repository and follow the PowerShell or Bash command in labs/languages/zig-activity/README.md.

The command uses the Framework source include directory. This particular model needs a Framework status declaration, but it does not require a compiled Framework service library.

## 1. Identify the inputs

The Zig main file imports activity.zig. The command also names the existing C bridge and activity.c implementation.

The include option points the C compiler at Framework headers. The C flags select C23 for the C inputs. The libc option supplies the host C runtime used by the toolchain.

Do not assume that a header search path also links a library. Headers describe interfaces; libraries provide compiled definitions.

## 2. Identify the output

The output filename is chosen explicitly. PowerShell launches the Windows executable with the call operator. Bash launches the executable with a relative path beginning dot-slash.

These are host builds. Choosing a different output extension does not turn the executable into an iPhone application or firmware image.

## 3. Separate build and test commands

The build-exe command creates the demonstration. The test command uses activity.zig as the test root and compiles the same C sources.

If either command fails, stop and read its first diagnostic. Running an executable left from an earlier successful build can give misleading confidence about newly changed source.

## Exercise

Mark every path in the command as source input, header directory or output. Then change only the repository location on paper and rewrite the affected paths.

Explain why copying the C model into the Zig file would make later fixes harder to maintain.

## Recovery and evidence

For a missing header, inspect the include directory. For a missing symbol, inspect the linked source list. For an unfamiliar standard-library error, confirm the installed Zig version.

Record the complete command and actual result. The guide's expected output is a learning aid, not a claim that your toolchain has already passed qualification.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/zig-activity/README.md). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-handle-an-error-and-continue.md) · [Next lesson](06-check-the-interface-contract.md)

