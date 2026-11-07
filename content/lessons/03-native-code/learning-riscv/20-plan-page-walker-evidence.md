<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/20-plan-page-walker-evidence.md

PURPOSE:
Explain the lesson: Plan evidence for an address translator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Plan evidence for an address translator

## Prepare

Open `labs/native/sv39-address-translation/sv39.h`, `sv39.c` and `main.c` in a text editor. This lab calculates addresses in ordinary C arrays. It does not change your computer's memory mappings. Hexadecimal uses digits 0–9 and A–F; `0x1000` is 4096 in decimal.

## Understand the idea

A model can teach a useful slice of a larger system. This one covers a three-level route, 4 KiB pages and basic access checks. Its header lists omitted hardware features. A test plan should state the supported slice precisely.

## Work through the example

1. Make a table with valid first byte, valid last byte, adjacent unmapped page, misaligned frame and denied execution.
2. Add expected status and expected output preservation.
3. Add an upper-half canonical address.
4. Read `test_sv39.c` and match each row to an assertion.
5. Record that no privileged instruction is executed.

## Check your reasoning

This evidence checks the C model. It does not qualify actual MMU switching, multiprocessor translation caches or user/supervisor policy.

## If something differs

If you later integrate a real kernel walker, add separate hardware or emulator evidence rather than relabelling these hosted calculations as a boot test.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/sv39-address-translation/sv39.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](19-preserve-an-output-after-translation-fails.md)

