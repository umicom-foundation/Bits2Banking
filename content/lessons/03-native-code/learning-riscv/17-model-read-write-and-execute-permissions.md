<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/17-model-read-write-and-execute-permissions.md

PURPOSE:
Explain the lesson: Model read, write and execute permissions.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Model read, write and execute permissions

## Prepare

Open `labs/native/sv39-address-translation/sv39.h`, `sv39.c` and `main.c` in a text editor. This lab calculates addresses in ordinary C arrays. It does not change your computer's memory mappings. Hexadecimal uses digits 0–9 and A–F; `0x1000` is 4096 in decimal.

## Understand the idea

Permission bits describe operations allowed on a page. Reading bytes, changing bytes and executing instructions are different requests. The model requires every requested permission to be present. It also rejects a write-only leaf when constructing a mapping.

## Work through the example

1. Map a page with `BTB_SV39_READ | BTB_SV39_WRITE`.
2. Predict a read request, a write request and an execute request.
3. Find `(entry & requestedAccess) != requestedAccess`.
4. Predict a combined read-and-execute request.
5. Find the test that requests execution on the writable example.

## Check your reasoning

Read and write are accepted; execute and read-plus-execute are refused. Testing only whether any requested bit matches would wrongly accept the combined request.

## If something differs

When access is denied, inspect the requested operation and page flags. Do not automatically add execute permission to make a test pass.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/sv39-address-translation/sv39.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](16-check-canonical-virtual-addresses.md) · [Next lesson](18-construct-a-mapping-before-publishing-it.md)

