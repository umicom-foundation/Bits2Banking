<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/save-and-reuse-a-model-checkpoint.md

PURPOSE:
Save a model checkpoint without overwriting earlier work

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Save a model checkpoint without overwriting earlier work

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


## A checkpoint is saved model state

Training happens in memory. A checkpoint stores model state so it can be inspected or loaded later. Its format must carry enough information to reject incompatible or damaged data.

Choose a new output path in a practice directory:

~~~powershell
New-Item -ItemType Directory -Force "C:\umicom\practice\document-model"
& ".\build\learning-dataset\umicom-native-llm-source-train.exe" ".\framework\learning\native-llm\datasets\first-documents\dataset.txt" 16 "C:\umicom\practice\document-model\first.umi"
~~~

The source trainer calls `UmiAiTrainingDecoderCheckpointSaveNewFile`. Expect a success message only after publication succeeds. Repeating this command with the same destination should refuse replacement; choose another name for another run.

## Follow the failure path

1. Train to a new path.
2. Keep that file for comparison.
3. Attempt the same destination again.
4. Confirm the command reports failure instead of claiming it saved a new checkpoint.
5. Compare the earlier file's hash before and after with `Get-FileHash` if investigating replacement behaviour.

Creating the directory is separate from creating the checkpoint file. Missing permissions, an absent parent directory or an existing destination are ordinary errors that should be explained to the user.

## Resuming is an additional contract

A model checkpoint does not automatically include every optimiser, sampler or scheduler state needed to reproduce training continuation. Framework has separate experiment and optimiser checkpoint facilities. Study those contracts before implementing a Resume button.

The source trainer in this lesson always starts a new model. Saving its output does not make the next invocation resume it. Keep that distinction visible in an application's commands and user guide.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/ai/training/checkpoint.h).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Evaluate learning before making a quality claim](evaluate-before-making-a-claim.md) · [Next: Plan fine-tuning and distributed training experiments](plan-finetuning-and-distributed-training.md)
