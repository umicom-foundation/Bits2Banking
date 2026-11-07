# RISC-V sequences

Read, assemble and call six small RV64 functions. This lab supplies teaching examples for the instruction and calling-convention boundaries also used by Umicom Kernel. It does not replace Kernel implementations.

## Reading setup

Open sequences.h, then sum.S. A .S file is assembly passed through the C preprocessor. Read the header contract before interpreting the instructions. You can trace registers and memory on paper without installing software.

## Assemble objects on Windows or Linux

Install LLVM with RISC-V target support. In this directory run these commands separately in PowerShell or Bash:

```text
clang --target=riscv64-unknown-elf -march=rv64i -mabi=lp64 -c sum.S -o sum.o
clang --target=riscv64-unknown-elf -march=rv64i -mabi=lp64 -c minimum.S -o minimum.o
clang --target=riscv64-unknown-elf -march=rv64i -mabi=lp64 -c bits.S -o bits.o
clang --target=riscv64-unknown-elf -march=rv64i -mabi=lp64 -c call.S -o call.o
llvm-objdump -dr sum.o call.o
```

An object contains instructions, symbols and possibly unresolved references. It is not a bootable image or a Windows executable. The call object refers to BtbSum64, which linking must resolve.

## Run the C checks in a RISC-V Linux environment

One reproducible route uses a Linux host with a RISC-V Linux cross compiler, its static C library, and QEMU user-mode emulation installed. Use the package documentation for your distribution, then check that these command names are available.

```bash
riscv64-linux-gnu-gcc -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -march=rv64gc -mabi=lp64d -static check.c sum.S minimum.S bits.S call.S -o check-riscv
qemu-riscv64 ./check-riscv
```

C17 is sufficient for this portable harness and is accepted by older cross toolchains; the Umicom implementation direction remains C23. The Linux command compiles fresh matching objects instead of mixing the LP64 teaching objects with LP64D libraries.

Expected: RISC-V sequence checks passed and exit status zero. These commands are supplied for qualification and were not executed for this delivery.

## Diagnose setup failures

- Missing compiler: install the RISC-V Linux cross-toolchain package, not just a host compiler.
- Missing static startup or C library: install the matching cross libc development package.
- Wrong executable format: run with the matching emulator or on a RISC-V Linux host.
- Assertion failure: keep the failing line, compiler version and source revision before changing code.

The harness checks behavior, including zero lengths, unsigned wrap and shift boundaries. It does not prove preservation of every callee-saved register; inspection of call.S is a separate ABI review.

See [the RISC-V ABI specification](https://riscv-non-isa.github.io/riscv-elf-psabi-doc/) and [the instruction reference](https://docs.riscv.org/reference/isa/unpriv/rv64.html) for the machine contracts.
