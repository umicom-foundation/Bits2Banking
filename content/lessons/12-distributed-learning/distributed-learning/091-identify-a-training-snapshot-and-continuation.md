<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/distributed-learning/091-identify-a-training-snapshot-and-continuation.md

PURPOSE:
Identify source data and continuation settings

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Identify source data and continuation settings

Training adjusts numbers called model parameters so that predictions better match examples. A batch is a group of examples used for one adjustment. This module follows a small, local Framework experiment. It assumes no previous machine-learning course and introduces each term before using it. A local experiment is the first measurement needed when designing work for several computers.

## Set up this laboratory

1. Install a C23 compiler, CMake and Ninja. On Windows, open PowerShell and make the installed UCRT64 tools available with `$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path`. On Linux, open a terminal and ensure `cc`, `cmake` and `ninja` are installed through your distribution.
2. Use a checkout of Umicom Framework containing `learning/native-llm/inspect_accumulation.c`. The examples below use the Framework child of Umicom Applications.
3. Configure a separate laboratory directory. This prepares build instructions; it does not train a model.

```powershell
Set-Location C:\umicom\Umicom-Applications\framework
cmake -S learning/native-llm -B build/learning-accumulation -G Ninja -DBUILD_TESTING=ON
cmake --build build/learning-accumulation --target umicom-native-llm-accumulation
& .\build\learning-accumulation\umicom-native-llm-accumulation.exe 2
```

In Bash, change to the Framework directory, run the same two `cmake` commands, then run `./build/learning-accumulation/umicom-native-llm-accumulation 2`. Stop if configuration or compilation fails; inspect the first diagnostic before proceeding. Expected successful output includes `Effective tokens: 40` and `Comparison: within tolerance`. Numerical values and memory observations must be recorded from your actual run. These are instructions to execute, not a claim that a particular environment has passed.

## A filename is not a training identity

A file named `model.bin` can contain different bytes tomorrow. A path tells a program where to look; a content digest identifies a particular byte sequence. SHA-256 produces a fixed-size digest used to detect changes to reviewed bytes. An unsigned digest does not establish who supplied those bytes.

A continuation resumes training from an earlier state. To interpret it, retain the model parameters, optimiser state where applicable, source-data identity and relevant training settings. A seed alone is insufficient when data ordering or optimiser state changes.

## Inspect the Framework records

The source-lock API binds checkpoint bytes to the dataset loader's imported source-snapshot identity. The run lock covers training settings. Gradient-clipping policy has its own companion record. The source-lock header explicitly requires checking the relevant records together for strict continuation.

1. Read the `Format` and `Verify` signatures. Both receive bytes already supplied by the caller and a loaded dataset.
2. Notice that formatting a source lock does not decode the checkpoint. The checkpoint codec has that responsibility.
3. Read `SaveNewFile`: an occupied destination is refused.
4. Note that publishing several companion files is not one atomic filesystem action.

## Design a review folder

Keep an immutable source manifest, exact input snapshot, checkpoint, applicable policy records and run report together. Record the source revision and build environment. Store private documents in a location chosen by their owner and retain permission to use them. Do not publish personal training material merely because a hash has been computed.

## Exercise

Consider two checkpoints with equal filenames and different bytes. A source-lock verification must distinguish them. Next consider unchanged checkpoint bytes with an altered training document. The dataset identity must distinguish that case too. Finally consider identical bytes signed by an unknown party: byte equality still does not supply trust in the publisher.

These distinctions are necessary before distributing tasks. Every worker assignment needs an unambiguous base snapshot and authorised data scope.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/ai/training/training_source_lock.h).

## Continue learning

[Course contents](../../../courses/distributed-learning/index.html) · [Previous: Check that rejected training preserves the model](090-preserve-a-model-after-rejected-training.md) · [Next: Plan a distributed experiment from a local baseline](092-plan-distributed-work-from-a-local-baseline.md)
