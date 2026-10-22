# Supplement 19L — AdamW Effective Batches and Exact Checkpoint Continuation

**Author:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT  
**Implementation:** native C23 · **Source of truth:** Umicom Framework

## Why we need this lesson

Our earlier experiments showed two useful techniques. **Gradient accumulation** divides an effective training batch into smaller calculations that fit memory. **AdamW** keeps moving averages of earlier gradients to choose its next parameter update. We now combine both techniques without losing the optimiser's memory of previous steps.

Imagine we are training the Umicom assistant to complete small, reviewed examples from our C23 banking application. One training step may contain four independently sampled fragments. Processing all four fragments at the same time might require too much temporary memory, even though the underlying model parameters fit comfortably. A microbatch of one fragment works on only one quarter of that training graph. Crucially, we **do not update the model after every fragment**: we first combine all the gradients and make one AdamW update.

## Outcomes

You will be able to explain:

1. The difference between an **effective batch** and a **microbatch**.
2. Why a mean gradient from a smaller final microbatch must be weighted by the number of tokens it represents.
3. Why AdamW's first and second moments change **once per effective batch**, not once per microbatch.
4. How a combined decoder-and-AdamW checkpoint permits exact continuation under an unchanged training plan.
5. How to run native regression tests without disabling or disguising antivirus detections.

## A complete effective step, illustrated

Suppose the decoder reads four eight-token source-code fragments. We choose `microbatchSequences=1` so the Framework processes one eight-token fragment at a time. After each fragment it frees intermediate activations but retains the running parameter-gradient sums.

```text
Training fragments:  4 sequences × 8 tokens = 32 target positions

   Fragment A      Fragment B      Fragment C      Fragment D
       |               |               |               |
  forward/back     forward/back    forward/back    forward/back
       |               |               |               |
   8 gradients     8 gradients    8 gradients    8 gradients
       +---------------+---------------+---------------+
                               |
                    Token-weighted mean gradient
                               |
                    ONE transactional AdamW step
                               |
                   Model weights + moments update
                               |
                  Combined checkpoint can be saved
```

If microbatch `i` contains `N_i` target tokens and its mean parameter gradient is `g_i`, the effective gradient is:

\[g_{effective}=\frac{\sum_i N_i g_i}{\sum_i N_i}\]

For four equal eight-token fragments, this is simply the average of four gradient vectors. For a final shorter microbatch, the sizes matter. Adding unweighted microbatch means would over-represent the shorter fragment.

## AdamW state and the meaning of an optimiser step

AdamW maintains first-moment and second-moment arrays for the **same canonical parameters** used by the decoder. The simplified mathematical recurrences are:

\[m_t=\beta_1m_{t-1}+(1-\beta_1)g_t\]
\[v_t=\beta_2v_{t-1}+(1-\beta_2)g_t^2\]

Here `t` is the effective optimiser step, **not** the number of microbatches. A four-microbatch effective update advances `t` by one. Advancing AdamW four times would produce different parameter values and moment estimates and would not be equivalent.

The Framework-owned `UmiAiTrainingDecoderTrainAdamWAccumulated` operation reuses the same gradient reducer as accumulated SGD, then applies the existing transactional AdamW optimiser exactly once. No application copies neural-network mathematics or writes directly to tensor storage.

## Practical C23 contract

The public API is declared by the existing `gradient_accumulation.h` contract:

```c
UmiStatus UmiAiTrainingDecoderTrainAdamWAccumulated(
    UmiAiTrainingDecoder *model,
    UmiAiTrainingAdamW *optimizer,
    const size_t *inputIds,
    const size_t *targetIds,
    size_t tokenCount,
    size_t microbatchSequences,
    float learningRate,
    float *outLoss);
```

Its requirements are deliberately strict. The optimiser must belong to that decoder, token IDs must fit its vocabulary, the sequence length must divide the token count, the requested microbatch graph must fit the established tensor capacity, and the learning rate must be positive and finite. Failed calls do not publish a new optimiser step or overwrite `outLoss`.

The new experiment APIs, `UmiAiTrainingExperimentRunAdamWAccumulated` and `UmiAiTrainingExperimentResumeAdamWAccumulated`, select deterministic training windows using the existing source-manifest sampler. They evaluate on the held-out partition. They retain the published direct-batch AdamW API unchanged.

## Checkpoint continuation: a reproducible example

Consider an experiment scheduled for **six optimiser steps**. Run the first two effective steps, then save a combined decoder-and-AdamW checkpoint. Restore that pair and complete steps three through six using the original six-step learning-rate schedule. The regression test compares that result with an uninterrupted six-step run.

The comparison includes decoder parameters **and** AdamW moments. On identical source bytes, random seeds, microbatch setting, optimiser configuration and absolute-step schedule, the resulting combined checkpoint is byte-identical in the validated native environment.

**Limit:** the checkpoint file is not itself proof that training source content or the schedule has not changed. Verify their provenance independently before approving a resumed experiment. Its integrity checksum is an accidental-corruption check, not a digital signature.

## PowerShell laboratory — build and test

The commands below are interactive build instructions, not implementations of Umicom functionality. Open PowerShell with the MSYS2 UCRT64 compiler available:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" `
    -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    -R 'adamw_microbatch' --output-on-failure
```

After antivirus review of the existing quarantined binaries, run the **full test suite**. A CTest `BAD_COMMAND` because a security tool blocked a process is not a numerical test failure and should not be hidden by renaming executables or globally excluding your build folder.

## Reading the results

- **Numerical parity** compares trained predictions against a direct-batch AdamW update within an explicit float32 tolerance. It does not require bitwise equality when floating-point summation order differs.
- **Resume identity** compares complete combined checkpoint bytes when the microbatch setting and training plan are identical. Exact equality is expected for the same execution environment and deterministic operator ordering.
- **Failure atomicity** deliberately submits invalid inputs and verifies that the decoder, optimiser state and caller output remain unchanged.
- **Memory efficiency** compares peak retained graph allocations, not total Windows process working-set size.

## Review questions

1. Four microbatches of eight tokens produce how many AdamW parameter updates? **One.**
2. Why does the final shorter microbatch receive less weight? **Its mean represents fewer training examples.**
3. Why must we save AdamW moments? **They influence the next update even when model weights are identical.**
4. What must be retained across resume besides checkpoint bytes? **The approved source data, source split, seeds, optimiser options, microbatch setting and absolute-step learning-rate schedule.**
5. Is a locally quarantined executable automatically a false positive? **No. Investigate and obtain a vendor determination before running it.**

## Engineering boundaries and further work

The educational dataset sampler still bounds one training draw to four source sequences; larger effective draws require future sampler work. Our small C23 decoder is not a production coding assistant. The next meaningful work includes documenting corpus provenance and enforcing reviewed experiment identities at checkpoint acceptance, while developing a larger and more efficient native training runtime.

**Service to Many Leads to Greatness.**
