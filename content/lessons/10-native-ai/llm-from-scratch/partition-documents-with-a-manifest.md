<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/partition-documents-with-a-manifest.md

PURPOSE:
Separate training and evaluation documents

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate training and evaluation documents

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


## Two different jobs

Training data is used to change the model. Evaluation data measures predictions without changing it. If a model sees the evaluation answers during training, the measurement becomes less informative. This is called data leakage.

The Framework laboratory assigns whole files to one group. Its manifest is a short text file listing those decisions:

~~~text
UMICOM-AI-DATASET-1
train training/project.txt
train training/document.txt
eval evaluation/workspace.txt
~~~

## Follow each line

1. The header identifies the manifest format.
2. `train` selects a training document.
3. `eval` selects an evaluation document.
4. Paths begin at the directory containing the manifest. Forward slashes work in this format on Windows too.
5. Both groups need at least one document.

The loader rejects duplicate paths and matching content fingerprints with matching lengths. This helps catch obvious duplicates; it does not identify every paraphrase or related document. Put versions of the same document in the same group during your own preparation.

## Experiment in the practice copy

Copy the contents of a training document into the evaluation file. Run the inspector from the next lesson against this practice manifest. Expect a rejection. Restore the evaluation text and inspect again.

The manifest accepts a restricted path alphabet and rejects `..` components. These checks do not make it a security sandbox: filesystem links can still refer elsewhere. Open manifests that you have reviewed in a directory you control.

## Check your understanding

Explain why a random split of adjacent sentences from one repeated manual can still leak information. A better split keeps related documents together and uses genuinely separate material to assess the intended task. For this tiny example the purpose is to learn the mechanics, not to estimate production model quality.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/ai/training/dataset_manifest.h).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Prepare documents for a first training dataset](prepare-reviewed-documents.md) · [Next: Inspect the dataset with a native C program](inspect-dataset-with-native-c.md)
