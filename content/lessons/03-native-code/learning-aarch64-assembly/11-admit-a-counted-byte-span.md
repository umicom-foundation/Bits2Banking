<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/11-admit-a-counted-byte-span.md

PURPOSE:
Check a byte span before reading it

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check a byte span before reading it

A span describes a beginning and a count. The Assembly example receives a pointer in X0 and a byte count in X1. It returns the sum of up to four bytes. For an oversized span or an absent pointer with a positive count, it returns `UINT32_MAX`.

```text
if count > 4 then refuse
if count = 0 then return 0
if pointer is absent then refuse
read exactly count bytes and return their sum
```

Read the guard branches before you trace the load. `ldrb w3, [x0], #1` reads a byte and advances the pointer by one. The register used as the loop count is different from the byte value. Without the initial guard, an empty span would reach an unwanted first read.

```powershell
clang --target=aarch64-none-elf -c sum-checked-bytes.S -o sum-checked-bytes.o
llvm-objdump -d sum-checked-bytes.o
```

Identify both returns and the first possible load. The caller still owns the live byte storage and tells the truth about its available length. A numeric cap controls work under that caller contract.

[Course contents](index.md) · [Previous lesson](10-check-a-native-record-offset.md) · [Next lesson](12-describe-a-frame-to-the-debugger.md) · [Source · sum-checked-bytes.S](../../../courses/learning-aarch64-assembly/examples/sum-checked-bytes.S) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/11-admit-a-counted-byte-span.html)
