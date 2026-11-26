<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/01-trace-a-register-write.md

PURPOSE:
Trace a write to W0

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Trace a write to W0

An Arm CPU in AArch64 mode has general-purpose registers, small storage locations used by its instructions. In this lab, `x0` names all 64 bits of register zero and `w0` names the low 32 bits of the same register. A write to `w0` clears the high half.

### Predict the result first

Write `0x12345678_ffffffff` on paper as the starting X0 value. The underscore divides the two halves. Add one to the low half and keep only 32 bits. The low half becomes zero. The instruction also clears the high half, so X0 becomes zero. With X0 initially equal to 41, the same instruction produces 42.

```text
result = (low_32_bits(argument) + 1) modulo 2^32
return result
```

### Inspect the object

```powershell
clang --target=aarch64-none-elf -c write-word.S -o write-word.o
llvm-objdump -d write-word.o
```

Look for `add w0, w0, #1` followed by `ret`. These commands inspect object bytes from any supported host with the LLVM tools. The paper trace predicts runtime behavior. The displayed instruction confirms which operation the assembler encoded.

Umicom C places its small integer results in W0. The next lesson assembles a value that needs both 16-bit halves. [Arm AAPCS64 calling convention](https://github.com/ARM-software/abi-aa/blob/main/aapcs64/aapcs64.rst)

[Course contents](index.md) · [Next lesson](02-build-an-immediate.md) · [Source · write-word.S](../../../courses/learning-aarch64-assembly/examples/write-word.S) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/01-trace-a-register-write.html)
