# Measure Held-Out Token Loss, Accuracy and Perplexity

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## What does evaluation actually measure?

A native language model outputs a vector of vocabulary logits at each token position. An evaluation compares those scores against the declared next-token target, but **only at the positions selected by the response loss mask**. Ignored prompt and padding targets must not inflate or dilute the result.

Umicom's new `UmiAiTrainingSupervisedExperimentEvaluate` reads held-out windows from the Framework-owned supervised dataset. For each window it calls the existing decoder projection adapter's cross-entropy evaluation and logits APIs. The new service coordinates weighted aggregation and selected-target top-1 comparison; it does **not** implement a competing softmax or attention kernel.

## Why naive averaging can be wrong

Suppose held-out example A has two selected targets and average loss 0.4. Example B has six selected targets and average loss 1.2.

The unweighted average of per-example losses is `(0.4 + 1.2) / 2 = 0.8`. But that treats a two-target answer as equally informative as a six-target answer.

The correct token-weighted loss for this selected-token objective is:

`(2 × 0.4 + 6 × 1.2) / (2 + 6) = (0.8 + 7.2) / 8 = 1.0`.

The denominator is the **total number of selected targets**, not total context positions and not number of documents. This makes the metric comparable across examples of unequal response length, assuming the evaluation dataset itself is comparable.

## Top-1 next-token accuracy

At one selected position, the model predicts the token with the greatest logit. If that token matches the reviewed target, the position counts as correct. Ties use the lowest vocabulary ID, matching the native argmax convention.

For eight supervised tokens, if three top predictions match, accuracy is `3 / 8 = 0.375 = 37.5%`.

Accuracy ignores how close the other logits were. Cross-entropy responds to the probability assigned to the correct token. A model can improve cross-entropy without changing the top-1 answer and vice versa.

## Perplexity is another view of the same loss

For mean cross-entropy `L` measured using natural logarithms, perplexity is `exp(L)`. If `L = ln(2) ≈ 0.6931`, then perplexity is about `2`. This is **not a new independent benchmark**: it is a monotonic transform of the same held-out next-token objective.

If `exp(L)` would overflow the floating-point representation, the Framework explicitly reports `perplexityAvailable = 0` rather than inventing a zero or infinite speed/quality claim.

## Read the C23 report

```c
UmiAiTrainingSupervisedEvaluation evidence = {0};
UmiStatus status = UmiAiTrainingSupervisedExperimentEvaluate(
    adapter, dataset, &evidence);
if (status == UMI_STATUS_OK && evidence.perplexityAvailable) {
    /* evidence.meanCrossEntropy and evidence.perplexity refer to the
     * exact same selected-target, held-out dataset snapshot. */
}
```

## Exercises

1. Two held-out examples contain three and seven selected targets. Why not divide summed token losses by two? **The metric is per target, not per example.**
2. Loss is 0.0 on a selected target. What would perplexity be? **`exp(0) = 1`.**
3. Does 60% top-1 accuracy imply safe advice in banking? **No; it measures selected-token predictions on a declared dataset only.**
4. Why refuse a non-finite logit? **A ranking or cross-entropy derived from NaN/Inf cannot provide trustworthy evidence.**

Study [Mathematics Unit 29](../11-maths-for-ai/29-token-weighted-loss.md) and [Unit 30](../11-maths-for-ai/30-accuracy-and-perplexity.md) for step-by-step calculations.
