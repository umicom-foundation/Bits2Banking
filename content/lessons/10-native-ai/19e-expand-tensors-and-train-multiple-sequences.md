# Supplement 19E — Train Multiple Source-Code Sequences with Wider Native Tensors

**Bits to Banking · Building an LLM from Scratch**  
**Author:** Sammy Hegab · **Umicom Foundation**  
**Implementation:** C23 in Umicom Framework

## Learning outcome

By the end of this lesson, you should be able to calculate how tensor shapes determine the memory required for a language-model training step, explain why a seemingly small model can reject a larger mini-batch, examine the actual Framework memory-limit implementation and run a complete multi-sequence training experiment. We are not introducing a replacement neural-network library: every learning exercise uses the same Umicom Framework implementation used by our earlier decoder lessons.

## 1. Why did the model reject two sequences?

Our early decoder has a vocabulary of 260 token IDs: four reserved IDs and one for each possible byte. Suppose it reads a context of eight tokens. The output layer must produce 260 scores (called *logits*) for each token position. For one sequence, that means:

\[
8\ \text{positions} \times 260\ \text{classes} = 2,080\ \text{logits}.
\]

A score is stored as an IEEE 754 32-bit floating-point number, using four bytes. The output values alone therefore require `2,080 × 4 = 8,320` bytes. During training, gradients, intermediate activations and attention probabilities consume additional memory.

Two independent sequences in the same optimisation step require `2 × 8 × 260 = 4,160` logits. The initial teaching tape could hold only 4,096 scalar values per tensor. The calculation did not fail because the machine ran out of memory. It failed because we deliberately set a smaller safety limit in our neural engine.

> **Engineering principle:** An explicit software limit is not the same as physical RAM capacity. Raise limits only after checking every dependent allocation, multiplication and caller-owned buffer.

## 2. The difference between a shape and an allocation

A tensor shape describes how many values are logically arranged along each axis. One logits tensor has the shape `[sequences × time, vocabulary]` because our existing automatic-differentiation tape stores row-major matrices. Four independent sequences with context eight produce:

| Dimension | Value | Meaning |
| --- | ---: | --- |
| Sequences | 4 | Four unrelated source-code examples |
| Context length | 8 | Eight token positions in each example |
| Rows | 32 | `4 × 8` token positions |
| Columns | 260 | One score for each vocabulary ID |
| Total logits | 8,320 | `32 × 260` float values |
| Output-value bytes | 33,280 | `8,320 × 4` bytes |

A separate gradient array of the same shape adds another 33,280 bytes. Other intermediate tensors, especially within the Transformer Block, also need space. The size of the entire computational graph therefore cannot be inferred from the logits alone.

The current Framework raises the per-tensor limit to **16,384 elements**. This permits the four-sequence example while keeping a finite, testable upper bound.

## 3. Follow the authoritative Framework code

Open `C:\umicom\Umicom-Applications\framework\include\umicom\ai\training\tape.h`. Find `UMI_AI_TRAINING_MAX_ELEMENTS`. This is the authoritative upper bound used by the native automatic-differentiation tape. Matrix multiplication is implemented in `src/ai/training/matrix_kernel.c`, with its contract declared in `include/umicom/ai/training/matrix_kernel.h`.

The matrix kernel preserves its small-result stack fast path but uses a shape-sized temporary heap allocation for results above the original 4,096-element ceiling. It validates dimensions and input values before allocation, then computes the entire output before copying to the caller. The previous stack-workspace declaration is retained inside a documented disabled block for engineering review. No existing public matrix function was renamed.

A simplified shape calculation, not an alternative implementation, is:

```c
/* Dimensions of one output-logits matrix for four independent sequences. */
const size_t sequences = 4U;
const size_t contextLength = 8U;
const size_t vocabularySize = 260U;
const size_t rows = sequences * contextLength;
const size_t elements = rows * vocabularySize;
const size_t bytes = elements * sizeof(float);
/* elements == 8320 and bytes == 33280 on the supported FP32 platform. */
```

This calculation illustrates the shape. The real Framework code additionally checks products before multiplication, validates capacities and uses ownership-aware allocation. Do not replace the Framework validation with this explanatory fragment.

## 4. Why temporary storage matters

A matrix multiplication may be asked to write its result over the same memory that contains one of its input matrices. Calculating directly into the caller's output would overwrite input values that are still needed for later dot products.

The existing Umicom matrix API therefore uses staging: it computes the complete answer in a separate temporary buffer, checks each resulting floating-point value, and only then copies the answer to the caller. This also provides **failure-atomic behaviour**. If an input contains `NaN`, an allocation fails or a result cannot be represented, the caller's existing output data remains unchanged.

