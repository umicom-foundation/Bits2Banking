<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/distributed-learning/089-measure-memory-without-promising-a-budget.md

PURPOSE:
Measure memory without confusing a plan with a limit

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Measure memory without confusing a plan with a limit

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

## What a capacity plan describes

Memory holds parameters, gradients and intermediate results. `UmiAiTrainingCapacityPlanCompute` reports selected logical payload sizes from the decoder's authoritative shapes. A payload is the data portion of an allocation. Metadata, allocator bookkeeping and other temporary objects also consume memory.

The field `minimumRetainedPayloadBytes` deliberately describes a lower bound on selected data. It is not a safe whole-process memory budget. Scheduling a worker with exactly that much available memory could still fail.

## Read two observations together

The demonstration prints the microbatch token capacity from the plan and the peak bytes recorded by the model's training tape. The tape manages computation-graph allocations. Its peak is useful for comparing graphs, but it is not the operating system's measurement of all process memory.

1. Run with argument `5` and record the reference and accumulated tape peaks.
2. Run with argument `1` and record them again.
3. Explain which temporary graph became smaller.
4. State which quantities the program did not measure, such as total process resident memory or energy consumption.

Do not infer that every microbatch choice has identical runtime. Smaller groups can reduce memory at the cost of extra repeated work and scheduling overhead.

## Explore a real guard

The decoder offers `UmiAiTrainingDecoderSetMemoryBudget`. Its budget applies to tape-managed committed graph storage. Zero restores the unlimited setting for that particular accounting mechanism. The existing accumulated-limits regression sets a budget near the current allocation, attempts training and checks that rejection preserves the model.

Read that test before changing it. A budget rejection is an expected result when a requested operation cannot fit. Catching it is safer than assuming a planned number guarantees success.

## Exercise

Design a worker-capacity record with separate fields for supported tensor shape, observed tape peak, observed process peak and available host memory. Include units and the tool used for every measurement. A single label such as 'powerful machine' does not provide enough information to admit a task.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/ai/training/capacity_plan.h).

## Continue learning

[Course contents](../../../courses/distributed-learning/index.html) · [Previous: Compare floating-point results with explicit tolerances](088-compare-results-with-numerical-tolerances.md) · [Next: Check that rejected training preserves the model](090-preserve-a-model-after-rejected-training.md)
