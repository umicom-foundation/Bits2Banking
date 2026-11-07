<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/evaluate-before-making-a-claim.md

PURPOSE:
Evaluate learning before making a quality claim

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Evaluate learning before making a quality claim

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


## Ask one measurable question

A quality check needs a task. For this module the question is: does the trained decoder assign better predictions to held-out byte sequences? That is narrower than asking whether it understands programming.

## Build a comparison table

| Run | Training steps | Dataset identity | Baseline evaluation loss | Final evaluation loss |
| --- | --- | --- | --- | --- |
| A | 16 | Record the digest | Record output | Record output |
| B | 32 | Same digest | Record output | Record output |

1. Keep the input files and model configuration fixed.
2. Run each experiment and record its exit status.
3. Compare final evaluation losses, not only the last training batch.
4. Explain any changed compiler, seed or source revision.
5. Repeat with independently selected held-out material before making broader claims.

The last training loss covers one sampled batch. Evaluation averages several held-out batches in the example. These numbers describe different inputs and should not be treated as interchangeable.

## Avoid tuning against the answer sheet

Repeatedly choosing every setting based on one evaluation set can adapt development decisions to that set. Larger projects separate training, validation for development decisions and a final test set kept for the final assessment. This introductory loader has two named partitions; a third-stage evaluation policy needs an explicit additional workflow.

## Recovery

If loss becomes non-finite, such as infinity or NaN, stop and retain the exact configuration and diagnostics. Do not remove the failure check to obtain a success message. Inspect numerical ranges, learning rate and data before changing the experiment.

Framework's quality-gate services can compare evidence against explicit rules. A rule cannot establish an ability that the measurement never tested.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/learning/native-llm/MODEL_QUALITY_GATE.md).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Train a small decoder on the reviewed documents](train-a-small-document-decoder.md) · [Next: Save a model checkpoint without overwriting earlier work](save-and-reuse-a-model-checkpoint.md)
