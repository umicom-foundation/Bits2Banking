# 75. How a function call crosses the C and Assembly boundary

Suppose Umicom Trader calculates a simulated order quantity by calling one small routine. The C source says which function to call, but the processor needs a precise agreement about registers, the stack and return values. That agreement is part of an **Application Binary Interface (ABI)**.

The same C23 declaration may produce different Assembly instructions on Windows x86-64, Linux x86-64 and RISC-V64.

## 1. Begin with one C declaration

```c
#include <stdint.h>

uint32_t AddCounts(uint32_t first, uint32_t second);
```

Both arguments and the result are unsigned 32-bit values. The declaration does not say where those numbers are stored while the function executes. The compiler follows the ABI selected by its target toolchain.

An ABI includes register assignments, stack alignment, the representation of types, how symbols are named, and how control returns to the caller. Different platforms can share an instruction set yet use different ABIs.

## 2. Follow the first two arguments

| Target ABI | First integer argument | Second integer argument | Integer return register |
| --- | --- | --- | --- |
| Windows x64 | `ECX` (low 32 bits of `RCX`) | `EDX` (low 32 bits of `RDX`) | `EAX` |
| x86-64 System V | `EDI` | `ESI` | `EAX` |
| RISC-V64 ELF | `a0` | `a1` | `a0` |

These are the arrangements for simple scalar arguments in the stated conventions. Floating-point arguments, structures, variadic functions and calls with many parameters have additional rules.

Open the real Framework files [x86-64 addition](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/learning/assembly/add_x86_64.S) and [RISC-V64 addition](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/learning/assembly/add_riscv64.S). They provide architecture-specific implementations of the same operation.

The x86-64 source includes separate preprocessor branches because Windows and System V pass the first two integers in different registers.

## 3. Understand what a return instruction does

On x86-64, `ret` resumes execution at the return address left by the caller. On RISC-V, `ret` is a pseudoinstruction that returns using the `ra` link register. The return value is in the register specified by the ABI.

A function that calls further functions may need to preserve a return address or callee-saved registers. Those saved values often live on the **stack**. A function with no nested calls and no local stack storage may need no stack frame at all.

The stack pointer must be suitably aligned at function-call boundaries. An incorrect hand-written Assembly prologue can corrupt memory or make C functions fail even when the arithmetic instructions look correct.

## 4. Build the existing cross-language lesson

The Framework already has an architecture-aware C/Assembly learning target. From the Umicom Applications checkout:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-all-debug `
    -DUMICOM_BUILD_LEARNING_EXAMPLES=ON `
    -DUMICOM_LEARNING_BUILD_ASSEMBLY=ON
cmake --build --preset windows-ucrt64-all-debug `
    --target umicom-learning-assembly --parallel 2
ctest --preset windows-ucrt64-all-debug `
    -R "^framework\.learning\.assembly$" --output-on-failure
```

These steps use the x86-64 Assembly implementation on a supported Windows UCRT64 target. A different compiler target may reject the option because no matching Assembly implementation exists. Do not interpret a RISC-V compiler probe failure on x86-64 as a test failure.

The supplied Framework example compares the C and Assembly results over many integer combinations, including boundary values. That is much stronger evidence than checking only `2 + 3`.

## 5. See why an object file still needs a linker

An Assembly implementation exports a symbol, for example `AddTwoAssembly`. C source can declare the function, but the linker must still find its machine-code definition.

If you omit the Assembly object from the target, you will get a missing symbol at link time. If you supply an object for the wrong CPU or object format, the linker generally refuses to combine the files. This is why **target architecture** and **binary container format** both matter.

The [new binary-header command](74-read-elf-pe-coff-with-c23.md) allows you to inspect the object and executable headers before looking more deeply with `objdump`.

## 6. Connect this to Umicom Kernel

Read [Umicom Kernel's RISC-V bootstrap](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S). The bootstrap establishes `sp`, the stack pointer, before calling `UmiKernelMain()`. It also places the hart identifier in `a0` and the device-tree address in `a1`.

Those are not arbitrary choices. The Assembly-to-C call follows the RISC-V calling convention. The compiler-generated C function expects those input registers to be meaningful.

**Exercise:** Explain why Windows x86-64 Assembly cannot simply be linked to a RISC-V kernel. Name the two RISC-V registers used for the first two arguments, and identify the code in `boot.S` that prepares them.

**Continue:** [Lesson 76 — freestanding C and the Umicom Kernel build](../06-umicom/76-freestanding-c-and-umicom-kernel.md).
