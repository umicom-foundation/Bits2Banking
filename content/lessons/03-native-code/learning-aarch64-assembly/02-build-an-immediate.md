<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/02-build-an-immediate.md

PURPOSE:
Build a signed result in two instructions

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Build a signed result in two instructions

An immediate is a number written in an instruction. `movz` sets the selected 16-bit field and clears the remaining fields. `movk` replaces one field while keeping the others. Try rebuilding the word `0xfffeee90` on paper.

1. `movz w0, #0xee90` produces `0x0000ee90`.
2. `movk w0, #0xfffe, lsl #16` fills bits 16–31 and produces `0xfffeee90`.
3. The receiving C function treats W0 as a signed 32-bit `int`. Under two’s complement, the bit pattern represents −70000.

```powershell
clang --target=aarch64-none-elf -c return-constant.S -o constant-reference.o
llvm-objdump -d constant-reference.o
```

Some disassemblers print `mov` as an alias for the first instruction. Use the instruction bytes and destination register to recognize it. Replacing the second instruction with another `movz` loses `ee90`. Predict the new word before testing a copy.

This is the small shared ARM64 instruction sequence used by the Umicom C native constant emitter. The last two lessons compare this source with the generated ELF and COFF objects.

[Course contents](index.md) · [Previous lesson](01-trace-a-register-write.md) · [Next lesson](03-compare-signed-and-unsigned.md) · [Source · return-constant.S](../../../courses/learning-aarch64-assembly/examples/return-constant.S) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/02-build-an-immediate.html)
