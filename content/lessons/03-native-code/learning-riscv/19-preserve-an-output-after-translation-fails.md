<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/19-preserve-an-output-after-translation-fails.md

PURPOSE:
Explain the lesson: Preserve an output after translation fails.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve an output after translation fails

## Prepare

Open `labs/native/sv39-address-translation/sv39.h`, `sv39.c` and `main.c` in a text editor. This lab calculates addresses in ordinary C arrays. It does not change your computer's memory mappings. Hexadecimal uses digits 0–9 and A–F; `0x1000` is 4096 in decimal.

## Understand the idea

Output parameters are caller-owned variables used to receive a result. A refusal should not replace a useful previous value with a partial calculation. The walker assigns `*outPhysical` only after validating the complete route and permissions.

## Work through the example

1. Set an output marker to `0xdeadbeef`.
2. Request an unmapped next page.
3. Request an unsupported permission on the mapped page.
4. Find the return reached in each case.
5. Check that neither path reaches the output assignment.

## Check your reasoning

Both refused operations leave the marker unchanged. The caller must still check the return status; an unchanged marker is not a successful translated address.

## If something differs

If a caller uses the output despite failure, repair the caller's status handling rather than choosing a marker that happens to look invalid.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/sv39-address-translation/sv39.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](18-construct-a-mapping-before-publishing-it.md) · [Next lesson](20-plan-page-walker-evidence.md)

