<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/distributed-learning/090-preserve-a-model-after-rejected-training.md

PURPOSE:
Check that rejected training preserves the model

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Check that rejected training preserves the model

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

## Failure must have a defined effect

A function can reject a request because an argument is invalid, a capacity is exceeded or memory cannot be allocated. The caller needs to know whether anything changed before the failure. The accumulated-training API promises that a failed call preserves trained weights, completed step count and the caller's loss output.

A checkpoint is a serialised representation of model state. Serialisation converts structured in-memory state into an explicit byte format. It does not mean copying raw pointers into a file.

## Follow the existing rejection test

1. The test creates a model and encodes a checkpoint into a `before` buffer.
2. It sets a visible sentinel value in `loss`, so an unexpected write is detectable.
3. It tries invalid group size, incomplete contexts, an invalid learning rate and an out-of-range target identifier.
4. It also constrains graph memory and tries another training call.
5. It encodes the model again and compares checkpoint lengths and bytes.
6. It verifies that the completed-step count is still zero.

`memcmp` compares byte sequences. Here the sequences use the checkpoint codec's defined representation. That is more meaningful than comparing an arbitrary C structure containing padding or pointers.

## Extend the reasoning to workers

A coordinator must not partially apply a rejected update. Validate the update's identity, expected shape and numeric values before changing authoritative parameters. Acknowledging a message and applying its update are separate actions; a retry must not apply the same accepted contribution twice.

This local test establishes only the API behaviour being exercised. It does not establish crash-safe distributed transactions or protect against a compromised worker. Those require their own storage and protocol contracts.

## Exercise

Write a table with columns Request, Expected status, Weights changed, Step count changed and Output changed. Fill rows for a valid call and each rejection above. For the valid row, expect one step. For rejected rows, expect unchanged state. Use this table when reading owner-run results rather than interpreting every nonzero status as a product defect.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/ai_training/test_training_accumulated_limits.c).

## Continue learning

[Course contents](../../../courses/distributed-learning/index.html) · [Previous: Measure memory without confusing a plan with a limit](089-measure-memory-without-promising-a-budget.md) · [Next: Identify source data and continuation settings](091-identify-a-training-snapshot-and-continuation.md)
