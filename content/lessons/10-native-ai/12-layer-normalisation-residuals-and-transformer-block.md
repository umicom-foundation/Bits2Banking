# Lesson 12 — Layer Normalisation, Residual Paths and a Complete Transformer Block

**Bits to Banking · Build Your Own LLM from Scratch**  
**Author and project originator:** Sammy Hegab · Umicom Foundation  
**Primary language:** C23 (CPU teaching backend)  
**Implementation:** `framework/src/ai/training/transformer.c`, `transformer.h`, `tape.c`  
**Working experiment:** `framework/learning/native-llm/train_transformer.c`

## 1. What this lesson builds

Lesson 11 implemented multi-head attention. A single attention operation is useful, but it is not yet a transformer block. A **decoder Transformer Block** combines attention with a feed-forward network, layer normalisation and residual connections. The result is a component we can eventually repeat several times to build a decoder-only language model.

Our goal is to implement and train **one block** using the already established Umicom Framework tensor tape. By the end, you should understand each mathematical step, find its native C23 implementation, check the shapes of all parameters, and verify that the complete forward and backward passes work. This is a real trainable neural component, but it is still **not** a complete LLM.

## 2. The block architecture

The current Umicom implementation uses **pre-layer-normalisation**. The input is normalised before each sublayer, while the residual connection bypasses the sublayer:

```text
                                input X
                                   |
                    +--------------+-------------+
                    |                            |
                 LayerNorm                      residual
                    |                            |
             Q/K/V projections                  |
                    |                            |
            Multi-Head Causal Attention         |
                    |                            |
             Output Projection                  |
                    |                            |
                    +--------------- ADD --------+
                                    |
                              residual state R1
                                    |
                    +---------------+-----------+
                    |                           |
                 LayerNorm                    residual
                    |                           |
             Dense Up + Bias                   |
                    |                           |
                   ReLU                         |
                    |                           |
             Dense Down + Bias                 |
                    |                           |
                    +-------------- ADD --------+
                                   |
                              output X'
```

Mathematically:

`N1 = LayerNorm(X)`

`A = Project( MultiHeadCausalAttention(N1*Wq, N1*Wk, N1*Wv), Wo )`

`R1 = X + A`

`N2 = LayerNorm(R1)`

`FF = ReLU(N2*Wup + bup) * Wdown + bdown`

`X' = R1 + FF`

The two residual paths allow each sublayer to learn a correction to its input rather than always needing to reconstruct the complete representation. This is an important optimisation property of deep networks.

## 3. Layer normalisation from first principles

Layer normalisation works **within one token's channel vector**. It does not use other samples in the batch when computing the mean and variance. For an input row `x` with `D` channels:

`mean = sum(x_i) / D`

`variance = sum((x_i - mean)^2) / D`

`normalised_i = (x_i - mean) / sqrt(variance + epsilon)`

`output_i = gamma_i * normalised_i + beta_i`

Here `gamma` and `beta` are trainable channel-wise parameters. Epsilon is a small, positive number which prevents division by zero when every input channel has the same value.

**Worked example:** for `x = [1,2,3,4]`, mean is `2.5`, and population variance is `1.25`. With a sufficiently small epsilon, the normalised vector is approximately:

`[-1.3416, -0.4472, 0.4472, 1.3416]`.

If gamma is `[1,1,1,1]` and beta is `[0,0,0,0]`, the output is simply the normalised vector. During training, gamma and beta can learn to rescale and shift those channels.

### Differentiating layer normalisation

It is not enough to calculate a forward result. Training requires gradients with respect to the input, gamma and beta. Let `dy` represent the gradient arriving from the subsequent operator; define:

`xhat = (x - mean) * inverseStd`

`dxhat = dy * gamma`

For one row with `D` channels, the input derivative is:

`dx = inverseStd / D * (D*dxhat - sum(dxhat) - xhat*sum(dxhat*xhat))`.

The affine parameter gradients are `dgamma += dy*xhat` and `dbeta += dy`. They **accumulate across all token rows** because gamma and beta are reused by every token in the batch.

In `src/ai/training/tape.c`, `UmiAiTrainingLayerNorm` implements the forward pass. The `UMI_AI_TRAINING_LAYER_NORM` case inside `BackwardNode` applies the derivative. The tests compare both passes against independently computed values rather than merely checking that training loss goes down.

## 4. The feed-forward sublayer

Attention decides which existing token information should be combined. A feed-forward network then transforms the resulting representation **independently for each token row**.

Our educational block uses two learned dense matrices. The first expands from `channels` to `hiddenChannels`; the second reduces back to `channels`. The activation function is **ReLU**, because its forward rule and derivative are easy to inspect. Larger modern models often use different activations, including GELU or gated variants; those are later extensions, not currently claimed functionality.

For `channels=4` and `hiddenChannels=6`, the matrix shapes are:

| Quantity | Shape | Meaning |
|---|---|---|
| `N2` | `[batch*time, 4]` | Normalised residual state |
| `Wup` | `[4, 6]` | Expansion projection |
| `bup` | `[1, 6]` | Broadcast bias |
| `ReLU(N2*Wup + bup)` | `[batch*time, 6]` | Activated hidden state |
| `Wdown` | `[6, 4]` | Reduction projection |
| `bdown` | `[1, 4]` | Broadcast output bias |
| `FF` | `[batch*time, 4]` | Shape compatible with residual |

