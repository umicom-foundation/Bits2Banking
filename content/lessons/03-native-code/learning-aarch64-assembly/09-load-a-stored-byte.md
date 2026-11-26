<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/09-load-a-stored-byte.md

PURPOSE:
Read one stored byte in two integer forms

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read one stored byte in two integer forms

Imagine a box in memory holding the byte `0xfe`. A pointer tells the CPU where that box is. The practice functions both load the same byte through X0. They describe the upper bits of their returned integer differently.

| Load | 32-bit result | Meaning |
| --- | --- | --- |
| `ldrb w0, [x0]` | `0x000000fe` | 254 when read as an unsigned integer |
| `ldrsb w0, [x0]` | `0xfffffffe` | −2 when read as a signed integer |

Predict the results for `0x7f` and `0x80`. The top bit matters to the signed load. Because both instructions read exactly one byte, neither consumes the next byte in the source.

```powershell
clang --target=aarch64-none-elf -c load-byte-views.S -o load-byte-views.o
llvm-objdump -d load-byte-views.o
```

Find the two named functions and compare their operand sizes. In a Framework file reader, decide whether a field is an unsigned encoded byte or a signed value before choosing its load and conversion.

[Course contents](index.md) · [Previous lesson](08-link-a-windows-arm64-caller.md) · [Next lesson](10-check-a-native-record-offset.md) · [Source · load-byte-views.S](../../../courses/learning-aarch64-assembly/examples/load-byte-views.S) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/09-load-a-stored-byte.html)
