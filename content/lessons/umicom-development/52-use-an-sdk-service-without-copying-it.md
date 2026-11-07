<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/52-use-an-sdk-service-without-copying-it.md

PURPOSE:
Explain the lesson: Use an SDK service without copying it.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use an SDK service without copying it

## Prepare

Open labs/native/framework-hash/main.c and its README. The lab links an installed Umicom Framework SDK through Umicom::base; use the documented CMake prefix for your SDK. Read base/sha256.h alongside the consumer before compiling.

## Understand the idea

The consumer includes umicom/base/sha256.h and links Umicom::base. Framework owns SHA-256 implementation. The laboratory owns its input bytes, expected results and presentation.

## Work through the example

Draw source file → public header → imported library target. Find the include, find_package and target_link_libraries statements. Explain what each supplies.

## Check your reasoning

The header describes callable interfaces; the library supplies implementation. CMake's imported target carries the installed dependency information.

## If something differs

If linking fails, inspect the SDK package and target rather than copying hashing source into the application. Keep one shared implementation.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](51-record-a-device-observation.md) · [Next lesson](53-count-input-bytes-and-output-capacity.md)

