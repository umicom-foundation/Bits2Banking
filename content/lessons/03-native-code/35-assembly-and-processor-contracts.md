# From C to Assembly: what a processor executes

A program written in C describes work using names, variables and functions. A processor does not read C source files. A compiler translates the source into machine instructions selected for a particular processor architecture. Assembly language lets us inspect those instructions in a form that is easier for humans to read.

Imagine adding two counts in Umicom Studio: the number of open documents and the number of saved documents. The calculation is simple, but it is a useful place to understand the journey from C to a CPU.

## 1. Understand a processor instruction

A CPU contains **registers**, which are small, fast storage locations for values that the processor is currently using. An instruction tells the processor to perform an operation such as moving a value, adding two values, comparing values or jumping to another instruction.

```text
C source:       return first + second;
                       │
                       ▼
C compiler:     generates instructions for the selected CPU
                       │
                       ▼
Assembler:      encodes instructions into object-file bytes
                       │
                       ▼
Linker:         combines compiled objects and required libraries
                       │
                       ▼
CPU:            fetches, decodes and executes machine instructions
```

An **instruction set architecture**, abbreviated **ISA**, defines which instructions, registers and execution rules software may rely on. x86-64 and RISC-V are different ISAs. A program built for x86-64 cannot be executed directly by an ordinary RISC-V processor without translation or emulation.

An **application binary interface**, or **ABI**, adds rules used when compiled functions communicate: which registers hold arguments, where a result is returned, how the stack is aligned and which registers a function must preserve. Two computers can both be x86-64 but use different calling conventions.

## 2. See the C function

The Umicom Framework learning examples include the following function in `framework/examples/learning/assembly/add.c`:

```c
#include <stdint.h>

uint32_t AddTwoC(uint32_t first, uint32_t second)
{
    return first + second;
}
```

Here `uint32_t` is an unsigned 32-bit integer. Its largest value is 4,294,967,295. Unsigned addition wraps modulo 2³² rather than producing undefined signed-overflow behaviour. That detail makes the C and Assembly results straightforward to compare, including boundary cases.

## 3. Follow the same work in x86-64 Assembly

The live Framework example is [`add_x86_64.S`](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/learning/assembly/add_x86_64.S). Its important instructions are:

```asm
#if defined(_WIN32)
    movl %ecx, %eax
    addl %edx, %eax
#else
    movl %edi, %eax
    addl %esi, %eax
#endif
    ret
```

`movl` copies a 32-bit input into `eax`. `addl` adds the other input. `ret` returns to the caller, with the result in `eax`.

On 64-bit Windows, this function receives its first two integer arguments in `ecx` and `edx`. On the x86-64 System V ABI used by Linux, it receives them in `edi` and `esi`. This is why Assembly must be written for the **processor architecture and the platform ABI**, not merely for “a 64-bit computer”.

## 4. Compare the RISC-V 64 version

Open the actual [RISC-V example](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/learning/assembly/add_riscv64.S).

```asm
AddTwoAssembly:
    addw a0, a0, a1
    ret
```

On RISC-V 64, `a0` and `a1` carry the first arguments. `addw` adds the low 32-bit words, and `a0` carries the result to the caller according to the RV64 ABI. The exact register names changed, but the function still performs the same arithmetic.

The examples belong to different target architectures. You build the version selected by CMake for your compiler; you do not put x86-64 and RISC-V instructions in the same executable.

## 5. Inspect the generated Assembly yourself

### Windows PowerShell with MSYS2 UCRT64

Create a practice directory, then inspect your compiler output without modifying Umicom Framework:

```powershell
New-Item -ItemType Directory -Force "C:\umicom\assembly-practice" | Out-Null
Set-Location "C:\umicom\assembly-practice"

@'
#include <stdint.h>
uint32_t AddTwoC(uint32_t first, uint32_t second)
{
    return first + second;
}
'@ | Set-Content -Encoding utf8 "add.c"

& "C:\msys64\ucrt64\bin\gcc.exe" -std=c23 -O0 -S "add.c" -o "add-unoptimised.s"
& "C:\msys64\ucrt64\bin\gcc.exe" -std=c23 -O2 -S "add.c" -o "add-optimised.s"

Get-Content "add-optimised.s"
```

The `-S` option asks GCC to stop after writing Assembly. `-O0` disables normal optimisation; `-O2` enables commonly used optimisation passes. Compare the two `.s` files. Both must implement the C function, but the number and ordering of instructions may differ. Exact generated text depends on your compiler version and target.

### Linux Bash

```bash
mkdir -p "$HOME/umicom/assembly-practice"
cd "$HOME/umicom/assembly-practice"
cat > add.c <<'CODE'
#include <stdint.h>
uint32_t AddTwoC(uint32_t first, uint32_t second)
{
    return first + second;
}
CODE
cc -std=c23 -O0 -S add.c -o add-unoptimised.s
cc -std=c23 -O2 -S add.c -o add-optimised.s
cat add-optimised.s
```

If your older compiler rejects `-std=c23`, use the supported equivalent `-std=c2x` for that installation and record the compiler version.

## 6. Run the real Umicom Assembly test

The Framework already contains a CMake-controlled exercise and a test that compares C and Assembly for boundary values. In your existing Umicom Applications checkout, enable the learning exercises using the active build preset and the documented assembly option when your target is supported:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-all-debug `
    -DUMICOM_BUILD_LEARNING_EXAMPLES=ON `
    -DUMICOM_LEARNING_BUILD_ASSEMBLY=ON
cmake --build --preset windows-ucrt64-all-debug --target umicom-learning-assembly --parallel 2
ctest --preset windows-ucrt64-all-debug -R "framework.learning.assembly" --output-on-failure
```

The test is an executable comparison, not a screenshot. A successful test means the implementation returned the expected results on the selected architecture. It does not prove that handwritten Assembly is faster than C.

## 7. Trace the result through an ABI

For `AddTwoAssembly(2, 3)`, the caller places `2` and `3` in the appropriate argument registers. The function adds them, places the result in the return register and returns. The C caller reads the result as a `uint32_t`.

Try values `0`, `1`, `3` and `UINT32_MAX`. Predict the wrapped result before running the tests. Explain why a 32-bit addition can give `0` after adding `1` to `UINT32_MAX`.

### Continue learning

Read [Writing safer C](36-safer-c-programming.md), then [how to build native code with CMake](../05-engineering/37-cmake-and-build-systems.md). When you are comfortable with registers and calling conventions, [follow the first Umicom Kernel boot](../06-umicom/40-boot-umicom-kernel.md), where Assembly prepares the machine before C can execute.
