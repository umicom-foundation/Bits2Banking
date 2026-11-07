<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/distributed-learning/093-distinguish-publisher-trust-and-model-quality.md

PURPOSE:
Distinguish publisher verification from model quality

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Distinguish publisher verification from model quality

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

## Two questions require different evidence

'Who approved these bytes?' is a provenance question. 'Does this model perform the task well?' is a quality question. A valid signature can help answer the first under an approved key policy. It does not answer the second.

Framework's training-trust batch verifier checks several signed publications using existing signature and policy services. It returns a deterministic JSON receipt only when every publication satisfies its verification rules. The receipt itself is unsigned. The header also states that reading several files sequentially is not one atomic filesystem snapshot.

## Read the boundaries

1. Find the maximum batch size of eight publications.
2. Find the independently approved policy-file argument. Trust should not be selected by an untrusted candidate model.
3. Find the explicit evaluation time shared by the whole batch.
4. Find the duplicate-receipt rejection and unchanged-output-on-failure contract.
5. List the services the verifier does not perform: model execution, training, weight parsing and network access.

## Add a separate quality review

Use reviewed held-out examples that were not used to optimise the candidate. Define the metric, baseline and rejection threshold before seeing the candidate result. Keep evaluation data confidential when necessary. Check for overlap between training and evaluation sources, because memorised examples can make a weak model appear successful.

For untrusted workers, replicated computations may detect some errors but agreement alone does not prove honesty. Several workers can share a failure or malicious objective. Worker admission, independence assumptions and the cost of verification require explicit design.

## Exercise

Classify these observations: a matching digest, an approved signature, a lower held-out loss and ten matching worker replies. Explain what each supports and what it leaves unknown. A complete report retains all four as different evidence types rather than collapsing them into a single 'trusted' badge.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/ai/training/training_trust_batch.h).

## Continue learning

[Course contents](../../../courses/distributed-learning/index.html) · [Previous: Plan a distributed experiment from a local baseline](092-plan-distributed-work-from-a-local-baseline.md) · [Next: Write a reproducible training laboratory report](094-write-a-reproducible-training-lab-report.md)
