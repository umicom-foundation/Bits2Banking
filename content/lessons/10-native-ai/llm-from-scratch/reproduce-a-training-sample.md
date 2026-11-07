<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/reproduce-a-training-sample.md

PURPOSE:
Reproduce a sample without crossing document boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Reproduce a sample without crossing document boundaries

This practical module starts with ordinary text files. You will learn what a dataset, token, training step and evaluation result mean by following the existing native Framework laboratory.

## Setup recap

A terminal runs commands that you type. A compiler translates C source into a program; CMake describes the build and Ninja performs the necessary steps. On Windows install Git and the MSYS2 UCRT64 C compiler, CMake and Ninja. Keep Umicom Applications at `C:\umicom\Umicom-Applications`. On Linux use your system's C23 compiler, CMake and Ninja and change into your Applications checkout.

This module uses a small standalone directory within Framework. It does not require a GPU, account or model download. Configure once in PowerShell:

~~~powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S framework/learning/native-llm -B build/learning-dataset -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/learning-dataset --target umicom-native-llm-dataset umicom-native-llm-source-train --parallel 2
~~~

In Bash use the same CMake commands from the checkout directory; omit the PowerShell Path line. Stop if a command reports an error. The lessons explain expected results rather than assuming the build has succeeded. The [CMake course](../../../courses/learning-cmake/index.html) expands each build concept.


## What the sampler controls

A sample is a short input-and-target sequence drawn from a document. Framework takes a partition, context length, sequence count, seed and batch number. A seed is an initial number used by a deterministic pseudo-random procedure. It is not a password or an assurance of secure randomness.

The inspector requests one sequence, context length eight, seed 4477 and batch zero. It supplies two separate arrays containing eight `size_t` elements each.

## Follow the sampling call

~~~c
size_t inputs[8], targets[8];
UmiStatus status = UmiAiTrainingDatasetBatch(
    dataset, UMI_AI_TRAINING_PARTITION_TRAIN,
    8U, 1U, UINT64_C(4477), UINT64_C(0),
    inputs, targets, 8U);
~~~

The final capacity is a count of elements, not bytes. `sizeof inputs` counts bytes and is not the correct argument here. `sizeof inputs / sizeof inputs[0]` computes the element count if the object is a real array in this scope.

## Run and compare

1. Run the inspector twice without changing the files.
2. Compare the document order, digest and token arrays.
3. Expect identical reports for the unchanged snapshot and implementation.
4. In a practice copy, reorder the two training entries in the manifest.
5. Inspect again and record the difference. Order is part of the dataset identity.

Framework samples eligible windows across the requested partition and never combines the end of one document with the beginning of another. This prevents an invented boundary from becoming a training example.

## Boundaries to test

The contract allows context lengths 1–32 and sequence counts 1–4. It rejects undersized or overlapping output arrays without changing them. A model can impose tighter limits than the dataset sampler. Read the decoder's shape requirements before increasing batch sizes.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/dataset_manifest.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Understand input tokens and next-byte targets](understand-byte-token-windows.md) · [Next: Record the identity of an imported dataset](identify-the-imported-dataset.md)
