![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Learning x86 Assembly

Trace registers and a small x86-64 function before attempting platform-specific programs.

Read Introduction to Computers and C integer/function lessons. Begin with paper traces before assembling any code.

[Browser course](../../../courses/learning-x86-assembly/index.html) · [Choose a subject](../../../start/course-series.md)

## Reading order

1. [Registers and instructions](01-registers-and-instructions.md)
2. [A function called from C](02-a-function-called-from-c.md)

## Course outline: later topics

Memory addressing, branches, stack frames, debugging and C calling conventions.

Read one topic at a time. The list above links to available lessons; the outline describes further study. Each practical lesson gives its own tool requirements.

## Practical labs: read, change and check

Follow these after the introductory lessons. Each lab includes its own setup recap and explains the expected result.

- [Inspect the object code produced from Assembly](03-inspect-object-code.md)

## Continue with a practical source study

A C function call and an Assembly function must agree on where arguments and results live. You will trace two small integers through the existing AddTwoAssembly example and learn how to separate a CPU instruction from the calling convention used by an operating system.

- [Follow arguments through an Assembly function](04-follow-arguments-through-a-function.md)


## NASM data and linkage

Create a small practice record, inspect its byte layout, then follow a reference the assembler leaves for the linker. These five lessons cover NASM’s data pseudo-instructions, two position expressions and the directives used to describe the example sections and symbols. You can follow the byte traces with pencil and paper.

1. [Write initialized data in NASM](05-write-initialized-data.md)
2. [Reserve storage in NASM](06-reserve-storage.md)
3. [Count and repeat bytes in NASM](07-count-and-repeat-bytes.md)
4. [Include a known byte fixture in NASM](08-include-a-known-byte-fixture.md)
5. [Name sections and link symbols in NASM](09-name-sections-and-link-symbols.md)
