# Accumulate Gradients Across Smaller Native Training Batches

**Bits to Banking · Build Your Own LLM from Scratch · Umicom Foundation**  
**Author and project originator:** Sammy Hegab  
**Implementation language:** C23  
**Repository of record:** Umicom Framework

## Purpose

A language model learns by adjusting its parameters using gradients computed
from examples. It is often useful to estimate the gradient using many examples
before changing the parameters. However, a large training batch requires large
intermediate tensors, including output logits, attention probabilities and
backpropagation buffers.

In this lesson, we use **gradient accumulation** to process one large *effective
batch* as several smaller **microbatches**. Each microbatch uses the real Umicom
Framework decoder and training tape. The Framework temporarily retains only
one microbatch's computation graph, copies its gradient information, and then
releases that graph. Once all examples have been processed, the optimiser
changes the model's parameters **exactly once**.

This is a genuine memory-management technique used in neural-network training.
It does not increase the number of model parameters or make the model more
intelligent without better training data and experiments.

## Prerequisites

Complete the earlier lessons covering the training tape, cross-entropy,
backpropagation, multiple sequences, checkpoints and training-memory budgets.
You should know that a tensor is a shaped array of numbers and that the
backward pass calculates how the loss changes with each trainable parameter.

## One large batch versus several microbatches

Our educational byte-level decoder uses 260 token IDs. Suppose we prepare eight
independent C23 source-code sequences containing eight input tokens each.

The total number of token positions is:

```text
8 sequences × 8 tokens = 64 token positions
```

The output layer would produce:

```text
64 positions × 260 token scores = 16,640 logits
```

The current educational training tape limits each tensor to 16,384 elements.
Consequently, the entire effective batch **cannot** be materialised as one
logits tensor, even before considering other activations.

Instead, process two sequences at a time:

```text
2 sequences × 8 positions × 260 logits = 4,160 elements
```

Repeat that operation four times, discarding temporary graph nodes after each
backward pass. Keep only the accumulated parameter gradients and the trainable
parameter values. The four microbatches still contribute to **one** optimiser
update over all 64 positions.

The model does not learn four times faster. We reduce peak graph memory at the
cost of processing multiple forward/backward passes. Actual training throughput
must be measured.

## The essential mathematics

Let a complete effective batch contain **N** tokens. Divide it into
microbatches with token counts **n₁**, **n₂**, and so on. Let **gᵢ** represent
the *mean* parameter gradient from microbatch **i**.

The correct effective-batch mean gradient is:

```text
G = (n₁ × g₁ + n₂ × g₂ + …) / N
```

The effective-batch mean loss uses the same weighting:

```text
L = (n₁ × L₁ + n₂ × L₂ + …) / N
```

The weights **nᵢ** matter when the final microbatch contains fewer sequences.
A plain average of microbatch means would give the short final microbatch too
much influence.

For example, suppose two microbatches contain 16 and 8 tokens, with mean
gradients of 0.20 and 0.50 for a particular parameter:

```text
G = (16 × 0.20 + 8 × 0.50) / 24
  = (3.20 + 4.00) / 24
  = 0.30
```

A simple average of 0.20 and 0.50 would incorrectly produce 0.35.

For SGD with a learning rate of 0.025:

```text
new parameter = old parameter − 0.025 × 0.30
```

The update must happen **once**, after every microbatch has contributed.
Updating after each microbatch would be ordinary small-batch SGD, a different
training procedure.

## How Umicom Framework implements this

The authoritative public interface is:

`framework/include/umicom/ai/training/gradient_accumulation.h`

The implementation extends the original Framework-owned training services:

- `framework/src/ai/training/decoder.c` composes forward, loss, backward,
  gradient collection, graph rewind and one final update.
- `framework/src/ai/training/tape.c` validates every supplied gradient and
  candidate parameter value before applying one transactionally checked SGD
  update.
- `framework/learning/native-llm/train_microbatches.c` is a thin command-line
  consumer. It does not duplicate training mathematics.

The high-level decoder operation is:

