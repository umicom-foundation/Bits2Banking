<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/inspect-dataset-with-native-c.md

PURPOSE:
Inspect the dataset with a native C program

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Inspect the dataset with a native C program

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


## Run the inspector

From the Applications checkout in PowerShell:

~~~powershell
& ".\build\learning-dataset\umicom-native-llm-dataset.exe" ".\framework\learning\native-llm\datasets\first-documents\dataset.txt"
~~~

In Bash:

~~~bash
./build/learning-dataset/umicom-native-llm-dataset ./framework/learning/native-llm/datasets/first-documents/dataset.txt
~~~

Expect `Documents: 3; training: 2; evaluation: 1`, byte counts, a 64-character hexadecimal SHA-256 value and two sampled windows. Byte counts may differ between line-ending conventions.

## Follow the ownership

1. `main` receives command-line arguments. `argc` counts them; `argv` holds their text.
2. `UmiAiTrainingDatasetLoadManifest` reads the manifest and creates an owned dataset snapshot.
3. `UmiAiTrainingDatasetInspect` copies summary information into a local structure.
4. `UmiAiTrainingDatasetDocument` copies one document's metadata at a time.
5. `UmiAiTrainingDatasetDestroy` releases the dataset after the report or on failure.

A status value tells the caller whether an operation succeeded. The example checks it before using an output. The inspector contains presentation code; the reusable parsing and sampling logic stays in Framework.

## Make a controlled mistake

Run the program without its manifest argument. It should print usage information and return exit code 2. In PowerShell, inspect `$LASTEXITCODE` immediately after the program. In Bash use `echo $?` immediately afterwards.

An unreadable or rejected manifest returns 1. If loading succeeds but a document is too short for an eight-token context plus a target, sampling can still fail. Add meaningful text in your practice document and inspect again. Do not treat a partially printed report as success.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/learning/native-llm/inspect_dataset.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Separate training and evaluation documents](partition-documents-with-a-manifest.md) · [Next: Understand input tokens and next-byte targets](understand-byte-token-windows.md)
