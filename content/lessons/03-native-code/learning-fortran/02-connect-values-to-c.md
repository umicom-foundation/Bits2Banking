<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-fortran/02-connect-values-to-c.md

PURPOSE:
Teach connect fortran values to the c contract.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Connect Fortran values to the C contract

[Course contents](index.md) · [Previous](01-run-your-first-program.md)

## Move from a value to a function call
The first lesson printed a local value. This lesson sends a value to an existing C function and checks its answer. A function is a named operation with declared inputs and an output. A foreign-function interface describes a call into code compiled from another language.

## Work in a deliberate order
1. Read [Prepare one shared C boundary](../native-language-interoperability/01-prepare-a-shared-boundary.md). Build the C archive and run its checks before adding another compiler.
2. Read [the Fortran interoperability lesson](../native-language-interoperability/06-call-c-from-fortran.md). Match every declared type and external name to bridge.h.
3. Open this course's main example, which is separate from hello. Do not compile both entry points together.
4. Write down your expected answers for inputs -1, 0, 41, 999 and 1000.
5. Build using the full command in the interoperability lesson, then compare all five results. Keep a missing compiler or linker recorded as not run.

## Read the error contract
A result of -1 means refusal; it is not a valid next count. The C model accepts 0 through 999 and produces 1 through 1000. The caller must preserve that distinction. A successful result from 41 is 42, but that does not prove the boundary inputs work.

## Ownership without hidden allocations
Only integer values cross this boundary. No address is retained and no managed-language object is passed to C. This small design makes it possible to study linkage independently of allocation and garbage collection. Later text or image APIs require separate lifetime and capacity rules.

## Exercise and worked answer
Explain why adding one directly in the Fortran client is not equivalent. Answer: it duplicates the rule and can skip its rejection cases. Explain why passing an integer with the wrong width is dangerous even if 41 appears to work. Answer: the caller and callee may read different register or stack bytes, and larger or negative values expose the mismatch. Keep the implementation in C and correct the interface declaration instead.

## Read the complete source

[labs/languages/fortran-activity/main.f90](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/fortran-activity/main.f90)
