# Supplement 19D — How Much Memory Does Training Our Language Model Need?

**Bits to Banking · Build Your Own LLM from Scratch**  
**Author:** Sammy Hegab · **Umicom Foundation**  
**Languages:** C23 for implementation, PowerShell for interactive build and tests

## Learning objectives

By the end of this lesson, the learner should be able to explain the difference
between the model's parameters, intermediate activations, parameter gradients
and auxiliary training storage. You will inspect the actual native Umicom
Framework training tape, calculate the space needed for a small decoder,
configure a memory budget and observe how rejected work is handled without
corrupting model state.

This lesson builds on matrix multiplication, backpropagation, causal attention,
checkpoints and the inference profiler. The goal is to understand the *real
memory ownership rules of the application we are building*, not to copy a
separate experimental neural-network implementation into the educational
repository.

## 1. Where does training memory go?

A language model stores *parameters* such as its embedding vectors, attention
projection matrices and feed-forward weights. During training, the model must
also retain enough information to calculate derivatives of the loss with
respect to those parameters. That creates several distinct categories of
memory use.

Consider a trainable C23 tensor containing a four-by-four matrix. It owns
16 `float` values, which occupy 64 bytes when `float` is IEEE 754 binary32.
It also owns 16 gradient values: another 64 bytes. The Framework additionally
allocates metadata that records the matrix dimensions, its owning tape, its
operation and any earlier tensors on which it depends.

Suppose the matrix becomes the input to a `ReLU` activation. The resulting
matrix is another tensor and owns another values array and gradients array.
These derived tensors are **activations**: they belong to the computation used
for the current training step. They are not permanent model parameters.

A causal-attention operation can additionally preserve the probability
weights used when backpropagating through attention. An embedding gather keeps
an owned copy of the selected integer token IDs so gradients can be returned
to the correct rows in the embedding table. An exact memory estimate must
account for these buffers, not only the model's weights.

**Key distinction:** the memory reserved for a trained model is only part of
what the same model may need during training.

## 2. Calculating our decoder's parameter storage

Our initial byte tokenizer provides 260 token IDs. Consider the native decoder
configured for a context of eight tokens, eight channels, a sixteen-channel
feed-forward hidden layer and two attention heads.

The decoder's parameter shapes are not hard-coded in this lesson. The
Framework already defines them in the native decoder schema, which the memory
planner reuses. For this configuration there are 15 trainable parameter tensors
with **4,792 scalar parameters**.

At four bytes per scalar:

\[
\text{parameter value bytes} = 4,792 \times 4 = 19,168
\]

Training also retains corresponding gradient arrays:

\[
\text{parameter gradient bytes} = 4,792 \times 4 = 19,168
\]

Thus parameters and their gradients require **38,336 bytes**, before accounting
for tape metadata, activations and attention probability storage. This value
is an exact logical float32 payload count for the specified architecture,
not a measurement of the operating system's resident memory.

For one sequence of eight tokens, the decoder also constructs an output-logit
matrix containing `8 × 260 = 2,080` values, consuming 8,320 bytes. Two
attention heads over the same eight-token context retain up to
`2 × 8 × 8 = 128` probabilities, occupying 512 bytes in this teaching
implementation.

These items are **not the whole forward graph**: there are additional layer
normalisation, query/key/value, residual and feed-forward tensors. A careful
engineer must distinguish a *lower-bound payload calculation* from a safe
memory budget for the complete training operation.

## 3. Why a computer with plenty of RAM can still reject a model

The present Umicom learning tape deliberately limits each tensor to 4,096
scalar elements. These limits make debugging and numerical verification
manageable. They are not measurements of the available RAM.

What happens if we double the minibatch from one eight-token sequence to two?
The output logits would need:

\[
2 \times 8 \times 260 = 4,160 \text{ elements}
\]

That exceeds the existing 4,096-element tensor limit. Our Framework capacity
planner therefore returns `UMI_STATUS_CAPACITY_EXCEEDED` before constructing
the model. It also checks attention-probability storage and the exact parameter
shapes, using the same rules enforced by the native decoder.

You should never solve this kind of failure by silently discarding training
examples, shrinking a parameter without the user's knowledge or changing the
public tensor contract without reviewing the resulting tests and checkpoints.

## 4. Committed memory versus temporary work

