<!--
Umicom Bits2Banking
File: content/lessons/04-web/nodejs-native-reporting/03-diagnose-a-refused-or-empty-result.md

PURPOSE:
Keep successful zero, a blocked or failed job, and arithmetic overflow separate in the test evidence.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom Foundation">
</picture>

# Diagnose a refused or empty result

[Course contents](index.md) · [Previous · Connect a known native producer](02-connect-a-known-native-producer.md) · [Browser edition](../../../courses/nodejs-native-reporting/lessons/03-diagnose-a-refused-or-empty-result.html)

Keep successful zero, a blocked or failed job, and arithmetic overflow separate in the test evidence.

## Write the acceptance cases

- Three rows and version 1 read as 2 posted and 1750 cents.
- An empty, valid version 1 report reads as 0 posted and 0 cents.
- An unsupported version or a row with a repeated ID is rejected before rendering.
- A refused executable, timeout or nonzero exit status produces an unavailable message. The adapter should preserve the previous verified report outside this attempt.

## Trace the overflow signal in x86-64 assembly

Assembly spells out machine instructions. The C reporter widens to 64 bits before checking a new total. This small instruction trace shows how the processor itself marks a signed 32-bit overflow for the direct addition. It is a paper exercise in NASM-style notation.

```asm
    mov edx, 42          ; simulated previously accepted result
    mov eax, 2600
    add eax, -850
    jo .out_of_range    ; branch when the signed sum cannot fit
    mov edx, eax        ; commit a result only on the success path
    jmp .finished
.out_of_range:
    ; The previously accepted value in EDX is still 42.
.finished:
```

1. Trace the first three instructions and record 1750 in EAX. The overflow branch is not taken, so EDX receives 1750.
2. Now start EAX at 2147483647 and add 1. The signed overflow flag is set. The assembly branch leaves EDX at 42. Explain why an unavailable result is different from a successful total of zero.
3. Use a disposable JSON copy and duplicate entry ID 101. Predict which Node adapter condition refuses it. The C producer checks ascending IDs before producing either output format.

In an Umicom Automated Testing exercise, record the child’s exit status, the parser decision and the screen state as separate observations. That helps a reviewer locate the failing layer even when the page displays the same short message.

- [Intel x86 architecture manuals](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [React and Native Statement Data](../../../courses/react-native-statements/index.html)
- [Native statement lab on Umicom WebServer](../../../umicom/native-statement-web-lab.md)

## Follow another path

- [Practical Web and Data Foundations](../../../courses/practical-web-and-data-foundations/index.html)
- [React and Native Statement Data](../../../courses/react-native-statements/index.html)
- [Native statement lab on Umicom WebServer](../../../umicom/native-statement-web-lab.md)
- [Applied native courses](../../../start/applied-native-courses.md)

[Course contents](index.md) · [Previous · Connect a known native producer](02-connect-a-known-native-producer.md) · [Browser edition](../../../courses/nodejs-native-reporting/lessons/03-diagnose-a-refused-or-empty-result.html)
