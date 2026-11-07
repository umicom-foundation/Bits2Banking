<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/distributed-learning/087-weight-a-short-final-microbatch.md

PURPOSE:
Weight a shorter final microbatch correctly

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Weight a shorter final microbatch correctly

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

## A mean needs its denominator

A mean is a total divided by the number of items. Suppose three groups contain sixteen, sixteen and eight token positions. Their mean losses are 2, 4 and 8. Averaging these three means equally gives `(2 + 4 + 8) / 3`, about 4.67. That incorrectly gives the small final group as much influence as either larger group.

The token-weighted mean is:

```text
(16 × 2 + 16 × 4 + 8 × 8) / 40
= (32 + 64 + 64) / 40
= 4
```

The same principle applies to each coordinate of a mean gradient. Every coordinate must use the same effective-batch denominator. Do not divide once per worker merely because workers are convenient units of scheduling.

## Trace the implementation

1. Open `decoder.c` and find the active `CollectAccumulatedGradients` function.
2. Find `currentTokens`, which is the smaller of the remaining count and the microbatch limit.
3. Find `weightedLoss += ... currentTokens`. This converts the group mean back into its weighted contribution.
4. Find the inner loop that adds each gradient multiplied by `currentTokens`.
5. Find the division by `tokenCount` after every group has contributed.

The temporary sums use `double` and the final gradients use `float`. These are floating-point number types. The wider temporary representation reduces rounding during accumulation; it does not make arithmetic exact. The implementation also rejects nonfinite values, such as an infinity produced by an invalid numerical result.

## Exercise

Repeat the arithmetic with group sizes 8 and 32 and mean losses 1 and 3. The correct effective mean is 2.6. Explain why 2 is incorrect.

For a future distributed protocol, carry both the contribution and its sample or token count. Define whether padding, ignored targets or repeated samples contribute to that count. Agreement on a hash cannot repair an ambiguous denominator. This laboratory has no padding or ignored-target convention: it uses the supplied aligned token positions.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/decoder.c).

## Continue learning

[Course contents](../../../courses/distributed-learning/index.html) · [Previous: Count sequences, tokens and optimiser updates](086-count-sequences-tokens-and-updates.md) · [Next: Compare floating-point results with explicit tolerances](088-compare-results-with-numerical-tolerances.md)
