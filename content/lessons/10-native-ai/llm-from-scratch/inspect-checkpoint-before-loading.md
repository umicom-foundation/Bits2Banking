<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/inspect-checkpoint-before-loading.md

PURPOSE:
Inspect a checkpoint before loading a model

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Inspect a checkpoint before loading a model

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

## What the operation does

A model contains many numbers called weights. Training changes these numbers. A checkpoint stores enough information to recreate a particular state. Reading a filename or header alone does not establish that the remaining numbers are valid. Framework's inspection operation checks the whole bounded checkpoint and returns a small summary.

Think of the data flow as three separate stages:

```text
checkpoint bytes → complete validation → metadata
                                      → optional decoder construction
```

The same validator is used by decoder loading. The application chooses whether to continue after inspecting the summary. Inspection itself allocates no decoder or training tape.

## Follow the calls

1. Open main.c and find CheckpointEncode. The variable written is the byte count, not a token count.
2. Find CheckpointInspect. Its first argument points to readable bytes; its second says how many bytes belong to the checkpoint; the third points to the result structure.
3. Read the status check immediately afterwards. Only the OK path prints info.
4. Run the normal example using the setup above. Compare vocabulary, context and completed steps with the configuration in main.c.
5. Add a print of info.config.attentionHeads using PRIu32. Rebuild the one laboratory target and confirm the expected value is two.

A pointer gives access to storage. It does not describe how long that storage is, so the byte count is essential. The caller must keep the buffer readable and unchanged until inspection returns. Afterwards, the returned summary contains values rather than borrowed pointers, so it remains usable after the input buffer is freed.

## Check your understanding

Why is a successful header read insufficient? A truncated tensor or nonfinite weight may occur later in the file. Why can the application show metadata without creating a decoder? The inspection loop validates serialized values directly; it does not create tensors. If an error is returned, leave the previous displayed model information in place and show the failure separately.

## Read the source

[Open the example source](../../../../labs/native/llm-checkpoint-inspection/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Next: Read model dimensions and training progress](read-model-dimensions-and-progress.md)
