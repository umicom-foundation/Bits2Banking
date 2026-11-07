# Inspect the object code produced from Assembly

An assembler turns instruction names into machine bytes. An object file contains those bytes plus information the linker needs to join files together. This lab lets you inspect that intermediate result before running a complete program. It extends the existing C-to-Assembly addition exercise.

## Setup recap

Use an x86-64 Windows or Linux machine with GCC and GNU Binutils. On Windows, put `C:\msys64\ucrt64\bin` first on the current PowerShell PATH. On Linux, install the compiler and Binutils packages for your distribution. Check `gcc --version` and `objdump --version`. The [C and Assembly terminal lab](../../learning-c/terminal-assembly-lab.md) explains the installation and complete executable build.

Copy the existing `add_x86_64.S` from `Umicom-Applications/framework/examples/learning/assembly` into an empty practice folder. Use `Copy-Item` in PowerShell or `cp` in Bash. Read it before compiling. The capital `.S` tells GCC to preprocess the file, so its platform conditions can select the correct argument registers.

Here are the complete copy steps. Choose a new practice folder; if it already exists, use another name instead of overwriting earlier work. Adapt the checkout path if yours differs, and stop after any command error.

PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
New-Item -ItemType Directory -Path 'C:\umicom-learning\x86-object'
Copy-Item -LiteralPath 'C:\umicom\Umicom-Applications\framework\examples\learning\assembly\add_x86_64.S' -Destination 'C:\umicom-learning\x86-object'
Set-Location 'C:\umicom-learning\x86-object'
Get-Content 'add_x86_64.S'
```

Bash:

```bash
mkdir -p "$HOME/umicom-learning"
mkdir "$HOME/umicom-learning/x86-object"
cp "$HOME/umicom/Umicom-Applications/framework/examples/learning/assembly/add_x86_64.S" "$HOME/umicom-learning/x86-object/"
cd "$HOME/umicom-learning/x86-object"
cat add_x86_64.S
```

## 1. Assemble one file

Run these commands from the practice folder in either shell:

```text
gcc -c add_x86_64.S -o add_x86_64.o
objdump -t add_x86_64.o
objdump -d add_x86_64.o
```

`-c` stops before linking. The symbol table printed by `-t` should contain `AddTwoAssembly`, the function name used by C. `-d` prints decoded instructions from executable sections. Your output's addresses, spacing and object format can differ from another platform's output.

## 2. Read the instructions as a trace

On Windows x64, this example receives the two integer arguments in `ecx` and `edx`. It copies the first into `eax`, adds the second, and returns. On the common Linux x86-64 ABI, the corresponding incoming registers are `edi` and `esi`; the result still uses `eax`.

| Moment | Example value in result register |
|---|---|
| After copying the first argument, 7 | 7 |
| After adding the second argument, 5 | 12 |
| At `ret` | 12 is available to the caller |

These names describe 32-bit parts of processor registers. The function's C declaration determines how the caller interprets those bits. The ABI is the agreement between separately compiled code, including argument locations and which registers must be preserved.

## 3. Compare source and object

Find the copy, addition and return instructions in the disassembly. You may also see metadata or toolchain-specific formatting. Explain what each instruction changes. Then inspect `objdump -h add_x86_64.o`: the executable section contains code; other sections can carry metadata.

An object file is not yet a complete application. It has no C runtime startup or terminal printing. Link it with the existing C example by following the terminal lab, then compare the program's result with your register trace.

## 4. A small experiment

In a practice copy only, replace the addition instruction with subtraction. Assemble and inspect again. Predict the result for 7 and 5 before running the linked example. Restore the addition and rebuild. This exercise connects one source change to one instruction change, rather than treating Assembly as an unexplained block of text.

If the assembler rejects register names, confirm you are using an x86-64 compiler. If the linker reports a missing symbol, compare the C declaration and exported symbol exactly, including capital letters. Do not fix that problem by changing unrelated Framework APIs.

## References and route

Read the [GNU objdump manual](https://sourceware.org/binutils/docs/binutils/objdump.html) for inspection options and Microsoft's [x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170) for the Windows ABI. The real source is [`add_x86_64.S`](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/learning/assembly/add_x86_64.S). Return to [Learning x86 Assembly](index.md).

[Next: Follow arguments through an Assembly function](04-follow-arguments-through-a-function.md)
