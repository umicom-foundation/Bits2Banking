<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/85-check-real-ai-client-boundaries.md

PURPOSE:
Explain the lesson: Check real AI client boundaries.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check real AI client boundaries

## Prepare

Use a terminal with a C23 compiler, CMake and Ninja. Obtain Bits2Banking and Framework source checkouts. The lab README explains PowerShell and Bash commands, the source-directory option, expected results and recovery. You do not need a trained model or an AI service account.

## Understand the idea

A useful contract test describes what remains unchanged after a failed operation as well as what is produced after a successful one. A result should not become partly valid just because the first input element was acceptable.

## Work through the example

1. Read `test_contracts.c` in the Framework AI lab.
2. Find the `reserved` case and note that its last token is invalid.
3. Predict the destination and count after rejection.
4. Find `nonfinite` and list the four report fields checked after rejection.
5. Run the named cases using the README's CTest command when your toolchain is ready.

## Check your reasoning

Rejected decoding leaves bytes 7, 8 and 9 and count 99 unchanged. Rejected gradient input leaves norm 13, scale 0.5, element count 7 and clipped flag 1 unchanged. Checking fields avoids unspecified padding bytes in C structures.

## If something differs

Keep arrays separate as the example does. These tests do not establish input/output aliasing support, convergence of a model, or behaviour on an untested platform.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-ai-contracts/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](84-build-the-framework-ai-contract-lab.md)

