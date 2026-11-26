<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/04-trace-a-bounded-loop.md

PURPOSE:
Trace a loop with an explicit maximum

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Trace a loop with an explicit maximum

This function sums an unsigned count down to one. Its caller can supply any 32-bit value. The function allows at most 16 iterations and returns zero if the value exceeds that limit.

```text
sum = 0
if count > 16 or count = 0 then return sum
repeat
    sum = sum + count
    count = count - 1
until count = 0
return sum
```

Trace inputs 0, 3, 16 and 17. The results are 0, 6, 136 and 0. For 3, make three rows with the value of W0 before `subs`, the value of W1, and whether the next branch is taken. The final `subs` makes W0 zero and the branch falls through. The `cbz` before the loop protects the zero-iteration case.

```powershell
clang --target=aarch64-none-elf -c sum-under-limit.S -o sum-under-limit.o
llvm-objdump -d sum-under-limit.o
```

Look for the unsigned `b.hi` limit, the zero check and the backwards branch. Layout addresses can change between builds. The condition and target relationship are the important observations. Apply the same bounded-work habit when designing Framework readers and bytecode exercises.

[Course contents](index.md) · [Previous lesson](03-compare-signed-and-unsigned.md) · [Next lesson](05-preserve-a-return-address.md) · [Source · sum-under-limit.S](../../../courses/learning-aarch64-assembly/examples/sum-under-limit.S) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/04-trace-a-bounded-loop.html)
