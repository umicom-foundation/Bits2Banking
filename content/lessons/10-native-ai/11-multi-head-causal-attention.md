# Lesson 11 — Multi-Head Causal Attention: Several Views of the Same Sequence

**Bits to Banking · Build Your Own LLM from Scratch**  
**Author and project originator:** Sammy Hegab · Umicom Foundation  
**Implementation language:** C23  
**Required source:** `framework/src/ai/training/tape.c` and `framework/include/umicom/ai/training/tape.h`  
**Native validation:** `framework/tests/ai_training/test_training_multihead.c` and `test_training_multihead_gradients.c`

## 1. What you will learn

By the end of this lesson, you should be able to explain why a transformer divides its attention channels into **heads**, calculate the attention scores for two independent heads, understand how the causal mask applies to each head, and trace the implementation and tests in Umicom Framework. You should also understand the difference between a multi-head *neural-network layer* and multiple specialised *models* cooperating inside an application. Those are different architectures.

**Prerequisites:** Lesson 09 (embeddings), Lesson 10 (single-head causal attention), the matrix and differentiation lessons. This chapter continues the *same* training tape, rather than starting an unrelated neural-network implementation.

## 2. A reason to use multiple heads

In Lesson 10, one attention mechanism analysed each token using one set of projected query, key and value vectors. A transformer may benefit from looking at several relationships at once. Consider the phrase:

> The Framework module calls the Data Server after validating the transaction.

One head might learn a relationship between *module* and *Framework*. Another might learn associations between *transaction* and *Data Server*. These are examples of the types of patterns a trained network could discover, not fixed rules encoded into the software. Real heads are learned numerical projections, and there is no guarantee that an individual head corresponds neatly to one human-interpretable concept.

We do not need a different model executable per head. In **multi-head attention**, the heads are parallel calculation paths *inside the same model*. Our eventual C Expert, Framework Expert and Calypso Expert are separate trained models coordinated at application level. They should not be confused with these neural-network attention heads.

## 3. From channels to heads

Suppose the hidden representation has **four channels**, and we choose **two attention heads**. Each head then receives a contiguous group of two channels:

```text
Input token representation: [c0, c1, c2, c3]
                               |     |   |     |
Head 0:                        [c0, c1]
Head 1:                                  [c2, c3]

Head 0 attention output:     [h00, h01]
Head 1 attention output:     [h10, h11]
Concatenated output:         [h00, h01, h10, h11]
```

This split is valid only when `channels % headCount == 0`. In our implementation, all query, key and value matrices have the same `[batch*time, channels]` dimensions. The head width is `channels / headCount`. Within each head, scaled dot-product attention uses the square root of the **head width**, not the full model width.

A production transformer commonly learns query, key and value projections with matrices that map from the full hidden width into the concatenated head space. Our Block implementation follows this pattern: it creates `Q=XWq`, `K=XWk`, `V=XWv` with full-width matrices, then divides their channels into heads during attention.

## 4. Calculate a small example

For one attention head with query `q`, key `k` and head width `d`, the compatibility score is:

`score = dot(q, k) / sqrt(d)`.

For **Head 0**, consider the query `[1, 0]` and two allowed keys `[1,0]` and `[0,1]`. Because `d=2`, the scores are approximately `[0.7071, 0]`. The stable softmax probabilities are approximately `[0.6698, 0.3302]`.

If the corresponding value vectors are `[2,0]` and `[0,2]`, this head returns approximately:

`0.6698*[2,0] + 0.3302*[0,2] = [1.3396, 0.6604]`.

**Head 1** processes its own two channels independently. For a query `[0,1]`, keys `[0,1]` and `[0,-1]`, its scores are `[0.7071,-0.7071]`. Its probabilities are approximately `[0.8044,0.1956]`. If values are `[0,4]` and `[4,0]`, the result is approximately `[0.7824,3.2176]`.

The four-channel concatenated output becomes approximately:

`[1.3396, 0.6604, 0.7824, 3.2176]`.

