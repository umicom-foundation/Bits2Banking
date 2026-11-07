<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/distributed-learning/092-plan-distributed-work-from-a-local-baseline.md

PURPOSE:
Plan a distributed experiment from a local baseline

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Plan a distributed experiment from a local baseline

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

## Define the question before adding machines

Distributed learning assigns parts of training work to multiple processes or computers. A coordinator manages a round, while workers compute contributions. A verifier checks specified evidence. One physical computer may perform several roles in an experiment, but the responsibilities should remain explicit.

The local microbatch laboratory provides a reference for one numerical step. It is not a distributed trainer. It does not open sockets, authenticate workers or merge independently trained checkpoints.

## Learn from a low-communication design

The OpenDiLoCo paper and its public implementation study training with less frequent communication between workers. Their reported experiments are useful evidence for research design, not a performance promise for an unrelated model or network. Read the [paper](https://arxiv.org/abs/2407.07852) and [project](https://github.com/PrimeIntellect-ai/OpenDiLoCo) alongside the exact versions used in your own experiment.

A system that performs multiple local updates before communication is algorithmically different from this laboratory's accumulation of gradients before one update. Define that difference explicitly rather than using the word 'distributed' for both.

## Write a minimal experiment plan

1. Choose one fixed model configuration and reviewed dataset.
2. Measure a single-process reference: loss, runtime, memory and completed examples.
3. Define the worker assignment, base-checkpoint identity and contribution format.
4. Add two workers on a controlled local network before expanding to slower links.
5. Measure bytes transmitted, waiting time and failed or retried work separately from computation time.
6. Compare held-out quality at comparable work or elapsed-time budgets.

## Exercise

Create an empty results table before running anything. Use columns for source revision, worker count, accepted token positions, wall time, bytes sent, evaluation loss and failure count. Leave unavailable measurements blank and explain them; do not fill them with estimates presented as observations.

A useful result may show that distribution is slower for a small task. That finding can identify communication overhead or task granularity as the next engineering question.

## Read the source

[Open the example source](https://arxiv.org/abs/2407.07852).

## Continue learning

[Course contents](../../../courses/distributed-learning/index.html) · [Previous: Identify source data and continuation settings](091-identify-a-training-snapshot-and-continuation.md) · [Next: Distinguish publisher verification from model quality](093-distinguish-publisher-trust-and-model-quality.md)
