# Lab: build C and Assembly together

A processor executes machine instructions. Assembly gives readable names to those instructions. C and Assembly can cooperate when they agree how arguments and results move between functions. That agreement is a calling convention, part of an application binary interface (ABI).

## Setup recap

This lab uses the existing Umicom x86-64 addition example. It requires an x86-64 Windows or Linux computer and GCC. You do not need an IDE. Install GCC, CMake, Ninja and GDB using [the terminal setup lab](terminal-lab.md), confirm `gcc --version`, and obtain a local Bits2Banking checkout or downloaded source archive. Choose your own practice folder.

## 1. Create working files from the real example

These commands assume the checkout is `C:\umicom\Umicom-Bits2Banking` on Windows or `$HOME/umicom/Umicom-Bits2Banking` on Linux. Change that source path if yours differs. Use a new practice folder; do not overwrite work there.

PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
New-Item -ItemType Directory -Path 'C:\umicom-learning\assembly-call'
Set-Location 'C:\umicom-learning\assembly-call'
Get-Content 'C:\umicom\Umicom-Bits2Banking\labs\native\assembly-functions\main.c' -Raw | Set-Content -Encoding ascii main.c
Get-Content 'C:\umicom\Umicom-Bits2Banking\labs\native\assembly-functions\add_x86_64.S' -Raw | Set-Content -Encoding ascii add_x86_64.S
Get-Content add_x86_64.S
```

Bash:

```bash
mkdir -p "$HOME/umicom-learning/assembly-call"
cd "$HOME/umicom-learning/assembly-call"
cp "$HOME/umicom/Umicom-Bits2Banking/labs/native/assembly-functions/main.c" .
cp "$HOME/umicom/Umicom-Bits2Banking/labs/native/assembly-functions/add_x86_64.S" .
cat add_x86_64.S
```

You have created a `.c` source and a `.S` source in your own folder. The uppercase `.S` tells GCC to run its preprocessor before assembling, allowing the file to select the host's calling convention.

## 2. Trace one call

The C declaration is `extern uint32_t AddTwoAssembly(uint32_t left, uint32_t right);`. A declaration describes a function without providing its body. `uint32_t` is an unsigned 32-bit integer type. The body resides in the Assembly file.

On Windows x64, this function receives the first two integer arguments in the `ECX` and `EDX` registers. On Linux x86-64 using the System V ABI, they arrive in `EDI` and `ESI`. Registers are small named storage locations in the processor. Both variants place the result in `EAX`.

```text
C caller with (27, 15)
  -> argument registers
  -> movl: copy first argument to EAX
  -> addl: add second argument to EAX
  -> ret: return to the caller
  -> C receives 42
```

GNU Assembly notation here writes source before destination: `movl %ecx, %eax` copies ECX into EAX. `addl %edx, %eax` adds EDX to EAX. The `l` suffix selects a 32-bit operation. `.globl AddTwoAssembly` makes the symbol available for linking. `ret` returns using the return address established by the call.

## 3. Compile, assemble and link

PowerShell:

```powershell
gcc -std=c23 -Wall -Wextra -g main.c add_x86_64.S -o assembly-call.exe
.\assembly-call.exe
$LASTEXITCODE
```

Bash:

```bash
gcc -std=c23 -Wall -Wextra -g main.c add_x86_64.S -o assembly-call
./assembly-call
echo $?
```

Stop if compilation fails. Expected output includes `Payment IDs 27 and 15 combine to 42.` and `C and Assembly agree on 100 value pairs.` These are arithmetic labels in a teaching program, not a payment operation. The C program compares ten possible left values with ten right values, including unsigned wraparound boundaries.

## 4. Investigate linking

In a separate output attempt, omit `add_x86_64.S` from the compiler command. The linker should report an unresolved `AddTwoAssembly` reference. The declaration told the C compiler how a call looks; it did not provide the implementation. Add the Assembly source back and rebuild.

## Exercise and answer

For inputs 7 and 25, the result is 32. Trace the two register operations before running. For the largest unsigned 32-bit value plus one, the low 32 bits are zero; the existing test checks this wraparound deliberately. Do not generalise that result to signed C overflow, which has different rules.

Read [the complete example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/assembly-functions/README.md) for CMake registration and the separate RISC-V implementation. A host x86-64 run validates this host path only.

[Course contents](index.md) · [Next: use an IDE](terminal-to-visual-studio.md)
