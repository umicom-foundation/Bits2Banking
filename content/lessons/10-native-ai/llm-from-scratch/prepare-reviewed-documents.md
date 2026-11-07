<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/prepare-reviewed-documents.md

PURPOSE:
Prepare documents for a first training dataset

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Prepare documents for a first training dataset

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


## What a dataset means

A dataset is a collection of examples. Training changes numerical model parameters so that the model predicts these examples more accurately. Our first examples are short text documents about projects and editing. They are ordinary UTF-8 text, not PDF files or scanned images.

## Read before importing

1. Open `framework/learning/native-llm/datasets/first-documents/training/project.txt` in an editor.
2. Read every sentence. These are original teaching sentences; no customer data is needed.
3. Open `training/document.txt` and `evaluation/workspace.txt` beside it.
4. Make a separate practice directory and copy this whole dataset directory into it before making experiments.
5. Record who wrote each practice document, whether you may use it and what topic it teaches.

A PDF may contain page headers, broken words and repeated footers. Extract text with a document tool, then review the result before using it. Preserve meaningful paragraph boundaries. Do not simply rename a PDF to `.txt`: that changes its name, not its contents.

## A useful preparation checklist

| Check | Why it matters |
| --- | --- |
| Readable UTF-8 text | The byte tokenizer reads bytes exactly as stored. |
| Permission to use the text | Availability does not establish training rights. |
| No passwords or personal records | A trained model may reproduce its examples. |
| Correct and relevant content | Training can reinforce errors in the examples. |
| Limited repetition | Repeated pages can dominate a tiny dataset. |

## Try and explain

Write four original sentences explaining a file-save workflow. Ask another reader to follow them. Correct ambiguity before training. A language model cannot repair missing meaning in its source documents reliably.

Expected result: a small, reviewed text collection and a note about its origin. There is no trained model yet. If a file displays unreadable symbols, reopen it using the correct encoding or extract it again; do not train on a guessed conversion.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/learning/native-llm/datasets/first-documents/README.md).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Next: Separate training and evaluation documents](partition-documents-with-a-manifest.md)
