<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/distributed-learning/086-count-sequences-tokens-and-updates.md

PURPOSE:
Count sequences, tokens and optimiser updates

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Count sequences, tokens and optimiser updates

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

## Three different counts

A sequence is one complete context, here eight tokens. The effective batch contains five sequences, so it contains `5 × 8 = 40` token positions. A microbatch is the part processed by one temporary computation graph. An optimiser update is the final change to all trainable parameters. These quantities have different units.

| Argument | Sequences per graph | Token positions per graph | Final group | Optimiser updates |
|---|---:|---:|---:|---:|
| `1` | 1 | 8 | 8 | 1 |
| `2` | 2 | 16 | 8 | 1 |
| `5` | 5 | 40 | 40 | 1 |

A graph records intermediate calculations needed to compute gradients. A gradient describes how a small parameter change would affect the loss, the model's prediction error. Framework collects gradients from all groups, then updates the parameters once.

## Calculate before running

1. Divide forty by sixteen. Two full groups use thirty-two token positions.
2. Subtract thirty-two from forty. Eight positions remain.
3. Record the actual sequence of work as `16, 16, 8`.
4. Run the laboratory with argument `2` and compare its token-capacity and step-count output with your calculations.

The final group must contain whole contexts. The API rejects a token count that is not divisible by the configured context length. This is a shape rule: it ensures that a sequence is never silently cut in half.

## Understand the public contract

The parameters `inputIds` and `targetIds` point to caller-owned arrays. `tokenCount` counts elements, not bytes. `microbatchSequences` limits how many complete sequences one graph handles. `learningRate` controls the scale of the update. `outLoss` points to a float where the service writes the resulting mean loss on success.

## Check your understanding

For seven sequences of eight tokens and a microbatch size of three, write the group sizes in tokens. The answer is `24, 24, 8`; there is still one optimiser update. Seven separate optimiser calls would be a different experiment because each later call would see already modified weights.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/ai/training/gradient_accumulation.h).

## Continue learning

[Course contents](../../../courses/distributed-learning/index.html) · [Previous: Read the microbatch laboratory from input to result](085-read-the-microbatch-laboratory.md) · [Next: Weight a shorter final microbatch correctly](087-weight-a-short-final-microbatch.md)
