<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/identify-the-imported-dataset.md

PURPOSE:
Record the identity of an imported dataset

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Record the identity of an imported dataset

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


## A name is not an identity

Two files can have the same name and different contents. A SHA-256 digest is a fixed-size value calculated from bytes. Framework's dataset digest includes the ordered documents, their partitions, relative paths, lengths and content hashes.

## Read the fingerprint

1. Run the inspector and copy the `Dataset SHA-256` line into your experiment notes.
2. Also record the Framework revision, compiler version and manifest location.
3. Change one word in a practice document.
4. Run a fresh inspection. Expect a different digest.
5. Restore the word exactly, including line endings. Inspect again.

The dataset object owns an immutable snapshot: a fixed copy imported once. Hashing that object does not reopen its source files. If the disk changes later, the existing object's digest still identifies what it actually imported. A new process imports a new snapshot.

## Understand the limits

A digest detects a change when compared with a trusted expected value. It does not prove that a document is true, licensed, safe or approved. Anyone who can replace both a document and its expected digest can replace that comparison. A signature and a trusted signing policy address a different question: who approved particular bytes.

Framework also exposes a short noncryptographic document fingerprint in metadata. It is useful for accidental-change and duplicate checks. Use the dedicated SHA-256 snapshot API when recording a cryptographic dataset identity.

## Keep a small experiment record

Write four fields: dataset digest, model configuration, random seeds and result. Add the exact command and exit code. These records help distinguish a code regression from a changed dataset. A copied success message without source identity is insufficient evidence of a reproducible run.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/learning/native-llm/SOURCE_SNAPSHOT_SHA256.md).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Reproduce a sample without crossing document boundaries](reproduce-a-training-sample.md) · [Next: Train a small decoder on the reviewed documents](train-a-small-document-decoder.md)
