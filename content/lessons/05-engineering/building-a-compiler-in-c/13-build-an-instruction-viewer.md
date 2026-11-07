<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/13-build-an-instruction-viewer.md

PURPOSE:
Explain the lesson: Build an instruction viewer.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build an instruction viewer

An instruction viewer makes the boundary between compilation and execution visible. It asks the existing Umicom C compiler to translate source, then displays the instructions it produced.

## Setup recap

Follow labs/native/compiler-experiments/README.md. You need the Bits2Banking and Umicom C checkouts, a C23 compiler, CMake and Ninja. The guide includes PowerShell and Bash commands and explains every build stage.

The lab reuses UmicomC::Compiler. It does not contain a second parser.

## 1. Supply one source argument

Pass this complete program as one quoted argument:

```c
int main(void) { return 2 + 3 * 4; }
```

The shell's quotes keep spaces and punctuation together. They are not part of the language source passed to the compiler.

## 2. Admit the compiled result

inspect.c supplies a fixed instruction array and a count output. It checks umc_compile before reading the array.

On failure, count is zero, but some array entries may already have been written. The success status is therefore essential; observing nonzero bytes is not permission to execute them.

## 3. Read the emitted sequence

Predict PUSH 2, PUSH 3, PUSH 4, MULTIPLY, ADD, RETURN. Draw a stack after each instruction: [2], [2,3], [2,3,4], [2,12], [14].

RETURN publishes the result. Six instructions are expected, including RETURN.

The viewer also prints each instruction's source offset. An offset is a position measured from the beginning of the source, starting at zero.

## Exercise

Change the expression to (2 + 3) * 4. Predict how the instruction order differs before running it. Then compare both listings.

Explain why displaying instructions is useful even when execution later refuses division by zero.

## Recovery

A configuration error concerns locating and building the consumer. A compiler diagnostic printed by the viewer concerns its input program. Keep those failures distinct.

The language accepts a deliberately small arithmetic subset. This viewer does not demonstrate variables, loops, arbitrary C libraries or native machine-code generation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-experiments/inspect.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](14-admit-decimal-literals-without-overflow.md)


[Previous: Project: inspect bytecode and bound execution](12-project-bytecode-and-execution-budget.md)
