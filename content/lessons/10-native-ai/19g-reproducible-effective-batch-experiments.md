# Supplement 19G — Reproducible Effective-Batch Training Experiments

**Bits to Banking · Build Your Own LLM from Scratch**  
**Author:** Sammy Hegab · **Organisation:** Umicom Foundation  
**Implementation:** ISO C23 · **Source of truth:** Umicom Framework

## Learning objectives

After this lesson, a learner should be able to explain the difference between a
source-file sample, a training sequence, a microbatch, an effective batch and
an optimiser step. They should be able to configure a native training experiment
that uses more examples than one training graph can hold; reproduce that run;
and verify that an interrupted and resumed experiment yields the same final
checkpoint as an uninterrupted experiment.

These experiments measure an elementary byte-level decoder trained from random
parameters. Passing the exercises **does not** establish expertise in C23,
Calypso or Umicom Framework design.

## 1. The engineering problem

Our trainable decoder has a maximum of 16,384 elements per tensor. Suppose our
vocabulary has 260 token IDs and each source-code sequence contains eight
positions. An effective batch of eight sequences needs:

```text
8 sequences × 8 positions × 260 vocabulary entries = 16,640 logits
```

One logits tensor is therefore too large, even though a typical computer has
ample RAM. Increasing host RAM does not remove the per-tensor restriction.

Rather than changing the network architecture, divide the effective batch into
four microbatches of two sequences:

```text
Source dataset (TRAIN partition only)
          |
          v
    Effective batch
       8 contexts
          |
  +-------+-------+-------+-------+
  |       |       |       |       |
  2       2       2       2       sequences
  |       |       |       |
  Forward/backward in bounded tape graphs
          |
     Sum gradients
          |
    ONE SGD update
```

Each microbatch uses `2 × 8 × 260 = 4,160` logits. The graph is rewound before
processing the next microbatch. The Framework-owned decoder aggregates gradients
and performs **one** atomic optimiser update over the complete effective batch.

The parameters, learning rate and completed optimiser-step counter are unchanged
until all microbatches have been processed successfully.

## 2. Deriving the correct gradients

Assume three microbatches contain 16, 16 and 8 token positions. If their average
losses are `L1`, `L2`, and `L3`, the combined loss is:

```text
L = (16 × L1 + 16 × L2 + 8 × L3) / 40
```

The correct gradient is weighted in the same way:

```text
g = (16 × g1 + 16 × g2 + 8 × g3) / 40
```

Simply adding three already-averaged gradients and dividing by three would
underweight the larger microbatches and overweight the final, smaller one.
The existing `UmiAiTrainingDecoderTrainAccumulated` service implements the
weighted reduction using finite-value checks and a single tape-owned update.

## 3. Dataset sampling is independent of graph capacity

The existing dataset sampler accepts at most four complete sequences per call.
That does not mean an optimiser step is limited to four sequences. The new
experiment coordinator draws eight sequences as **two deterministic calls**:

```text
Sampler draw 0: 4 sequences
Sampler draw 1: 4 sequences
                  |
          8 source contexts
                  |
          4 microbatches
                  |
          1 optimiser step
```

Every draw uses the explicit training partition; the held-out partition is used
only for evaluation. Sampling is reproducible because each call uses an
absolute identifier:

```text
drawId = absoluteOptimiserStep × drawsPerStep + drawWithinStep
```

For an eight-sequence effective batch and a four-sequence sampler, `drawsPerStep`
is two. A resumed run beginning after step two continues with the same draw
identifiers that an uninterrupted run would use for step three.

**Important limitation:** The current portable decoder checkpoint stores weights,
architecture and optimiser-step count, but does not bind the original dataset,
training seed, effective batch settings or learning rate. The operator must
verify the same reviewed plan and source files before resuming.

## 4. Read the actual C23 implementation

The public contracts are:

- `framework/include/umicom/ai/training/experiment_accumulation.h`
- `framework/include/umicom/ai/training/experiment_plan.h`
- `framework/include/umicom/ai/training/gradient_accumulation.h`

The shared implementation is in:

- `framework/src/ai/training/experiment.c`
- `framework/src/ai/training/experiment_plan.c`
- `framework/src/ai/training/decoder.c`

`UmiAiTrainingExperimentRunAccumulated` and
`UmiAiTrainingExperimentResumeAccumulated` use the same dataset, model,
checkpoint and evaluation services as ordinary experiments. The established
`UmiAiTrainingExperimentRun` and `Resume` APIs remain available without changes
to their input structures or their single-batch execution semantics.

The training plan has two **opt-in keys**:

```ini
UMICOM-AI-EXPERIMENT-1
manifest=manifest.txt
steps=4
eval_interval=2
eval_batches=2
batch_sequences=1
effective_sequences=8
microbatch_sequences=2
learning_rate=0.025
model_seed=20261021
train_seed=4477
eval_seed=5544
context=8
channels=8
hidden_channels=16
attention_heads=2
```

The existing `batch_sequences` field continues to control the number of
sequences per **held-out evaluation draw**. `effective_sequences` determines
how many contexts contribute to one training update, and
`microbatch_sequences` determines the largest forward/backward graph.

Both new keys must appear together. Omitting both retains the original
single-batch training behaviour. A plan containing only one is rejected, and
the original strict plan parser rejects plans with unrecognised new keys.

## 5. Build, test and run on Windows

Use the actual Framework checkout under `C:\umicom\Umicom-Applications`.
PowerShell is used to invoke the native C23 program; it is not a training
implementation language.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" `
    -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    --output-on-failure --no-tests=error

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-experiment.exe" `
    ".\framework\learning\native-llm\fixtures\accumulated-experiment.conf"
```

The example prints the independent training and evaluation sizes and reports
held-out cross-entropy, sampled perplexity and the completed optimiser steps.
No checkpoint is written unless an explicit **new** output path is supplied.

## 6. Tests that demonstrate the claim

The focused native tests verify that:

1. A reviewed plan enables accumulation without weakening the old strict parser.
2. The same source, plan and seed produce identical checkpoint bytes across two runs.
3. A shorter run followed by resume produces the same checkpoint as the
   uninterrupted run to the same absolute optimiser step.
4. Invalid graph sizes, missing keys and cancellation preserve caller outputs
   and do not publish a partially trained decoder.

The tests do not prove equivalence between every microbatch order and a full
batch in real arithmetic: floating-point accumulation can produce small
rounding differences. Exact checkpoint equality is tested between **equivalent
repeated experiments using the same reduction order**.

## 7. Review questions and independent exercises

**Exercise A — Count the logits.** Calculate the logits for six sequences of
12 tokens with a 260-token vocabulary. Can the present tape represent all of
them in one output tensor? How many logits are required for microbatches of
one, two or three sequences?

**Exercise B — Uneven final microbatch.** For five sequences and a
microbatch limit of two sequences, write down the microbatch sizes and derive
the weighted mean-loss formula.

**Exercise C — Confirm the optimiser-step counter.** Run the example with
four optimiser steps. Explain why its step counter is four rather than 16.

**Exercise D — Check resume provenance.** Before continuing from a checkpoint,
identify the information you must verify manually: dataset contents, training
seed, effective and microbatch sizes, model architecture and learning rate.

**Engineering note:** This lesson prepares the native training infrastructure
for longer, better-controlled experiments. It does not expand the elementary
model's reasoning ability by itself.
