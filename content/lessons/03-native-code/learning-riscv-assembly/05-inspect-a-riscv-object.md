# Inspect a RISC-V object before linking

A cross-compiler runs on one kind of computer and creates code for another. You can inspect RISC-V code on a Windows or Linux development computer without running that code. This lab assembles a small Framework function, reads its symbols and follows its two-instruction calculation.

## Setup recap

Install Clang and LLVM tools with RISC-V target support. Confirm `clang --version`, `llvm-objdump --version` and `llvm-readelf --version`. On Windows these may be provided by your chosen LLVM installation or MSYS2 package; use the PATH for that installation. On Linux install the corresponding packages for your distribution. See [the terminal setup guide](../../learning-c/terminal-lab.md) for folders and command basics, and the [Kernel first-boot guide](../../06-umicom/umicom-kernel-from-scratch/understand-your-first-boot.md) for the separate emulator workflow.

Copy Framework's `examples/learning/assembly/add_riscv64.S` into a new practice folder. Use `Get-Content add_riscv64.S` in PowerShell or `cat add_riscv64.S` in Bash to inspect it. No disk image or real device is involved.

Here are the complete copy steps. Choose a new practice folder; if it already exists, use another name instead of overwriting earlier work. Adapt the checkout path if yours differs, and stop after any command error.

PowerShell:

```powershell
# Use the LLVM installation already checked above.
New-Item -ItemType Directory -Path 'C:\umicom-learning\riscv-object'
Copy-Item -LiteralPath 'C:\umicom\Umicom-Applications\framework\examples\learning\assembly\add_riscv64.S' -Destination 'C:\umicom-learning\riscv-object'
Set-Location 'C:\umicom-learning\riscv-object'
Get-Content 'add_riscv64.S'
```

Bash:

```bash
mkdir -p "$HOME/umicom-learning"
mkdir "$HOME/umicom-learning/riscv-object"
cp "$HOME/umicom/Umicom-Applications/framework/examples/learning/assembly/add_riscv64.S" "$HOME/umicom-learning/riscv-object/"
cd "$HOME/umicom-learning/riscv-object"
cat add_riscv64.S
```

## 1. Produce a relocatable object

These commands work in either terminal when LLVM is on PATH:

```text
clang --target=riscv64-unknown-elf -march=rv64imac -mabi=lp64 -c add_riscv64.S -o add_riscv64.o
llvm-readelf -h add_riscv64.o
llvm-readelf -s add_riscv64.o
llvm-objdump -d add_riscv64.o
```

`--target` chooses the target machine, not the machine running the command. `-march` selects supported instruction extensions. `-mabi` selects the calling agreement. `-c` creates an object without trying to find startup code or a linker script.

The header should identify RISC-V and a relocatable ELF object. ELF is a file format used for code, data and metadata. The symbol list should contain `AddTwoAssembly`. If the tools cannot decode RISC-V, check that your LLVM installation includes that target.

## 2. Trace the calculation

The function receives two values in `a0` and `a1`. Its `addw a0, a0, a1` calculates a 32-bit sum, then sign-extends that word into the 64-bit register. The C caller's declared 32-bit result determines the observable result. `ret` returns to the address in the return-address register; a disassembler may show its underlying instruction instead of this convenient alias.

For small inputs 7 and 5, write down `a0 = 12` after addition. There is no terminal output instruction here. Returning a value and printing a value are different operations.

## 3. Connect a function to a program

Read `umicom-kernel/programs/diagnostic/entry.S`. Its entry routine calls a C main function, then invokes the Kernel exit system call. That file needs the Kernel's ABI definitions and belongs in the Kernel build; do not compile it with the two-line example command and expect a bootable system.

```text
assembly source → object + symbols → linker + other objects → executable
```

Linking must provide the entry point and resolve references between objects. Booting additionally requires a machine configuration and boot environment. This lab establishes only the object step.

## Exercise and recovery

Identify the exported symbol, executable section and instruction that returns. Explain why running `add_riscv64.o` directly in PowerShell would not work: it is a relocatable object for another target, without an application's startup contract. If `clang` reports an unsupported target, install an appropriate toolchain rather than removing the target argument and accidentally producing host code.

Read the [RISC-V ABI specification](https://riscv-non-isa.github.io/riscv-elf-psabi-doc/) beside the [real Framework example](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/learning/assembly/add_riscv64.S). Continue with the [Kernel contract lab](../../06-umicom/umicom-kernel-from-scratch/16-discover-the-native-program-contract.md), or return to [Learning RISC-V Assembly](index.md).

[Next: Explain a word-sized result on RV64](06-explain-a-word-sized-result.md)

[Previous: Trace a leaf function](04-trace-a-leaf-function.md)