The change to shape-sized heap storage avoids reserving an entire maximum-capacity result on the C call stack for every matrix operation. It does **not** make temporary workspace memory part of the tape's committed-graph accounting. The tape budget measures only committed tensor nodes and their retained memory.

## 5. Build the real experiment

Open Windows PowerShell. The commands below use your established `C:\umicom` repository layout and the MSYS2 UCRT64 C23 toolchain:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" `
    -G Ninja `
    -DCMAKE_BUILD_TYPE=Debug `
    -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    --output-on-failure --no-tests=error

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-tensor-scale.exe"
```

Inspect the reported tensor ceiling, token count, logits size, training cross-entropy and peak committed graph memory. The demonstration uses 32 synthetic byte-token positions in four independent sequences. It performs a real optimisation step through the canonical decoder and then rewinds temporary graph nodes.

The inspected training loss is a measurement on a synthetic input. It is not proof of generalisation or programming expertise.

## 6. Apply multi-sequence learning to real C23 source files

The Framework's existing `dataset_manifest.h` and `experiment.h` APIs can already sample held-out and training files separately. With the expanded tensor limit, a reviewed experiment can use up to four independent sequences per optimiser step, subject to all configuration and resource checks. The present dataset API still has its own four-sequence ceiling even though the tensor shape planner can calculate a theoretical maximum of seven sequences for this particular decoder configuration.

That distinction is important: **shape feasibility does not override a dataset contract, file-access policy, model configuration or memory budget**. Our existing fixture manifest contains two training files and one independently held-out evaluation file. The training/evaluation partition remains unchanged when the number of sampled sequences increases.

A training experiment can use more examples per step without ever combining tokens from one source document with another. Attention continues to be causal within each independent sequence; predictions do not read future tokens or neighbouring examples.

## 7. Verify that old checkpoints still work

The educational model's checkpoint format (`UMIDEC04`) has not changed. Only the accepted size of individual in-memory training tensors has increased. The automated tests train a decoder with a token-embedding table larger than the old limit, encode its weights, decode them into an independent model and verify that the resulting logits and re-encoded bytes match. Earlier valid models continue using the same parameter names, ordering and checkpoint representation.

Checkpoint compatibility does not mean arbitrary large models can be saved: the current checkpoint file has its own maximum size. Nor does a checksum prove the authenticity of downloaded model weights. Approved model sources and dataset permissions remain essential.

## 8. Exercises and assessment

**Exercise A — Memory arithmetic.** Calculate the shape and logits-value bytes required for three independent sequences with context length eight and vocabulary size 260. Then calculate the same value for four sequences. Which result exceeded the original tensor limit?

**Exercise B — Regression evidence.** Find and run the tests `framework.ai.training.wide_matrix`, `framework.ai.training.wide_tape`, `framework.ai.training.wide_decoder` and `framework.ai.training.multi_sequence`. Identify which verifies backwards gradients and which verifies checkpoint equivalence.

**Exercise C — Failure atomicity.** Explain why staging is needed if a matrix result aliases its input, and why a complete output must not be copied to the caller before all numerical checks pass.

**Exercise D — Engineering judgement.** Suppose a model requires a 20,000-element activation tensor. Is 16 GB of RAM sufficient evidence that our present Framework will accept it? Identify the exact software contract that would reject this tensor.

**Extension — Independent evaluations.** Use the existing reviewed manifest and native experiment CLI to compare single-sequence and multi-sequence training under the same step budget and seeds. Record both training loss and held-out evaluation loss. Discuss why changing the batch size changes the optimisation path, even when the corpus does not change.

## 9. What we have and what remains

We have a native C23 Transformer decoder with wider bounded tensor support, shape-sized CPU matrix scratch storage, preserved gradient propagation, trainable larger embeddings, reproducible source-code mini-batches and the established checkpoint codec. The suite also contains numerical-parity and negative-input tests. The Framework remains the **single source of truth**, while the command-line application is a thin educational client.

We do not yet have an unrestricted tensor allocator, a multi-block production language model, general GPU training, dynamic context scaling, a full optimiser-state checkpoint or a professionally evaluated C23 expert. Those require further design and careful measurement rather than simply removing safety limits.

**Next reading:** Review the preceding training-memory lesson and the Framework learning guide `learning/native-llm/TENSOR_SCALING.md`, then inspect the complete source files under `src/ai/training/` and their regression tests.
