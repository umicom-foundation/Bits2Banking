<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/distributed-learning/088-compare-results-with-numerical-tolerances.md

PURPOSE:
Compare floating-point results with explicit tolerances

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Compare floating-point results with explicit tolerances

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

## Why two correct calculations can differ slightly

Computers store a finite selection of real-number approximations. Adding small contributions in a different order can change the last few represented digits. Splitting a graph into groups can therefore change rounding without changing the intended mathematics.

The demonstration compares two observations. Loss is one average prediction-error number. Logits are the model's raw prediction scores before conversion to probabilities. Comparing only loss could miss a difference in individual output scores, so the program also inspects all 2,080 logits for one eight-token context.

## Read the criteria

1. Confirm both models have exactly one completed optimiser step.
2. Confirm their losses are finite and differ by less than `1e-5`.
3. Compare corresponding logits and take the largest absolute difference.
4. Require that difference to be below `3e-5` and finite.

These limits match the existing educational regression's comparison scale. They are not universal tolerances for every model, device or optimisation. A later change to computation order needs evidence that an appropriate tolerance still detects meaningful regressions.

## Run a controlled comparison

Run arguments `1`, `2` and `5` separately. Record the compiler, source revision, argument, losses and largest difference. Keep the seed, input arrays and learning rate fixed. Changing several variables together makes a failure harder to explain.

If a comparison fails, check the first nonzero service result and confirm both models used the same configuration. Next inspect changes to reduction order, gradient scaling and parameter-update timing. Do not loosen a tolerance simply to make the program exit successfully.

## Exercise

Imagine the losses differ by 0.000001 but one logit differs by 0.4. Explain why a loss-only check is insufficient. Then imagine the output is NaN, meaning 'not a number'. The finite-value check is necessary because some ordinary comparisons with NaN are false in surprising ways. A useful test states both its numerical domain and its accepted error.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/ai_training/test_training_gradient_accumulation.c).

## Continue learning

[Course contents](../../../courses/distributed-learning/index.html) · [Previous: Weight a shorter final microbatch correctly](087-weight-a-short-final-microbatch.md) · [Next: Measure memory without confusing a plan with a limit](089-measure-memory-without-promising-a-budget.md)
