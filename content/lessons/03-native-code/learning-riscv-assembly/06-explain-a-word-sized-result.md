<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/06-explain-a-word-sized-result.md

PURPOSE:
  Present "Explain a word-sized result on RV64" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Explain a word-sized result on RV64

The RV64 example uses addw even though its registers can hold 64 bits. This lesson explains that choice by following a small result from a C-compatible function through the Assembly instruction and back to its caller.

Source to open: `Umicom-Applications/framework/examples/learning/assembly/add_riscv64.S`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\Umicom-Applications\framework\examples\learning\assembly\add_riscv64.S'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../Umicom-Applications/framework/examples/learning/assembly/add_riscv64.S'
```

## Understand the idea

A bit is one binary digit. Thirty-two bits form the word-sized result used by addw; RV64 integer registers contain 64 bits. The instruction adds the low 32 bits and extends bit 31 into the upper 32 bits. Read add.h: the function accepts and returns uint32_t, so its C-visible result is unsigned. Register sign extension does not change that declared type. The RV64 calling convention carries even unsigned 32-bit values in sign-extended form. The C caller interprets the low 32 bits according to the declaration; the full register is not a new unsigned 64-bit API.

```text
C-visible uint32_t       Low 32 bits      Full RV64 register
12                       0000000C         000000000000000C
4294967294               FFFFFFFE         FFFFFFFFFFFFFFFE

addw a0, a0, a1
ret
```

## Work through the lab

1. Open AddTwoAssembly. Find the architecture check, the addw instruction and ret. Explain each line in one sentence: reject an unsuitable build target, calculate a word result, return to the caller.
2. Trace a0 = 7 and a1 = 5. The low 32-bit result is 12. Its sign bit is zero, so the upper bits of the result are zero too.
3. Trace inputs 4294967294 and 0. The uint32_t result remains 4294967294. Its low 32 bits are FFFFFFFE, and the full register representation after addw is FFFFFFFFFFFFFFFE. The C return type still means unsigned 32-bit, not signed negative two.
4. Write a comparison table for (0,0), (7,5), (4294967294,0) and (4294967295,1). Record expected uint32_t results before running anything. The last case wraps to zero in the C reference. Record the build target with any eventual emulator observation.

## Expected result

The four C-visible results are 0, 12, 4294967294 and 0. You should distinguish the unsigned result type from the wider register representation. This reading exercise does not require a RISC-V computer or establish that a kernel image boots.

## If the result differs

If a debugger shows a negative full-register value, check the declared return type and the low 32 bits before diagnosing wrong arithmetic. Never replace uint32_t with a 64-bit type merely to match a debugger display: the interface and instruction would need a deliberate review together.

## Explain it yourself

Does a full-register display of FFFFFFFFFFFFFFFE mean that this uint32_t function has returned a signed negative value?

<details>
<summary>Worked explanation</summary>

No. The register contains a sign-extended representation of the 32-bit result. The declared uint32_t result is the low 32-bit value 4294967294. A debugger display format does not change the function's C type.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-riscv-assembly/lessons/06-explain-a-word-sized-result.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](05-inspect-a-riscv-object.md) · [Course contents](index.md)

## Technical references

[RISC-V instruction-set manual: RV64 word operations](https://docs.riscv.org/reference/isa/_attachments/riscv-unprivileged.pdf)

[RISC-V procedure calling convention](https://riscv-non-isa.github.io/riscv-elf-psabi-doc/)


[Next: Exchange the stack pointer with a control register](07-exchange-the-stack-pointer-with-a-csr.md)
