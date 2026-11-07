<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/preserve-outputs-on-checkpoint-errors.md

PURPOSE:
Preserve outputs when checkpoint inspection fails

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Preserve outputs when checkpoint inspection fails

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

## A result should become visible all at once

Imagine an application already displaying details for a valid checkpoint. A user selects a damaged file. If parsing overwrites the displayed summary field by field before failing, the screen could mix old and new values. Framework avoids this by building a local summary and copying it to the caller only after complete validation.

This is called failure atomicity: failure leaves the caller's previous output unchanged. It does not mean all application activity is transactional; it describes a precise contract for one API call.

## Read the implementation

1. Find the local info structure at the start of CheckpointInspect.
2. Follow assignments to info.config and info.completedSteps. These change local temporary storage.
3. Find each early return. None assigns to *outInfo.
4. Find the final *outInfo = info statement. It is the publication point.
5. In the laboratory, confirm printing occurs only after the status check.

## Read the test

The Reject helper fills an information structure with a sentinel byte pattern, copies its raw bytes into before, calls inspection, and compares the bytes afterwards. It also gives Decode an existing model pointer and checks the pointer is unchanged after rejection.

Use memcpy for the byte snapshot. Assigning one structure to another is appropriate for copying values, but a byte-for-byte padding check needs a byte snapshot. Padding is storage a compiler may place between fields for alignment; it is not application data.

## Extend the experiment

Add a normal inspection before the deliberately corrupted one. Keep the first summary in a separate variable. After rejection, print only that previously validated summary with an explicit message that the new input was rejected. Never label old metadata as belonging to the new file.

## Review question

Does preserving an output pointer free the caller's old model? No. The caller remains responsible for the old model's lifetime. A failed load must not destroy it or replace it with a half-built model.

## Read the source

[Open the example source](../../../../labs/native/llm-checkpoint-inspection/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Validate tensor shapes and finite weights](validate-weights-after-integrity.md) · [Next: Understand what a training restart needs](understand-optimizer-resume-state.md)
