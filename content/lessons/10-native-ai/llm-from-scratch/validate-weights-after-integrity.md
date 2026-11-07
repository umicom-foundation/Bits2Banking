<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/validate-weights-after-integrity.md

PURPOSE:
Validate tensor shapes and finite weights

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Validate tensor shapes and finite weights

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

## Bytes can be intact and still be invalid

A checksum answers whether bytes match a stored arithmetic check. It does not establish whether those bytes describe a supported model. Someone constructing a file can compute a matching checksum for an impossible shape or an invalid numeric value.

A floating-point number can also represent infinity or NaN. NaN means Not a Number and can arise from invalid arithmetic. This checkpoint format accepts finite weights only. Finite means the value is neither infinity nor NaN.

## Walk through validation

1. Framework checks the minimum and maximum checkpoint lengths before reading fields.
2. It checks the format identifier and version.
3. It validates model dimensions and calculates the exact expected size.
4. It verifies the checksum over the payload.
5. For each tensor, it compares stored rows and columns with the shape derived from the model configuration.
6. It reads every weight and requires isfinite to succeed.
7. Only after every check succeeds does it copy metadata to the output.

No tensor dimension read from the file is used directly to request a huge allocation. The expected shape comes from validated bounded configuration.

## Inspect the regression fixture

Open test_training_checkpoint_inspect.c. Find the shape, nan and infinity cases. Each changes bytes and then calls RepairChecksum. RepairChecksum is a small test-only fixture helper; applications continue using Framework's parser.

Why repair the checksum in a rejection test? Otherwise the input would fail at the integrity check and never reach the shape or numeric check being tested. The fixture intentionally gets past the earlier check to test the later one.

## Exercise

Describe two files with identical lengths: one containing valid finite weights and one containing NaN. Explain why length equality alone cannot distinguish them. Then follow the failure path and confirm that no new decoder handle is published for either a wrong shape or a nonfinite weight.

## Read the source

[Open the example source](../../../../labs/native/llm-checkpoint-inspection/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Separate a read cursor from a checksum length](separate-checksum-cursor-and-length.md) · [Next: Preserve outputs when checkpoint inspection fails](preserve-outputs-on-checkpoint-errors.md)