A subsequent output projection `Wo` lets the model combine information from different heads. This projection is applied by the complete Transformer Block in Lesson 12, not inside the attention operator itself.

## 5. The causal and batch boundaries remain mandatory

We are building a **decoder-only** language model. A token at time `t` may attend only to positions at or before `t`. It must not see the future token whose prediction is being learned. The mask must apply independently to every head.

Likewise, when several sequences are flattened into rows of a matrix, a query in one sequence must not read keys from another. The Framework operator computes the sequence start as `(row / sequenceLength) * sequenceLength` and visits only `past <= row % sequenceLength`.

For two batches of two tokens, the correct readable locations are:

| Query row | Sequence | Allowed key rows | Forbidden examples |
|---|---|---|---|
| 0 | First | 0 | 1, 2, 3 |
| 1 | First | 0, 1 | 2, 3 |
| 2 | Second | 2 | 0, 1, 3 |
| 3 | Second | 2, 3 | 0, 1 |

These are properties of the operator, not optional model prompts. A user cannot ask the model to bypass them.

## 6. Read the real native implementation

Open `C:\umicom\Umicom-Applications\framework\src\ai\training\tape.c` and find:

```c
UmiStatus UmiAiTrainingMultiHeadCausalAttention(
    UmiAiTrainingTape *tape,
    const UmiAiTrainingTensor *queries,
    const UmiAiTrainingTensor *keys,
    const UmiAiTrainingTensor *values,
    size_t sequenceLength,
    size_t headCount,
    UmiAiTrainingTensor **outTensor);
```

The function checks each opaque tensor belongs to the active tape, verifies the three matrix shapes, rejects invalid head counts, and checks multiplication bounds **before** allocating a temporary probability cache.

The cache stores a probability for each permitted key using logical indices `[head, row, past]`. Only the current and earlier positions are considered, so forbidden future tokens are not assigned probability values. Per-head weighted values are written into the correct output channel group.

For backward propagation, the tape implements the derivative of attention's softmax. The gradient through the values is weighted by attention probabilities; query and key gradients depend on how changing a score changes those probabilities. All three paths must accumulate because the same tensor may be used as query, key and value.

This is why we include a test with **aliased Q/K/V inputs**. If the implementation mistakenly overwrote one contribution with another, the analytical gradient would disagree with a numerical derivative.

## 7. Build, run and inspect

From PowerShell, after merging the batch into the correct local folders:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
      -B ".\build\windows-ucrt64-native-llm-debug" `
      -G Ninja -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
      --output-on-failure -R "framework.ai.training.multihead"
```

Read the outputs of `test_training_multihead.c`: its zero-query/zero-key test predicts a **uniform causal average**, so it is independent of a learned weight matrix or random seed. Then study `test_training_multihead_gradients.c`: it calculates central finite differences by slightly increasing and decreasing every selected parameter and comparing the resulting change in loss with reverse-mode backpropagation.

The numerical derivative is `(Loss(x+h) - Loss(x-h)) / (2*h)`. Floating-point arithmetic introduces error, so the test uses a stated tolerance rather than expecting exact binary equality.

## 8. Engineering limitations and questions

Our multi-head operator is intentionally bounded: up to 4,096 elements per tensor and up to 4,096 cached attention probabilities per operation. It runs on the CPU with scalar floating-point loops. Increasing sequence length makes the attention cache grow quadratically. A future implementation will need improved memory planning and optimised kernels before handling realistic contexts.

The code currently implements conventional multi-head attention; it does not yet provide rotary positional embeddings, KV caching, flash attention, arbitrary-dimensional tensor views or a production inference server.

**Review questions:** Why is the scaling factor based on head width? Why must the number of channels be divisible by head count? What happens if the causal mask is removed from the second head? What distinguishes a multi-head layer from three cooperating domain-expert language models?

**Practical extension:** Replace the two-head configuration with one head in a local, isolated test. Record which outputs remain the same and which do not. Do not change the Framework implementation just to make a poorly specified test pass.

Continue with **[Lesson 12 — Build a Complete Transformer Block](12-layer-normalisation-residuals-and-transformer-block.md)**.
