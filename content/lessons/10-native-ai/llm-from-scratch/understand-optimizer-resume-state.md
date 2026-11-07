<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/understand-optimizer-resume-state.md

PURPOSE:
Understand what a training restart needs

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand what a training restart needs

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

## Weights are only part of a training run

A decoder checkpoint stores model configuration, weights and its completed-step count. An optimizer decides how those weights are updated. AdamW keeps additional numbers called moments, which summarize earlier gradients. Restarting with the same weights but freshly reset moments changes the subsequent update sequence.

A gradient describes how a small change in a weight would affect the loss. Loss is a numeric measure of prediction error. The optimizer uses gradients and its own state to choose an update.

## Follow Framework's existing layers

1. Open checkpoint.h. It defines the single-decoder checkpoint used by this laboratory.
2. Open optimizer_checkpoint.h. Its combined format contains a decoder checkpoint and AdamW state.
3. Read the decode contract: both owned handles are published only on complete success.
4. Read the lifetime rule: destroy the optimizer before the decoder it is bound to.
5. Open training_run_lock.h and training_source_lock.h to see how experiment and source identities can accompany a resumed run.

```text
decoder state + optimizer state + training plan
              + dataset identity + next data position
              → a reproducible continuation experiment
```

## Plan a restart experiment

Write a table with two runs. Run A performs two training steps without interruption. Run B performs one step, saves a combined checkpoint, reloads it and performs the same second step. Keep the input batch, learning-rate schedule and numeric environment consistent. Compare full state, not just a friendly console message.

The existing tests contain continuation examples. Read them before designing a new one. Do not infer successful exact restart from the metadata inspection lab; this lab does not restore optimizer moments.

## Check your understanding

Can equal completed-step counts establish equal models? No. Can a decoder checkpoint prove which documents were used? No. These facts need separate evidence. Recording explicit identities makes experiment reports useful when investigating different outcomes.

## Read the source

[Open the example source](../../../../labs/native/llm-checkpoint-inspection/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Preserve outputs when checkpoint inspection fails](preserve-outputs-on-checkpoint-errors.md) · [Next: Build a checkpoint rejection checklist](test-checkpoint-rejections-systematically.md)
