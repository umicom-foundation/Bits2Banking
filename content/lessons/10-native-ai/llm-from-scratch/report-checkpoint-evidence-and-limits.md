<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/report-checkpoint-evidence-and-limits.md

PURPOSE:
Report checkpoint evidence clearly

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Report checkpoint evidence clearly

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

## Separate observations from claims

A useful report tells another learner what was inspected, which checks ran and what remains unknown. A valid checkpoint is a structurally accepted artifact. It is not automatically a useful language model, an authentic release or a reproducible training run.

## Create a short experiment record

1. Record the Framework source revision used to build the laboratory.
2. Record the compiler and operating system.
3. Copy the normal program's printed metadata into the record.
4. Run --corrupt and record the nonzero exit status and rejection message separately.
5. Record any tests you ran by name, with pass, failure or skipped outcomes. Leave unexecuted checks marked unexecuted.
6. State that this laboratory uses a newly initialized tiny model and performs no training unless you explicitly added a training step.

```text
Artifact: in-memory single-block decoder checkpoint
Format: 1
Training progress: 0 completed steps
Structural inspection: record the actual outcome
Authentication: not performed by this laboratory
Quality evaluation: not performed by this laboratory
```

## Connect to a larger application

A model browser can call the Framework inspector and display vocabulary, context and progress. A training application can use the combined optimizer checkpoint for restart. A release workflow can bind artifact hashes to reviewed provenance. A quality evaluation can measure held-out loss or task performance. Each has its own purpose and should report its own outcome.

For a file selected by a user, first apply the application's path and trust policy and read within the documented size limit. Do not treat a checksum as permission to accept files from any source. This lab deliberately avoids file selection so you can study the codec without mixing storage policy into it.

## Exercise

Write two sentences: one that accurately describes this lab and one that overstates it. Correct the overstatement. For example, replace a claim of a trained assistant with a statement that the program inspected a newly initialized bounded decoder. Clear evidence makes later debugging and learning much easier.

## Read the source

[Open the example source](../../../../labs/native/llm-checkpoint-inspection/main.c).

## Continue learning

<!-- Earlier end-of-module navigation retained for review:
[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Build a checkpoint rejection checklist](test-checkpoint-rejections-systematically.md)
-->
[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Build a checkpoint rejection checklist](test-checkpoint-rejections-systematically.md) · [Next: Separate retrieval from model training](retrieval-and-model-training.md)