The Framework exposes `UmiAiTrainingTapeMemoryInspect()` to inspect allocations
that have successfully joined a training tape. Its response records current
bytes, peak bytes, tensor count and separate value, gradient and auxiliary
payloads. The high-water mark remains visible after temporary nodes have been
released.

A new budget can be selected using
`UmiAiTrainingTapeSetMemoryBudget()`. A value of zero means that no explicit
*committed-graph budget* is enforced. A positive budget below the current
allocation is rejected without changing the tape. When a new computed tensor
would exceed the limit, its candidate allocation is released rather than
published. The existing graph and caller-provided output handles remain
unchanged.

The budget is **not a hard process-memory limit**. A C operator may create
temporary scratch buffers and compute an unpublished candidate node before
checking its committed cost. The memory inspector does not count those
short-lived allocations, allocator metadata or C stack frames. Compare with a
process-level profiler if total RAM use is the question.

Applications access the same measurement without owning internal tape pointers
through `UmiAiTrainingDecoderMemoryInspect()` and
`UmiAiTrainingDecoderSetMemoryBudget()`. Reusable implementations belong to
Umicom Framework; the user interface remains a thin consumer.

## 5. Build and inspect the real implementation

Open PowerShell and run the dedicated native laboratory. These instructions
use the exact checkout under your local Umicom workspace.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" `
    -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    --output-on-failure --no-tests=error

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-training-memory.exe"
```

The console first reports the capacity plan. It then creates the decoder,
records how much committed tape memory its parameters require, performs a
single training step and inspects memory again. Although the temporary graph
was released, the observed high-water mark remains above the current value.

The demonstration reads no confidential Calypso documents, connects to no
banking service and saves no checkpoint. It is a self-contained test of our
own native numerical engine.

## 6. Verify failure behaviour, not just successful training

Consider a model whose parameter tensors already occupy 42,704 bytes of
committed tape memory in one tested platform configuration. If you apply a
budget of 42,705 bytes, the next nontrivial derived tensor cannot be admitted.
The decoder returns a capacity error and discards temporary graph nodes.

The related regression test verifies that the rejected training attempt did
**not** change the model weights, completed step count, caller's reported loss
or saved checkpoint representation. Removing the limit allows the same model
to train normally.

This is more valuable than only checking whether an allocation function
returned `NULL`. It tests the consistency of the *whole training transaction*.

The exact metadata byte count can differ between platforms and compiler
ABIs. Always rely on the native inspector when reporting your own computer's
memory usage; do not assume that a debug Linux figure equals Windows memory.

## 7. Exercises and questions

**Exercise A — Calculate a tensor budget.** A training tensor has 50 rows and
12 columns. Calculate how many float32 value bytes and gradient bytes its
arrays require. Explain why the node also needs storage beyond those arrays.

**Exercise B — Plan a minibatch.** For a vocabulary of 260 token IDs and a
context of eight tokens, calculate the number of output logits for one,
two and three sequences. Which fit within 4,096 elements?

**Exercise C — Inspect an actual training run.** Run the native inspector,
record its committed and high-water memory numbers and explain why they
differ after training has finished.

**Exercise D — Test failure isolation.** Read
`tests/ai_training/test_training_decoder_memory.c`. Identify where the test
checks that an insufficient memory budget leaves the model's state unchanged.
Why would changing the weights before returning a capacity error be dangerous?

**Extension — Realistic scale.** Research why larger transformer models require
memory for more than parameter values and their gradients. In particular,
consider optimiser state, attention probabilities, longer contexts and
multi-layer activation storage. Explain why increasing one constant in the
current teaching API cannot by itself create a production LLM trainer.

## 8. What this teaches us for specialist models

Our objective is a family of native specialised models, including C23,
Umicom Framework and treasury-management experts. Those models will require
larger corpora and eventually larger neural networks. Before growing the
network, we need trustworthy evidence about whether the limitation is model
quality, dataset preparation, compute time, tensor capacity or actual memory
pressure.

The new planner and memory inspector give us a reproducible way to start that
work without inventing performance claims or compromising existing training
behaviour. The present educational decoder remains small, CPU-based and not
suitable for safety-critical production use.

**Source of truth:**
`framework/include/umicom/ai/training/capacity_plan.h`,
`framework/include/umicom/ai/training/tape.h`, and
`framework/learning/native-llm/TRAINING_MEMORY.md`.
