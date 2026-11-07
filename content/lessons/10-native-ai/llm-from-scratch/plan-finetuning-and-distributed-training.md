<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/plan-finetuning-and-distributed-training.md

PURPOSE:
Plan fine-tuning and distributed training experiments

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Plan fine-tuning and distributed training experiments

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


## Begin with the terms

Training from scratch starts with newly initialised parameters. Fine-tuning starts with an existing model and adjusts it for a selected task. Inference uses a model to produce predictions without a training update. Retrieving documents to include in a prompt changes the input, not the model parameters.

Distributed training divides work between processes or computers. Each participant must agree on the model, data policy, numerical representation and how updates are combined. A faster computer does not automatically produce a more trustworthy update.

## Design a bounded first experiment

1. Finish a repeatable single-process training run from this module.
2. Record the model shape, dataset digest, seed and baseline loss.
3. Divide one logical batch into smaller microbatches on the same machine.
4. Study Framework's gradient accumulation contract: compatible shapes, controlled accumulation and an explicit apply step.
5. Compare the accumulated update with a reference calculation before adding a network.

A microbatch is a smaller group of examples processed as part of one intended update. Accumulating gradients can reduce peak memory, but averaging and sample weights must match the reference objective. It is not sufficient to average arbitrary finished model files.

## Before involving another machine

Define a work identifier, base model digest, data partition, expiry, result format and verification policy. Reject duplicated, stale and incompatible results. Encrypt and authenticate transport; keep sensitive documents on authorised machines. Retain failed and rejected results separately from accepted results.

The inspected dataset tool is local and read-only. It does not dispatch training to remote nodes or issue rewards. Those features need their own implementation and tests. This lesson prepares a design using working local primitives.

## A useful next project

Write a small experiment proposal comparing single-batch and accumulated gradients on the same examples. State the expected tolerance and failure cases before coding. Continue with the existing distributed-learning course after you can explain and reproduce the local update.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/ai/training/gradient_accumulation.h).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Save a model checkpoint without overwriting earlier work](save-and-reuse-a-model-checkpoint.md)
