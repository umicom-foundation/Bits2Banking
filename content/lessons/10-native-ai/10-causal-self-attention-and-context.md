# Lesson 10 — Causal Self-Attention and Context-Sensitive Training

**Bits to Banking · Build Your Own LLM from Scratch**  
**Author:** Sammy Hegab · Umicom Foundation  
**Framework implementation:** `src/ai/training/tape.c`, `src/ai/training/sequence_shape.c`  
**Executable experiment:** `framework/learning/native-llm/train_attention.c`

## Learning objectives

The learner will explain why attention is required for context-sensitive predictions, calculate simple attention scores, understand a causal mask, trace gradients through queries/keys/values, and independently verify that a C23 training run reduces its objective on a tiny dataset.

**Prerequisites:** [Lesson 09](09-seeded-initialisation-and-token-embeddings.md) and the earlier tensor/backpropagation lessons.

## 1. Why an embedding alone cannot see earlier tokens

Consider these two training examples from our small educational vocabulary:

```text
framework learns  -> C23
calypso   learns  -> framework
```

The final input token is identical: **learns**. A context-free bigram model using only that token cannot always decide which successor is correct. To distinguish the sequences, the model must inspect what came **before** `learns`.

**Self-attention** provides a learned way for each token position to combine information from selected positions in its input sequence. It does not hard-code a rule saying that the first word determines the answer. Instead, it learns projection matrices whose dot products determine how strongly each available position contributes.

## 2. Queries, keys and values

Let the input embedding matrix be `X`, with one row per token. We derive three new matrices:

```text
Q = X * Wq    # queries
K = X * Wk    # keys
V = X * Wv    # values
```

For a query at position `i` and a key at position `j`, the raw compatibility score is:

`score(i,j) = dot(Q[i], K[j]) / sqrt(dk)`

where `dk` is the query/key vector width. Dividing by `sqrt(dk)` helps keep the scale of dot products manageable as that width grows.

Softmax turns allowed scores into attention weights:

`p(i,j) = exp(score(i,j) - maximumAllowedScore) / sum(exp(score(i,k) - maximumAllowedScore))`.

Subtracting the maximum before exponentiation avoids overflow from very large positive scores. The output at position `i` is the weighted sum:

`Y[i] = sum(p(i,j) * V[j])`, over permitted `j`.

These formulas are implemented by `UmiAiTrainingCausalAttention`, rather than supplied by an external language model.

## 3. The causal mask is a correctness property

A decoder predicts future tokens from earlier context. While training, it must not be allowed to read the answer from future input positions. A **causal mask** permits position `i` to inspect positions `0` to `i`, but not positions greater than `i`.

For three tokens, the permitted positions are:

```text
                 KEY POSITION
               t0     t1     t2
Query t0       YES     NO     NO
Query t1       YES    YES     NO
Query t2       YES    YES    YES
```

Our operator enforces this structurally by iterating only over permitted keys. Future positions are never given a probability, so they also receive no future-looking gradient through that earlier query.

For batched data, each independent sequence must have its **own** causal boundary. If the tape stores six flattened token rows containing two three-token sequences, the first sequence may only attend to rows `0..2`; the second may only attend to rows `3..5`. They must never attend across the batch boundary.

## 4. From rank three to the existing training tape

A realistic collection of sequences is logically shaped:

`[batch, time, channels]`.

Batch 01's training tape intentionally stores bounded 2D matrices. Instead of replacing that established ABI, this batch introduces `UmiAiTrainingSequenceShape`, which validates a rank-three logical layout and maps it to a two-dimensional allocation:

`[batch * time, channels]`.

For `batch=2`, `time=3`, `channels=4`, the tape receives a matrix of six rows and four columns. `UmiAiTrainingSequenceOffset` calculates checked element offsets in the original logical layout. The caller passes `time=3` as `sequenceLength` to attention; that parameter prevents mixing the two sequences.

This approach is appropriate for a first native single-head attention operator. It is **not yet a general rank-N tensor engine**.

## 5. A numerical attention example

Suppose there are two positions, with query/key width `2`, and the later position's two allowed scaled dot-product scores are:

