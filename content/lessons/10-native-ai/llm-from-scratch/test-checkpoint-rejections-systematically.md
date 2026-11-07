<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/test-checkpoint-rejections-systematically.md

PURPOSE:
Build a checkpoint rejection checklist

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Build a checkpoint rejection checklist

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

## Test one contract at a time

A regression test is a repeatable check for behavior that must keep working. A useful parser test checks both accepted input and rejected input. It also checks that a rejection does not damage an existing result.

The new inspection test executable accepts one named scenario. CMake registers each scenario separately so a failed result identifies the boundary being exercised.

| Group | Cases | Required behavior |
| --- | --- | --- |
| Normal data | metadata, trained | Return dimensions and correct completed steps |
| Arguments | null-input, null-output | Report invalid arguments |
| Length | truncated, trailing, oversized | Reject an incomplete or oversized representation |
| Format | magic, version, configuration, tensor-count | Reject unsupported identities and dimensions |
| Payload | shape, nan, infinity, checksum | Reject invalid contents |

## Read and extend the checklist

1. Open the test file and locate Reject. It checks both inspection and decode against the same input.
2. Read truncated. It checks every shorter prefix of one valid checkpoint rather than just a single missing byte.
3. Read oversized. The size guard rejects before reading the short fixture buffer.
4. Find RepairChecksum and identify which cases need it.
5. Add a proposed test to your notes: a wrong final tensor shape with a repaired checksum. Explain what it would cover beyond changing the first tensor.

## Run only the relevant checks after an authorized build

From an already configured Framework build directory, CTest can select registered tests by name:

```text
ctest --test-dir <configured-build-directory> -R "^framework.ai.training.checkpoint_inspect\." --output-on-failure --no-tests=error
```

Replace the placeholder with an actual build directory. The executable must be built first. A missing executable is a build or environment problem, not proof that a parser assertion failed. Keep the source revision, compiler and test output together when reporting a result.

## Review question

Why keep old round-trip tests as well? The new inspector must preserve existing checkpoint loading and deterministic continuation behavior. Additional rejection coverage complements those tests.

## Read the source

[Open the example source](../../../../labs/native/llm-checkpoint-inspection/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Understand what a training restart needs](understand-optimizer-resume-state.md) · [Next: Report checkpoint evidence clearly](report-checkpoint-evidence-and-limits.md)
