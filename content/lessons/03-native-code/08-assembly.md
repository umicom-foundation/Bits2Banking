# 8. Assembly: instructions the processor can execute

You have already written expressions such as `remaining = total - completed`. In Python, PowerShell and Bash, those expressions are interpreted by software that works out how to perform them. A compiled C program takes a different route: a compiler translates the source into machine instructions for a particular processor architecture.

**Assembly language** is a readable way to write or inspect those low-level instructions. It helps you understand registers, function calls, the stack and why the same source can produce different machine code on x86-64 and RISC-V.

## Follow a subtraction

Consider this C function:

```c
int CalculateRemaining(int total, int completed)
{
    return total - completed;
}
```

The compiler must arrange for the inputs to be available, perform subtraction, and return the result. How arguments are passed is defined by a **calling convention**: a set of agreements between compiled functions. It can use registers and the stack.

A simplified RISC-V 64-bit implementation is:

```asm
CalculateRemaining:
    sub a0, a0, a1
    ret
```

Here `a0` and `a1` are registers. Under the standard RISC-V calling convention, the first two integer arguments can arrive in those registers. The `sub` instruction subtracts `a1` from `a0`, placing the result in `a0`. The `ret` instruction returns to the caller. Because `a0` also holds the integer return value, no extra move is needed in this example.

This is a small function, **not a complete program**. It relies on a caller, a valid execution environment and the calling convention.

## Look at the compiler's real output

If you have GCC installed, create a file called `remaining.c` containing the C function above. Then run:

```powershell
gcc -std=c2x -O0 -S -o remaining.s remaining.c
Get-Content .\remaining.s
```

`-S` asks the compiler to produce an Assembly listing rather than an executable. `-O0` disables most optimisation, which can make early inspection easier. The exact output depends on your compiler, processor and platform. You may see additional instructions that set up a stack frame, as well as directives intended for the assembler.

Now generate an optimised listing:

```powershell
gcc -std=c2x -O2 -S -o remaining-optimised.s remaining.c
```

Compare the two files. A compiler may remove unnecessary loads, stores and stack operations. **Shorter Assembly is not always faster**, however: modern performance also depends on memory access, branch prediction, instruction scheduling and workload.

## Registers and the stack

A processor has a finite set of registers. When a function needs to retain values across another function call or uses more temporary data than fits in registers, it may use stack memory. The exact layout is determined by the target ABI and compiler choices.

Assembly code often interacts with memory using **load** and **store** instructions. That distinction matters on RISC-V, which is a load/store architecture: arithmetic generally operates on registers, while separate instructions transfer values to or from memory.

## Inspect machine code

A typical native build goes through these stages:

![From source code to execution](../../assets/diagrams/build-pipeline.svg)

*Source* is human-readable code; *object files* contain machine code and references; a *linker* connects the required pieces; the resulting executable can then be loaded by the operating system. On Windows, GCC commonly works with `.obj` or `.o` intermediates and a `.exe` program. Linux executable file names do not require a special extension.

## RISC-V, ARM64 and x86-64

RISC-V is an open instruction-set architecture, and it is central to the first research target for **Umicom Kernel**. x86-64 and ARM64 are other instruction-set families used widely in computers and servers. Assembly instructions, register names and machine-code encodings differ across these architectures.

When studying a compiled listing, first identify the target architecture. An x86-64 command listing is not a RISC-V command listing. We will later run native Umicom Kernel research builds in a QEMU RISC-V virtual machine rather than attempting to boot them directly on a development computer.

## Check your understanding

What does a calling convention describe? Why can the same C file produce different Assembly listings? What is the relationship between `sub a0, a0, a1` and `return total - completed`?

**Next:** [Write a small native program in C](09-c.md).