```text
Earlier key:  score = 0
Current key:  score = ln(3)
```

The softmax probabilities are then:

```text
pEarlier = exp(0) / (exp(0) + exp(ln(3))) = 1/4
pCurrent = exp(ln(3)) / (exp(0) + exp(ln(3))) = 3/4
```

If the corresponding scalar value components are `2` and `10`, the output is:

`(1/4) * 2 + (3/4) * 10 = 8`.

The test `test_training_attention.c` checks this weighted sum and proves that altering a later token does not change an earlier output. It also checks that one batch cannot read the values of another.

## 6. Backpropagation through attention

The attention output depends on **Q**, **K** and **V**, so the loss must provide gradients for all three. This is more complex than differentiating a simple matrix product because the softmax weights depend on the input projections.

If `gY` is the output gradient, then the value-vector contribution is `p(i,j) * gY[i]`. For the score derivative, first calculate:

`dp(i,j) = dot(gY[i], V[j])`.

The softmax derivative is:

`ds(i,j) = p(i,j) * (dp(i,j) - sum(p(i,k) * dp(i,k)))`.

Finally, propagate the score derivative to the queries and keys using the scaled dot-product rule. Contributions to a shared key or value row must **accumulate** across every query that attends to it.

The separate test `test_training_attention_gradients.c` checks all Q, K and V derivatives against **central finite differences**. This catches errors that could otherwise make training loss appear to decrease for the wrong reasons.

## 7. Run the complete C23 training experiment

The new example uses five trainable parameter matrices: embedding table, query projection, key projection, value projection and output projection. All are initialised from a fixed seed. Every forward pass invokes the existing tape's embedding, matrix multiplication, causal attention and cross-entropy operations.

The backward pass updates all five matrices with the existing Framework SGD operator. Derived nodes are then rewound so the training tape remains bounded.

After merging Batch 02, open PowerShell:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path

cmake -S '.\framework\learning\native-llm' `
    -B '.\build\windows-ucrt64-native-llm-debug' `
    -G Ninja -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build '.\build\windows-ucrt64-native-llm-debug' --parallel 2
ctest --test-dir '.\build\windows-ucrt64-native-llm-debug' --output-on-failure
& '.\build\windows-ucrt64-native-llm-debug\umicom-native-llm-attention-demo.exe'
```

The reference GCC 14.2.0 CPU run on Linux (seed `20261020`, 1,100 epochs) produced:

```text
epoch    1: training cross-entropy 1.393962
epoch   50: training cross-entropy 0.756655
epoch  200: training cross-entropy 0.004241
epoch  500: training cross-entropy 0.000771
epoch 1100: training cross-entropy 0.000255
```

These figures are **reference training results**, not guaranteed bit-identical outputs on every CPU or compiler. The executable itself checks that the final training loss improves by at least 10% over its first observation. The independently verified Framework tests check masked behaviour, repeated token gradients and finite-difference derivatives.

## 8. What this result does and does not prove

The experiment demonstrates that neural parameters in an attention-containing graph can learn to fit a tiny context-sensitive corpus. It is a real gradient-based training run using the Framework's own implementation.

It does **not** demonstrate generalisation, long-context language understanding, a complete GPT model, positional encoding, multi-head attention, layer normalisation, residual connections, checkpoint recovery, or an expert in C23 or Calypso. A fully-fledged transformer remains a later milestone.

## Exercises and assessment

1. Why does the causal mask permit an earlier token but prohibit a later token?
2. For attention probabilities `0.2` and `0.8`, calculate the weighted sum of values `3` and `9`.
3. Why must an attention gradient from several queries be added to the same key row?
4. What is the distinction between a logical 3D tensor layout and the tape's physical 2D allocation?
5. Change the learning rate in the educational demo to `0.1F`. Compare the training loss at epochs 50, 200 and 1,100; restore the reference value afterwards.
6. What independent tests would be required before claiming the model generalises to unseen sentences?

**Next research milestone:** implement residual paths, normalisation, feed-forward sublayers and multiple attention heads, followed by controlled training/evaluation splits and checkpoint persistence. We will describe those features as working only after their corresponding native tests pass.
