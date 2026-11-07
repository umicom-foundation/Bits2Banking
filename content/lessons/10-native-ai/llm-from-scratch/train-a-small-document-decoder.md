<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/train-a-small-document-decoder.md

PURPOSE:
Train a small decoder on the reviewed documents

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Train a small decoder on the reviewed documents

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


## What changes during training

A parameter is a stored number used by the model. A training step compares predictions with targets, computes how the error changes with each parameter and adjusts parameters. A decoder predicts the next token from the available context.

Run a short experiment in PowerShell:

~~~powershell
& ".\build\learning-dataset\umicom-native-llm-source-train.exe" ".\framework\learning\native-llm\datasets\first-documents\dataset.txt" 16
~~~

In Bash replace the executable path with `./build/learning-dataset/umicom-native-llm-source-train` and use forward slashes in the manifest path.

## Follow the work

1. The tool loads the reviewed dataset and prints its file metadata.
2. It creates a small byte-level decoder with a fixed seed.
3. It evaluates held-out examples before updating parameters.
4. Sixteen training steps request samples only from the training partition.
5. It evaluates the held-out examples again with the same evaluation sampling seed.

Expect a baseline evaluation loss, training progress and a final evaluation loss. Loss is a numerical measure of prediction error; lower is better for the same evaluation task. Do not expect a particular floating-point value on every machine.

## Interpret responsibly

A successful process exit tells you that the program completed its checks. It does not prove that training improved quality. The final evaluation loss may increase even when training loss decreases. Record both numbers.

Try 32 steps in a separate run and compare. This tool creates a new model on each invocation; it does not resume the previous model. Keep the dataset unchanged for this comparison. These tiny experiments teach training mechanics, not useful conversational or programming competence.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/learning/native-llm/train_source.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Record the identity of an imported dataset](identify-the-imported-dataset.md) · [Next: Evaluate learning before making a quality claim](evaluate-before-making-a-claim.md)