```c
UmiAiTrainingDecoderTrainAccumulated(
    model,
    inputTokenIds,
    targetTokenIds,
    effectiveTokenCount,
    microbatchSequences,
    learningRate,
    &meanTrainingLoss);
```

All inputs and outputs are caller-owned. The decoder owns its parameter
tensors; callers never receive writable model-weight pointers. The operation
is synchronous, so the caller must not use the same decoder simultaneously
from several threads.

### What happens to intermediate memory?

During each microbatch, the decoder builds a computation graph on the existing
training tape. Gradients from the backward pass are copied into temporary,
owned accumulation arrays with double-precision summation. The tape then
rewinds to its original parameter leaves, releasing the activation and
attention tensors.

After all microbatches complete, the Framework converts the weighted mean
gradients back to the model's float32 format. The tape performs one
**failure-atomic** SGD update: if any gradient or candidate weight is invalid,
none of the model parameters is changed.

An unsuccessful run does not increment the optimiser-step counter or write the
caller-provided loss result. Checkpoints, their existing binary format and the
ordinary single-batch training API remain unchanged.

## Practical laboratory: train using a source-code manifest

Open PowerShell and switch to the parent Applications repository:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
```

Configure the isolated native laboratory using the actual Framework source:

```powershell
cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" `
    -G Ninja `
    -DCMAKE_BUILD_TYPE=Debug `
    -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" --output-on-failure
```

Now train on the three small, original source files from our previously
reviewed native learning fixture. Two files belong to the training partition
and one is held out for evaluation:

```powershell
& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-microbatch.exe" `
    ".\framework\learning\native-llm\fixtures\manifest.txt"
```

A representative GCC Release run printed:

```text
Umicom native source-code gradient accumulation
Effective sequences: 8, tokens: 64; microbatch sequences: 2
Mean training cross-entropy: 5.553452
Optimiser steps: 1
Retained graph bytes: 42704 -> 42704; peak: 100768
This is a teaching experiment, not evidence of coding expertise.
```

The peak is an accounting measure for committed training-tape allocations,
not total process resident memory. Measurements can change with configuration
and future implementation improvements. The tiny source fixtures are not a
statistically meaningful benchmark of C23 competence.

## How we verify correctness

The Framework test suite checks the large-batch and accumulated approaches
against one another, using identical initial weights and examples. It
requires their losses and resulting logits to match within explicit floating-
point tolerances, because different summation orders need not be bitwise equal.

The tests also verify that an effective batch larger than the single-tensor
limit can train using smaller graphs; the final shorter microbatch receives
correct weighting; checkpoint save/reload still works; incorrect token IDs
and restrictive memory budgets cannot partially update the model; and each
effective batch increments the optimiser-step counter once.

The demonstration's temporary graph peak is also compared against the peak
observed while training a feasible complete batch directly.

## Exercises

1. Calculate the logits tensor size for 12 sequences containing eight tokens
   each with a vocabulary of 260 tokens. Why does it not fit our current
   single-tensor ceiling?
2. Divide those 12 sequences into microbatches of two sequences. How many
   forward and backward passes are needed before one weight update?
3. With a five-sequence batch, explain why microbatch sizes of two, two and
   one must not simply average their three mean gradients.
4. Run the command-line demonstration twice. Compare training loss,
   optimiser-step count and memory measurements. What must remain
   reproducible for a fixed seed and dataset?
5. Read the implementation of the supplied-gradient SGD operation. Identify
   where it refuses non-finite values and where it begins changing weights.
6. Test the behaviour when a training memory budget allows the persistent
   model weights but not an intermediate graph. Does a failure change the
   checkpoint bytes or completed optimiser steps?

## What comes next

This capability increases the **effective number of training examples per
optimiser update**, not the parameter count of the decoder. Larger experts
will still need scalable model storage, deeper architectures, efficient
activation handling, reliable experiment configurations and substantial
licensed training corpora.

The next engineering questions are whether accumulation can be integrated
into reviewed experiment plans without copying datasets, and how to manage
optimizer states and longer training runs reproducibly. Every modification
should continue using the Framework's authoritative model and tensor services.
