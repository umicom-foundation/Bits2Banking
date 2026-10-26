# Why earlier K/V rows should remain stable as a causal prefix grows

**Sammy Hegab · Umicom Foundation**  
**Format:** Educational video script with tensor diagrams and classroom exercises.

## Learning objectives

Distinguish past and future positions in causal attention; show how a model can verify every previously stored key/value component; and explain why this does not itself improve inference throughput.

## Narration: the promise of causality

A causal language model predicts future tokens from earlier ones. At a given position, the attention mask prevents the model from looking forward. Imagine a short prompt containing two tokens at positions zero and one. We append a third token at position two. The new token can look backwards; the first two cannot look forward to it. Therefore their canonical hidden states and projection rows should not change, provided their positions and model weights stay the same.

This principle applies at every Transformer layer. It is an important reason that prefix growth can potentially reuse work. But engineering cannot stop at a principle. The Umicom native capture checks the numerical values directly before accepting a new K/V row.

## Screen demonstration

Display a table containing two layers, a four-token maximum context and the first two valid tokens. The initial capture stores four token-layer rows. Append a third token and re-run the full canonical decoder. Compare the earlier key and value vectors element by element with the stored ones. Only if all comparisons pass may the cache owner append the third token's two new layer rows.

**Important:** The fresh diagnostic run still computed eight token-layer rows, because it evaluated four context positions across two layers. Only two K/V rows were newly admitted to storage. Display these figures in different columns to avoid treating storage work as compute savings.

## Numerical calculation

Use old key `[0.10,0.50]` and reference key `[0.10001,0.49998]`. Absolute differences are 0.00001 and 0.00002. Both fit a bound of 0.00004. Then show a deliberately incorrect value 0.50100, whose difference 0.00100 must fail.

The test should compare all previous rows, not merely the final key, and must reject NaN and infinite values. It should also refuse a wrong model checkpoint before reading the saved projections.

## Roll forward into the next topic

At full context capacity, a newly generated token forces the oldest token out. For the existing learned-absolute model, survivor positions change and the old keys are generally no longer mathematically valid. A full rebuild is mandatory. The next video shows why this rule is different from safe prefix growth.

## Exercise and answer

A three-layer model has two retained tokens; the context length is five. How many K/V token-layer rows are currently stored? **Six**, because `3 layers × 2 tokens = 6`. If one additional token is admitted, the store grows by three rows. The full canonical trace still evaluates `3×5=15` token-layer rows.

[Read Lesson 210](../../../lessons/10-native-ai/210-verify-existing-rows-before-appending.md).
