# Mathematics for AI — Unit 30: Accuracy and Perplexity Are Different

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Think about two candidates

A language model assigns a numerical score (a logit) to each possible next token. The token with the largest score is the **top-1 prediction**. The model also assigns a probability to each token after applying softmax, so it can express confidence even when the predicted token does not change.

Suppose there are two candidate tokens with logits `2` and `1`. Their unnormalised exponentials are approximately `e² = 7.389` and `e¹ = 2.718`. Their total is about `10.107`.

The first token's probability is `7.389 / 10.107 ≈ 0.731`. The second receives about `0.269`. The model predicts the first token because `2 > 1`.

## Cross-entropy measures the target probability

If the first token is the correct target, its negative log-likelihood is:

`L = -ln(0.731) ≈ 0.313`.

If the second token were correct, the loss would be `-ln(0.269) ≈ 1.313`. The same logits would then have **top-1 accuracy zero for this token**, because the highest-scoring token would be wrong.

`ln` is the natural logarithm; the minus sign makes negative logarithms of probabilities between zero and one into nonnegative losses.

## Perplexity re-expresses average cross-entropy

Perplexity uses the exponential of mean cross-entropy:

`PPL = exp(meanLoss)`.

If mean loss is `ln(2) ≈ 0.6931`, perplexity is about `2`. If mean loss is `ln(4) ≈ 1.3863`, perplexity is about `4`. **Lower is better for the same evaluation objective and dataset**, but a numerical score alone does not measure trustworthy reasoning or software safety.

Perplexity is not an independent extra signal if it is computed from the same loss. A reduction in perplexity tells us the mean cross-entropy decreased; it does not prove more correct answers on practical financial tasks.

## Work through top-1 accuracy

Suppose five held-out supervised targets have predictions:

| Expected | Predicted | Match? |
|---|---|---|
| A | A | Yes |
| B | C | No |
| A | A | Yes |
| C | B | No |
| D | D | Yes |

Three of five are correct: `3/5 = 0.6 = 60%`.

An improved model might increase the expected-token probabilities but leave these exact top predictions unchanged. Its cross-entropy would improve while top-1 accuracy remained 60%.

## Questions

1. Accuracy improves from `3/5` to `4/5`. What is the new percentage? **80%.**
2. If `L=0`, what is perplexity? **One.**
3. Can an invalid floating-point logit participate in a trustworthy comparison? **No; reject non-finite scores.**
4. Does perplexity measure response legality or model safety? **No.**

Continue with [Unit 29](29-token-weighted-loss.md) and [held-out evaluation](../10-native-ai/measure-held-out-token-loss-and-accuracy.md).
