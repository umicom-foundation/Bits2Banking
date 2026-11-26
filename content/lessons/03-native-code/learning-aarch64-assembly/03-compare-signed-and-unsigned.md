<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/03-compare-signed-and-unsigned.md

PURPOSE:
Compare the same bits as signed and unsigned

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Compare the same bits as signed and unsigned

`cmp w0, w1` updates flags for a subtraction. A later instruction chooses how to interpret those flags. `cset` writes one when its condition holds and zero otherwise.

| W0 | W1 | Signed less, LT | Unsigned lower, LO |
| --- | --- | --- | --- |
| 0xffffffff | 1 | 1 | 0 |
| 5 | 5 | 0 | 0 |
| 1 | 5 | 1 | 1 |

The first word means −1 as a signed 32-bit integer. As an unsigned integer it means 4294967295. Check each row in both interpretations before assembling the source.

```powershell
clang --target=aarch64-none-elf -c compare-words.S -o compare-words.o
llvm-objdump -d compare-words.o
```

Look for both named functions. The disassembler may display `cc` for the unsigned `lo` condition. Both names select the same carry-clear encoding. Keep an explicit choice of signedness when moving C comparisons into Assembly. In the next lesson, the loop guard treats every input as an unsigned count.

[Course contents](index.md) · [Previous lesson](02-build-an-immediate.md) · [Next lesson](04-trace-a-bounded-loop.md) · [Source · compare-words.S](../../../courses/learning-aarch64-assembly/examples/compare-words.S) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/03-compare-signed-and-unsigned.html)
