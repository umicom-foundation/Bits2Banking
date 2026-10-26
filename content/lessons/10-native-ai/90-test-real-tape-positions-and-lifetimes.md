# Lesson 90 — Test Real Tape Positions, Lifetimes and Repeatability

**Bits to Banking · Native AI · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework (C23)

## Purpose and prerequisites

Having checked the arithmetic in [Lesson 89](89-audit-rotary-gradients-against-an-oracle.md),
we now check the **lifetime of its data**. Read the [original illustrated
lesson](../../courses/llm-from-scratch/lessons/90-test-real-tape-positions-and-lifetimes.html)
for the full diagrams and test rationale.

A mathematical function can produce the right number while leaking memory,
retaining a stale gradient, using an expired tensor handle or partly changing
an output after failure. These are different classes of error and need
independent acceptance checks.

## Why repeated positions matter

For ideal rotary attention, shifting the query and key positions by the same
amount preserves their relative displacement:

`5 − 3 = 15 − 13 = 2`.

When both are moved together, their ideal rotary dot product remains the same.
Moving **only** the query changes the relative displacement and generally the
attention score. Finite-precision tests require a declared numerical
tolerance, not an assumption of universal bitwise identity.

The existing Framework lifecycle regression executes an eight-step training
problem at sixteen starting positions. Every run starts with the same bounded
query and key weights, then compares its loss trace, completed updates and
reported tape memory.

## Which nodes survive a training step?

The training tape owns parameter leaves, intermediate tensors, saved attention
probabilities and gradients. An optimiser changes the selected parameter
leaves. The next iteration must calculate a **new** forward graph from the
updated weights; retaining old intermediates would train against stale values.

The teaching experiment uses `UmiAiTrainingTapeRewind` to retain five original
leaf tensors and discard computed graph nodes. A post-update loss is measured
using a fresh forward pass. In an array named `lossAfterStep`, position zero is
the first completed update; position seven is the eighth.

A tape's **peak** tracked memory is the largest previously retained allocation.
Rolling back from 1,800 bytes to 1,200 bytes does not erase a peak of 1,800.
This is not automatically evidence of a leak; repeat runs and use sanitisers.

## Run the actual lifecycle qualification

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm\prefix-work" `
    -B ".\build\windows-ucrt64-native-llm-prefix-debug" -G Ninja `
    -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-native-llm-prefix-debug" `
    --target umicom-ai-training-rotary-qualification-lifecycle-test `
    --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-prefix-debug" `
    -R '^framework\.ai\.training\.rotary_qualification_lifecycle$' `
    --output-on-failure --no-tests=error
```

An invalid input (such as a non-finite weight) must be rejected without
replacing the caller's previously published report. A missing test executable
is **Not Run**, not a passing calculation.

## Practical exercise

A four-step run reports `lossAfterStep[2] = 0.08`. How many updates preceded
that observation? **Three.** Indices are zero-based.

Suppose the same experiment is repeated with only the key's absolute position
advanced. Should we assume the same RoPE score? **No.** Its relative offset
has changed.

If the tape reports a stable memory peak, does that prove there are no invalid
reads? **No.** Allocation accounting and sanitiser diagnostics measure
different properties.

This is also important for projection adaptation: independently owned adapter
leaves must outlive every training graph that refers to them. The new
[decoder projection laboratory](train-transformer-projections-with-response-only-loss.md)
uses a separate Framework tape so the historical decoder's fixed parameter
rewind cannot discard adapter leaves accidentally.

**Key point:** Reliable training requires mathematical parity, valid object
lifetimes, correct update order and failure-atomic outputs.
