# Lesson 13 — From a Transformer Block to a Trainable Decoder

**Bits to Banking · Build Your Own LLM from Scratch · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Umicom Framework, native C23  
**Prerequisites:** Lessons 01–12, especially matrix multiplication, embeddings, causal attention and reverse-mode automatic differentiation.

## What you will build

Previous lessons created individual mathematical operators and a trainable Transformer Block. A block takes a matrix of hidden vectors and produces a matrix of hidden vectors. **A language model also needs a way to turn token IDs into vectors and vectors back into vocabulary predictions.** This lesson connects those pieces without creating a second tensor library.

At the end of this lesson, you can follow a batch of token IDs through every stage of our experimental decoder and verify that changing a future token does not change an earlier prediction. You will also train all parameters together, not merely the output layer.

> Scope: This is a bounded **one-block, decoder-only Transformer model** that initialises its weights from a seed and learns from a tiny corpus. It is a genuine trainable neural model, but it is neither a production language model nor an Umicom software-engineering expert. Its currently fixed context length, vocabulary and tensor caps are deliberate learning constraints.

## 1. The complete forward path

The new Framework implementation is in `include/umicom/ai/training/decoder.h` and `src/ai/training/decoder.c`.

```text
input token IDs                       [B × T]
       │
       ├── token embedding lookup      [V × C] -> [B × T, C]
       └── position embedding lookup   [T × C] -> [B × T, C]
                          │
                   add embeddings      [B × T, C]
                          │
              pre-LN Transformer Block [B × T, C]
                 ├── LayerNorm
                 ├── Q/K/V projections
                 ├── multi-head causal attention
                 ├── output projection + residual
                 ├── LayerNorm
                 └── feed-forward + residual
                          │
                 vocabulary projection [C × V]
                          │
                        logits         [B × T, V]
                          │
              cross-entropy and gradients
```

Here `B` is the number of sequences in one batch, `T` is the number of input positions in each sequence, `C` is the number of hidden channels and `V` is the vocabulary size. The existing Framework tape represents `[B × T, C]` as a two-dimensional row-major matrix; the sequence boundary is supplied explicitly to causal attention.

For a tiny example, take two sequences, each containing three positions, a vocabulary of five tokens and four hidden channels. The token embedding table has shape `[5,4]`, the position table `[3,4]`, and the flattened input has six rows. The final logits matrix has shape `[6,5]`: **thirty real-valued scores**, five for each position.

## 2. Why trainable position embeddings matter

Token identity alone does not tell a network whether a token appears first or last. A learned position embedding assigns a vector to each position. For input `Umicom Framework C23`, the lookup might conceptually produce:

| Position | Token lookup | Position lookup | Sum sent to the Transformer |
|---|---|---|---|
| 0 | `E[Umicom]` | `P[0]` | `E[Umicom] + P[0]` |
| 1 | `E[Framework]` | `P[1]` | `E[Framework] + P[1]` |
| 2 | `E[C23]` | `P[2]` | `E[C23] + P[2]` |

Both tables are **trainable leaves on the same Framework tape**. The existing `UmiAiTrainingEmbeddingLookup` operator accumulates gradients into the selected rows, including repeated positions across batches. This is reuse, not an application-local reimplementation.

These are absolute position embeddings, not rotary or relative positions. We may compare alternative approaches in a future native experiment.

## 3. Logits are scores, not probabilities

The Transformer Block produces a hidden vector `h_t` for each position. A learned output matrix `W_out` transforms it into vocabulary logits:

\[
 z_t = h_t W_{out}, \qquad
 h_t \in \mathbb{R}^{C},\;
 W_{out} \in \mathbb{R}^{C\times V},\;
 z_t \in \mathbb{R}^{V}.
\]

Suppose one position gives logits `[2, 1, 0]`. The stable softmax calculation subtracts the largest logit before exponentiating. The resulting probabilities are approximately `[0.6652, 0.2447, 0.0900]`. If the correct next token is the **second** vocabulary entry, the negative log-likelihood is

\[
 L = -\ln(0.2447) \approx 1.408.
\]

