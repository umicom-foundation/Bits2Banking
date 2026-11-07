# Inspecting a native model checkpoint

This laboratory demonstrates a small C program calling Umicom Framework's checkpoint validator. A checkpoint is a saved representation of model settings and learned numbers. Inspecting it lets an application display information without constructing a second decoder.

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



## Read the program in order

1. Open main.c. The configuration defines four vocabulary entries, a context of two tokens, four internal channels, eight hidden channels, two attention heads and initial seed 13. Channels are vector dimensions; heads divide attention work into groups. The seed makes initialization repeatable for this implementation.
2. Create gives the program an owned model handle. A handle is a pointer through which Framework manages the object. Destroy releases that object at the end.
3. CheckpointSize calculates the required buffer length. malloc reserves that many bytes, and the NULL check handles allocation failure.
4. CheckpointEncode writes the complete binary representation. written records how many bytes are valid.
5. CheckpointInspect validates those bytes and fills a value-only information structure. printf displays that structure only after status is OK.
6. cleanup frees the buffer and destroys the model on success or failure. No caller should read info after a rejected inspection.

## Try a damaged checkpoint

Run the executable again with --corrupt. In PowerShell use & ".\build\checkpoint-inspection.exe" --corrupt; in Bash use ./build/checkpoint-inspection --corrupt. The program flips one checksum byte and should report rejection with a nonzero exit status. This is an intentional exercise outcome. It does not edit a real model.

## Extend the experiment

Change the vocabulary from four to six, rebuild only checkpoint-inspection, and compare the weight and byte counts. Then restore four. Explain why both token embeddings and output projection depend on vocabulary size. Try setting attentionHeads to three while channels remains four; model creation should reject incompatible dimensions.

This example inspects the single-block decoder format. AdamW resume uses its separate combined checkpoint API. A checksum detects accidental byte changes; it does not identify the author or establish that a model was trained well. Keep model quality evaluation and artifact authentication as separate checks.
