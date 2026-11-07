<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/distributed-learning/085-read-the-microbatch-laboratory.md

PURPOSE:
Read the microbatch laboratory from input to result

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read the microbatch laboratory from input to result

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

## Start with the data flow

A token is a numeric identifier for one item in a model's input vocabulary. This laboratory constructs identifiers directly; it does not download documents or tokenize private text. An array is a numbered collection of values. `input[40]` stores forty input identifiers and `target[40]` stores the expected next identifiers.

```text
40 input identifiers + 40 target identifiers
                  |
           identical initial models
              /            \
        one large graph   smaller graphs
              \            /
             one update each
                  |
        compare loss and predictions
```

`UmiAiTrainingDecoderConfig` describes the model: a vocabulary of 260 identifiers, contexts of eight tokens, eight channels, sixteen hidden channels and two attention heads. A context is the stretch of tokens considered together. A channel is one coordinate in the internal representation. An attention head computes one part of how earlier positions contribute to a prediction. These small dimensions keep the example inspectable on a CPU.

## Follow the program

1. Find the argument checks. Only `1`, `2` and `5` are accepted as microbatch sequence counts.
2. Find the loop that initializes the arrays. Every identifier stays inside the vocabulary.
3. Find both `UmiAiTrainingDecoderCreate` calls. The same seed, 4477, gives both models the same starting point for this comparison.
4. Find the two training calls and the later inspection calls. The program observes the service rather than implementing another neural network.
5. Find `finish`. Both owned model objects are destroyed there, including when a service call fails.

## Try and explain

Run the program with `--help`, then `2`, then `0`. Help returns successfully without training. The supported experiment returns zero if its comparisons pass. The unsupported argument returns a nonzero usage result. In PowerShell inspect `$LASTEXITCODE` immediately; in Bash use `echo $?`.

Write a three-sentence explanation of what was supplied, what was changed and what was compared. Do not describe this deterministic numerical fixture as a useful language model: its purpose is to expose the mechanics of one update.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/learning/native-llm/inspect_accumulation.c).

## Continue learning

[Course contents](../../../courses/distributed-learning/index.html) · [Next: Count sequences, tokens and optimiser updates](086-count-sequences-tokens-and-updates.md)