The Framework `UmiAiTrainingCrossEntropy` operator calculates this loss with a log-sum-exp formulation and differentiates it. We do **not** create a second softmax or gradient implementation in the decoder application.

## 4. Training all parameters as one operation

There are fifteen parameter tensors in the first decoder, including token embeddings, position embeddings, layer-normalisation scales and biases, Q/K/V matrices, output projection, feed-forward weights and biases, and the logits head.

The training step is performed by `UmiAiTrainingDecoderTrainStep`:

```text
1. Validate whole token sequences and vocabulary IDs.
2. Lookup token/position vectors, build one causal decoder graph.
3. Calculate average cross-entropy against known next-token IDs.
4. Reverse the graph to accumulate parameter gradients.
5. Validate ALL proposed SGD parameter updates.
6. Commit ALL updates together, or commit NONE.
7. Rewind temporary graph nodes and count one completed training step.
```

Step 5 is important. Batch 01 used `UmiAiTrainingSgdStep` on one parameter. Applying it repeatedly could partially update a model if a later parameter failed. Batch 04 extends the same tape with `UmiAiTrainingSgdStepMany`, which checks every candidate weight before changing any weight. Existing single-parameter SGD remains available and unchanged.

## 5. Inspect the real C23 contract

The new public decoder interface includes the following operations:

```c
UmiStatus UmiAiTrainingDecoderCreate(
    const UmiAiTrainingDecoderConfig *config,
    UmiAiTrainingDecoder **outModel);

UmiStatus UmiAiTrainingDecoderLogits(
    UmiAiTrainingDecoder *model,
    const size_t *inputIds,
    size_t tokenCount,
    float *outLogits,
    size_t capacity);

UmiStatus UmiAiTrainingDecoderTrainStep(
    UmiAiTrainingDecoder *model,
    const size_t *inputIds,
    const size_t *targetIds,
    size_t tokenCount,
    float learningRate,
    float *outLoss);
```

These are the exact intended public signatures in the Batch 04 implementation. The caller owns the token ID arrays and output buffers; the decoder owns its training tape and all parameter tensors. `tokenCount` must contain whole sequences of `contextLength`. `capacity` is expressed in **floats**, not bytes. Invalid inputs preserve output buffers.

The learner's implementation source is the definitive API reference. Read the function definitions and trace the `ForwardLogits` composition to `UmiAiTrainingTransformerBlockForward`, then to the canonical operators from Lessons 05–12.

## 6. Build and run on Windows

In PowerShell, **after** merging the package into the actual Framework checkout:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
      -B ".\build\windows-ucrt64-native-llm-debug" `
      -G Ninja -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
      --output-on-failure --no-tests=error

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-decoder-demo.exe"
```

The executable trains a tiny source-to-target mapping and reports training **and held-out** loss. It uses no pretrained weights, Python runtime, cloud provider or application-local neural maths.

## 7. A falsifiable test for causal masking

Use the same sequence prefix but change a later token:

```text
Sequence A: [0, 1, 2]
Sequence B: [0, 1, 4]
```

At time 0 and time 1, the logits must be **identical**, because neither position is allowed to observe position 2. The supplied `framework.ai.training.decoder_contract` test checks this property with a seeded model. It also confirms that constructing a second model with the same seed produces identical logits.

A causal model must also avoid looking across independent sequences batched together. The Transformer attention operator from Batch 03 enforces this boundary through an explicit sequence length.

## Review and extension exercises

1. Trace the parameter ID `UMI_DECODER_POSITION_EMBEDDING` from its shape to its gradient updates. Why is the same position row used in multiple batched sequences?
2. Explain why logits cannot be interpreted directly as probabilities.
3. Give the shapes of the token table, output matrix and logits if `B=2`, `T=2`, `V=4` and `C=8`.
4. Change the learner's seed and compare initial losses. Keep the dataset split seed unchanged. Which quantities are expected to change?
5. Explain why checking only the first parameter before SGD would be inadequate for a multi-tensor model.

**Evidence:** The supplied Batch 04 tests verify inference shapes, determinism, causal masking and training loss reduction. These tests do not prove usable English generation or specialist coding ability. Continue with [Lesson 14 — Held-Out Evaluation](14-held-out-evaluation-and-training-discipline.md).
