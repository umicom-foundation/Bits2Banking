# A function called from C

[Course contents](index.md) · [Previous: Registers and instructions](01-registers-and-instructions.md)

## The agreement between caller and function

An application binary interface, or ABI, describes rules such as where arguments arrive, where a result is returned and which registers must be preserved. Knowing the instruction set is not enough to call a function correctly.

Read `AddTwoAssembly` in the real x86-64 example. It adds two unsigned 32-bit inputs and returns their low 32-bit sum. The source selects these paths:

```text
Windows x86-64:  ECX first input, EDX second input -> EAX result
System V:       EDI first input, ESI second input -> EAX result
```

For inputs 7 and 5, the selected `movl` copies the first input to EAX. `addl` adds the second. `ret` returns control to the caller. It does not itself end the whole application or print the result. This function is a leaf: it does not call another function. It needs no local stack storage.

## Why platform selection matters

Imagine using the System V register choices while a Windows caller supplied arguments in ECX and EDX. The instructions might still assemble, but they would read the wrong values. A successful assembly is therefore different from correct integration.

Find the source's checks for x86-64 and Apple targets. Unsupported targets are rejected explicitly. This example supports Windows COFF and ELF, not every executable format. Read the surrounding example instructions before building; selecting the correct toolchain is part of the exercise.

## Exercise and answer

Make a register table for both supported paths with first input 10 and second input 2. Each path should place 12 in EAX. Then write a C-side check for the function's declared interface once you have located its declaration in the example project. The check must use the exact declared types, not a guessed prototype.

For unsigned 32-bit arithmetic, a low-word result can wrap at the maximum value. That behaviour is not automatically suitable for balances or allocation sizes. A shared Framework service must choose and document overflow behaviour for its domain. Assembly optimisation should preserve that contract, not silently redefine it. Later lessons introduce caller-preserved and callee-preserved registers before using more complex functions.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/examples/learning/assembly/add_x86_64.S). Path: `Umicom-Applications/framework/examples/learning/assembly/add_x86_64.S`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://www.nasm.us/doc/nasm03.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-x86-assembly/lessons/02-a-function-called-from-c.html).

[Course contents](index.md) · [Previous: Registers and instructions](01-registers-and-instructions.md)

Sammy Hegab · Umicom Foundation · Original learning material.
