<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/84-build-the-framework-ai-contract-lab.md

PURPOSE:
Explain the lesson: Build the Framework AI contract lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build the Framework AI contract lab

## Prepare

Use a terminal with a C23 compiler, CMake and Ninja. Obtain Bits2Banking and Framework source checkouts. The lab README explains PowerShell and Bash commands, the source-directory option, expected results and recovery. You do not need a trained model or an AI service account.

## Understand the idea

A source consumer compiles selected original Framework files and links its own small client to them. The learner owns the client; Framework remains the authority for token meanings and gradient measurements.

## Work through the example

1. Open `labs/native/framework-ai-contracts/README.md`.
2. Locate the Framework checkout's `include` and `src` folders.
3. Follow the configure command with that checkout as `UMICOM_FRAMEWORK_SOURCE`.
4. Build the lab, then run `btb-ai-contracts`.
5. Trace the three byte-to-token lines back to the input array in `main.c`.

## Check your reasoning

The intended bytes 65, 0 and 255 map to tokens 69, 4 and 259 and decode unchanged. The zero byte is preserved because the call uses a count, not a string terminator. This focused lab does not qualify the whole Framework SDK.

## If something differs

If configuration reports a missing Framework file, correct the source path. If compilation or a contract fails, retain the diagnostic and source revision; do not claim the expected output was observed.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-ai-contracts/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](83-write-a-gradient-measurement-lab-record.md) · [Next lesson](85-check-real-ai-client-boundaries.md)

