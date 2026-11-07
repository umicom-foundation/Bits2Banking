<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/distributed-learning/094-write-a-reproducible-training-lab-report.md

PURPOSE:
Write a reproducible training laboratory report

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Write a reproducible training laboratory report

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

## Make the result repeatable

A reproducible report lets another person understand and repeat the conditions of an experiment. It contains the inputs, method, observations and limitations. It should not contain credentials or private training text.

Start with the local microbatch experiment, which requires no remote account. Record the Framework revision using `git rev-parse HEAD` and record any uncommitted source differences separately. A commit identifier alone does not describe a modified working tree.

## Complete the report step by step

1. State the question: does dividing this fixed effective batch preserve the one-step result within the documented tolerances?
2. Record compiler, CMake and operating-system versions.
3. Record the model shape, seed, learning rate and deterministic input-generation rule.
4. Run each supported microbatch size and retain its output and exit code.
5. Run the focused CTest selection below after building its executable.
6. Explain failures and skipped checks separately. Do not label a check passed because its command was written in a guide.

```powershell
ctest --test-dir build/learning-accumulation -R '^framework\.ai\.training\.accumulation_demo\.' --output-on-failure --no-tests=error
```

In Bash use the same CTest command. The tests cover the three supported experiment sizes, help and a rejected argument. The existing deeper reducer tests remain separate coverage.

## Interpret the evidence

A passing result supports numerical consistency for this small fixture and build environment. It does not show that a model understands language, that a multi-host network is reliable or that a checkpoint is safe to deploy. Those are later experiments with different acceptance criteria.

## Capstone

Write a one-page proposal for a two-worker follow-up. Include assignment identity, authorised dataset scope, expected tensor shapes, duplicate handling, timeout handling, reference comparison and held-out evaluation. Mark every unimplemented protocol step as planned. Attach the local report as the starting measurement, not as proof that the distributed system already exists.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/learning/native-llm/inspect_accumulation.c).

## Continue learning

[Course contents](../../../courses/distributed-learning/index.html) · [Previous: Distinguish publisher verification from model quality](093-distinguish-publisher-trust-and-model-quality.md)
