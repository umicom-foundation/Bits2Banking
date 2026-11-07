<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/read-model-dimensions-and-progress.md

PURPOSE:
Read model dimensions and training progress

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read model dimensions and training progress

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

## Understand the summary

A dimension describes how many values fit along one axis of a tensor. A tensor is an array whose shape gives meaning to its elements. A vocabulary-by-channels embedding has one vector for each token. A context length limits how many token positions one sequence contains.

| Field | Meaning in this laboratory |
| --- | --- |
| vocabularySize | Number of accepted token identifiers |
| contextLength | Number of token positions in one training sequence |
| channels | Width of an internal representation |
| hiddenChannels | Width of the feed-forward hidden layer |
| attentionHeads | Number of attention groups |
| initialSeed | Initialization input for repeatable experiments |
| completedSteps | Number of completed optimizer updates recorded by the decoder |
| tensorCount | Number of separately stored parameter arrays |
| weightCount | Total scalar parameter values across those arrays |

## Compare two configurations

1. Record the output of the unchanged program.
2. Change vocabularySize from four to six in the first configuration initializer.
3. Rebuild checkpoint-inspection and run again. The tensor count stays the same, while the number of weights changes.
4. Restore the original configuration. Change only initialSeed from 13 to 14 and repeat.
5. Explain why the shapes remain the same although initialized weight values can differ.

The seed is a choice of starting state; it is not a model identifier. Two runs with the same seed can later train on different data. Likewise, completedSteps does not prove what data was processed or how useful the model is.

## Follow the real source

Open decoder_private.h and locate UmiAiDecoderParameterId. Follow UmiAiDecoderParameterShape in decoder.c to see the shape calculation for each parameter. This connects the public count to actual Framework storage instead of assuming every model uses the same architecture.

## Review question

A checkpoint reports 100 completed steps. Can you infer it saw 100 documents? No. A step is one parameter update; the amount of data per step depends on the training plan and batching. Record the plan and dataset identity separately.

## Read the source

[Open the example source](../../../../labs/native/llm-checkpoint-inspection/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Inspect a checkpoint before loading a model](inspect-checkpoint-before-loading.md) · [Next: Separate a read cursor from a checksum length](separate-checksum-cursor-and-length.md)
