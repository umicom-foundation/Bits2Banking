<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/separate-checksum-cursor-and-length.md

PURPOSE:
Separate a read cursor from a checksum length

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate a read cursor from a checksum length

This module explains how a native learning program checks saved model bytes before using them. Each lesson includes its own setup summary and follows the same small Umicom Framework example.

## Set up the laboratory

A terminal accepts typed commands. A compiler translates C into machine instructions. CMake prepares the build description, and Ninja follows it. Use a C23-capable compiler, CMake 3.26 or later, Ninja, the Bits2Banking checkout and the matching Umicom Framework checkout. The example uses Framework's real training module; no downloaded model or GPU is required.

On Windows, open PowerShell and use the UCRT64 tools installed at C:\msys64\ucrt64\bin. If your tools or checkouts are elsewhere, replace those paths. Enter each line separately and stop if an error is reported.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\llm-checkpoint-inspection"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build --target checkpoint-inspection --parallel 2
& ".\build\checkpoint-inspection.exe"
```

On Linux, install your distribution's C compiler, CMake and Ninja packages, then open Bash in the laboratory folder. Replace the Framework path with your checkout.

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DUMICOM_FRAMEWORK_SOURCE=/path/to/umicom-framework
cmake --build build --target checkpoint-inspection --parallel 2
./build/checkpoint-inspection
```

Expected output includes format 1, vocabulary 4, context 2, tensors 15 and completed steps 0. A vocabulary is the set of token identifiers a model accepts; this tiny example has four. The model has just been created, so zero completed training steps is correct. The program creates bytes in memory and does not read or write a checkpoint file.

If configuration cannot find Framework, check that the chosen directory contains cmake/UmicomNativeLlmTraining.cmake. If compilation cannot find CheckpointInspect, use matching header and source revisions. Do not work around the error by adding a second parser to the lab.

[Read the complete laboratory guide](../../../../labs/native/llm-checkpoint-inspection/README.md).

## Two numbers with different jobs

A cursor records the next byte to read. A length records how many bytes an operation should examine. A parser often advances a cursor after reading a value. A checksum length should stay fixed while that checksum is calculated.

In the decoder format, the last eight bytes contain the stored checksum. The calculation covers everything before those eight bytes. It must not include its own stored result.

## Trace the calculation

```c
const size_t payloadSize = byteCount - 8U;
size_t trailerPosition = payloadSize;
const uint64_t storedChecksum = Get64(bytes, &trailerPosition);
if (Checksum(bytes, payloadSize) != storedChecksum)
    return UMI_STATUS_PARSE_ERROR;
```

Get64 is an internal helper in checkpoint.c. It reads an unsigned 64-bit value and advances trailerPosition. Checksum reads payloadSize bytes. The variables have different names because they express different responsibilities.

1. Suppose byteCount is 1,000. Write down payloadSize: 992.
2. Before Get64, trailerPosition is also 992.
3. After reading eight bytes, trailerPosition becomes 1,000.
4. The checksum length remains 992 because payloadSize never changes.
5. Inspect the active Framework implementation and locate these statements.

## Why separate statements matter

Do not combine a cursor-changing read and another use of that cursor as operands of a comparison. C does not promise left-to-right evaluation of the comparison operands. Code that expects a particular order may compute a different length on another compiler or optimization setting. Separate statements make the intended order explicit.

This is a source-level reasoning exercise. A test that passes on one compiler does not prove every evaluation order is safe. During code review, search for expressions that both advance a cursor and use its old value.

## Exercise

Draw two boxes labelled payloadSize and trailerPosition. Walk through an eight-byte trailer read and update only the cursor box. Explain which value can safely be reused to validate the final tensor position.

## Read the source

[Open the example source](../../../../labs/native/llm-checkpoint-inspection/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Read model dimensions and training progress](read-model-dimensions-and-progress.md) · [Next: Validate tensor shapes and finite weights](validate-weights-after-integrity.md)
