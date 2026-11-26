<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/13-check-the-byte-contract-in-host-c.md

PURPOSE:
Check the same byte-span contract in host C

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check the same byte-span contract in host C

A small host program can answer questions about the intended rules before you test Assembly on its target. The C reference uses the same counted-span conditions and distinguishes a byte sum from the refusal value.

```powershell
gcc -std=c23 -Wall -Wextra -Wconversion -Werror checked-reference.c -o checked-reference.exe
.\checked-reference.exe
```

The result should be `Five counted-byte contracts passed.` Compare each C case with the decisions in the earlier Assembly listing. For the four-byte row, the sum is 0 + 8 + 255 + 1, or 264. The refusal value is outside all valid sums.

The host program runs the independent C reference. The Assembly disassembly tells you which instructions were encoded. Keep those two observations separate when describing coverage in Umicom Studio. A later target test can run the Arm routine against the same input table.

[Course contents](index.md) · [Previous lesson](12-describe-a-frame-to-the-debugger.md) · [Source · checked-reference.c](../../../courses/learning-aarch64-assembly/examples/checked-reference.c) · [Source · sum-checked-bytes.S](../../../courses/learning-aarch64-assembly/examples/sum-checked-bytes.S) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/13-check-the-byte-contract-in-host-c.html)
