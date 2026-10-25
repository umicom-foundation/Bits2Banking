# Mathematics for AI — Unit 5: Probability, Softmax and Learning Loss

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Companion:** [Illustrated HTML lesson](../../courses/maths-for-ai/lessons/05-probability-softmax-and-loss.html)

## What you will learn

A language model assigns a score to each possible next token. This lesson explains why those scores are **not yet probabilities**, how softmax converts scores into a probability distribution, and how cross-entropy measures an incorrect prediction. You need only fractions, powers and division.

## From a score to a probability

Consider a vocabulary containing two possible next tokens. The model returns the **logits** `s = [1, 0]`. A logit is an unrestricted score: a negative score is allowed, and the scores do not need to add to one. Softmax converts the scores into probabilities:

\[
P(i) = \frac{e^{s_i}}{\sum_j e^{s_j}}.
\]

Here `i` identifies one token; `sᵢ` is its logit; `e` is the exponential base, about 2.71828; and `Σ` means add the exponential for every candidate. Work through the arithmetic:

1. `e¹ ≈ 2.71828` and `e⁰ = 1`.
2. Add the numbers: `2.71828 + 1 = 3.71828`.
3. Divide: `P(first) ≈ 2.71828 / 3.71828 ≈ 0.73106`.
4. Likewise, `P(second) ≈ 1 / 3.71828 ≈ 0.26894`.
5. Check the total: `0.73106 + 0.26894 = 1.00000`.

The model has not declared a fact to be true. It has distributed one unit of probability across its two candidate tokens.

### Why subtract the largest logit?

For a larger logit, `e^s` can overflow floating-point storage. Subtracting the maximum logit from **every** score preserves softmax probabilities:

`softmax([1001, 1000]) = softmax([1, 0])`.

The numerator and denominator are both multiplied by the same factor, which cancels. This is a common numerical-stability technique; the Umicom Framework's existing cross-entropy operator owns its implementation.

## From probability to training loss

The loss for the correct token is `L = −ln(P(correct))`. The natural logarithm `ln` converts multiplication into addition and is the inverse of the exponential. The minus sign makes the loss nonnegative when the probability is between zero and one.

If the correct token is the first one, `L ≈ −ln(0.73106) ≈ 0.3133`. If the model assigns the correct token only `0.1`, the loss becomes `−ln(0.1) ≈ 2.3026`: a worse prediction produces a larger penalty.

For a batch, we normally **average** per-token losses. Average cross-entropy is a training objective, not an independent measure of factual accuracy, usefulness or safety.

## Framework connection

The C23 training tape already exposes `UmiAiTrainingCrossEntropy`. Its inputs are a tensor of logits and an array of target token IDs; the operator handles numerical stability and automatic differentiation. Bits2Banking does not need a second softmax implementation.

## Practise and check

**Question A.** Both logits are zero. What probabilities result?  
**Answer.** `e⁰ = 1` for each; the denominator is two; each token receives `0.5`.

**Question B.** The correct-token probability is `0.25`. What is its loss?  
**Answer.** `−ln(0.25) ≈ 1.3863`.

**Question C.** Does a lower loss on the training set prove a model is better on unseen questions?  
**Answer.** No. Train and evaluation documents must be separate, and useful model qualities require independent tests.

**Next:** [Derivatives, gradients and the chain rule](06-derivatives-and-chain-rule.md).