The Framework's existing `UmiAiTrainingMatmul`, `UmiAiTrainingAdd` and `UmiAiTrainingRelu` are the authoritative maths. `transformer.c` **composes** those operators; it does not reimplement matrix multiplication, bias broadcasting or ReLU.

## 5. Read the actual Framework implementation

Open `C:\umicom\Umicom-Applications\framework\include\umicom\ai\training\transformer.h`. The public configuration is:

```c
typedef struct UmiAiTrainingTransformerBlockConfig {
    size_t sequenceLength;
    size_t attentionHeads;
    float normEpsilon;
} UmiAiTrainingTransformerBlockConfig;
```

Its partner parameter struct contains two layer-normalisation scale/bias pairs, four attention projection matrices, and four feed-forward tensors (two matrices and two biases). All parameters are **borrowed opaque tape handles**. The Framework tape owns their storage and lifetime.

A caller first creates all required parameter tensors through `UmiAiTrainingTensorCreate`, then prepares the block parameters and executes:

```c
UmiAiTrainingTransformerBlockConfig config = {
    .sequenceLength = 2U,
    .attentionHeads = 2U,
    .normEpsilon = 0.0001F
};

UmiAiTrainingTensor *output = NULL;
UmiStatus status = UmiAiTrainingTransformerBlockForward(
    tape, input, &blockParameters, &config, &output);
```

This fragment assumes that `tape`, `input` and the twelve tensor pointers inside `blockParameters` have already been created. For a complete source example, open `learning/native-llm/train_transformer.c` alongside this lesson.

The block validates input and parameter shapes, captures the current tape node count, performs its steps in order, and publishes its output only if all operations succeed. Failure triggers `UmiAiTrainingTapeRollback`, which discards the newly created graph suffix while preserving the earlier tensor nodes. Their **values** remain unchanged, while any previously calculated gradients are invalidated so stale derivatives cannot accidentally be applied.

This transaction boundary is a practical application of Umicom Framework's ownership and failure-containment principles.

## 6. A full learning experiment

The native demonstration trains token embeddings, two attention heads, two layer normalisations, an expanding feed-forward network, two residual paths and a final vocabulary projection. It learns from a deliberately tiny corpus:

```text
framework learns  -> C23
calypso   learns  -> framework
```

The second token is identical in both sequences, so the same last-token embedding cannot by itself explain both targets. Attention provides a way to use earlier context. The experiment uses seeded parameter initialisation, cross-entropy loss and the existing tape's SGD update.

An example run from the prepared Batch 03 Linux validation produced:

```text
epoch    1: training cross-entropy 1.415803
epoch   50: training cross-entropy 0.079500
epoch  200: training cross-entropy 0.001164
epoch  500: training cross-entropy 0.000284
epoch 1200: training cross-entropy 0.000089
```

This demonstrates successful optimisation on the **same examples used for training**. It is not evidence of generalisation or a claim that the model can explain Umicom Framework source code. The course will introduce held-out evaluation, checkpoint persistence and actual token generation in later lessons.

## 7. Build and verify the implementation

Open PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
      -B ".\build\windows-ucrt64-native-llm-debug" `
      -G Ninja -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" --output-on-failure

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-transformer-demo.exe"
```

The CTest catalogue includes tests for multi-head masking, per-head gradients, layer-normalisation forward outputs, finite-difference gradients, residual identity, complete-block parameter derivatives, actual training progress and failure-atomic rollback.

Pay particular attention to **two tests**. `test_training_transformer_gradients.c` compares the gradients from the *entire composed block* with central finite differences and verifies that changing a future token cannot change the output of an earlier token. `test_training_block_failures.c` checks rejected input, foreign tape handles, output-pointer preservation and safe rollback of partial graph construction.

A test passing does not make a future larger model correct; it gives us a sound, measurable foundation for the next changes.

## 8. What we have built, and what remains

We have a genuine native **trainable Transformer Block**, not a general-purpose model. It contains two-head causal attention, projections, trainable per-row layer normalisation, an expanding ReLU feed-forward network and residual paths. It is tested independently and incorporated into a small learning demonstration.

Still missing: a complete decoder model with positional information, multiple stacked blocks, a production tokenizer and corpus pipeline, checkpoint persistence, evaluation on held-out data, sampling/inference API and performance improvements for larger model sizes. Our current tape also deliberately caps tensors at 4,096 elements and the complete graph at 256 nodes.

**Review questions:** What is the difference between pre-LN and post-LN? Why do residual paths require identical tensor shapes? Why do layer-normalisation beta/gamma gradients sum across rows? Why do we test Q/K/V derivatives numerically? What would happen if two sequences were allowed to share an attention mask?

**Practical extension:** Run the demo twice and compare losses for reproducibility. Then change only the seed in a local copy, rebuild and record whether training still converges. Finally, reduce the learning rate and explain the change in training speed. Do not commit arbitrary parameter changes as a replacement for measured engineering evidence.

Continue to **Lesson 13 — Transformer Logits, Loss and Backpropagation**, where we will make the complete decoder training flow explicit and prepare for a proper dataset pipeline.
