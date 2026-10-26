# Mathematics for AI — Unit 29: A Fair Average Across Answer Tokens

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Start with a practical question

Two synthetic questions have answers of different lengths. How do we calculate one honest average loss without giving a short answer and a long answer the same influence?

The number of supervised targets differs between the examples. A target is one token the model is asked to predict. A token may be a byte in Umicom's introductory byte vocabulary. Padding and prompt-only positions do not count if their loss mask is zero.

## Step 1 — Count each answer's targets

Suppose example A has **two** selected targets with mean cross-entropy **0.4**. Example B has **six** selected targets with mean cross-entropy **1.2**.

The unweighted average of the two reported means is:

`(0.4 + 1.2) / 2 = 0.8`.

That number is a valid **per-example average**, but it is not the overall *per-token mean* that the supervised objective asks for.

## Step 2 — Recover the token-weighted sums

Example A contributes `2 × 0.4 = 0.8` total loss units. Example B contributes `6 × 1.2 = 7.2`. Across both examples there are `2 + 6 = 8` selected tokens and `0.8 + 7.2 = 8.0` total loss units.

Therefore:

**Per-token mean loss** `= 8.0 / 8 = 1.0`.

The general rule is:

`weighted mean = Σ (tokenCountᵢ × meanLossᵢ) / Σ tokenCountᵢ`.

`Σ` means sum all items. `i` identifies an example. `tokenCountᵢ` is its number of supervised targets. `meanLossᵢ` is the example's average over those targets.

## Why the distinction matters

If a training report uses token-weighted loss but a held-out report uses an unweighted example average, it is easy to draw false conclusions. They do not measure the same objective. Umicom's `UmiAiTrainingSupervisedExperimentEvaluate` reports mean loss per selected held-out target. The experiment runner uses the same weighting for each epoch's **pre-update training-loss summary**.

These summaries still describe different data and time points. Training examples influence weights; held-out examples must not be used for SGD. Comparing them is useful only with this distinction explicit.

## Practice and answer

Example C has four selected targets with mean loss 0.5. Example D has one selected target with mean loss 1.5. Find the per-token mean.

**Solution:** total loss `4×0.5 + 1×1.5 = 3.5`; selected targets `4+1 = 5`; mean `3.5/5 = 0.7`. The unweighted average of 0.5 and 1.5 is 1.0, a different statistic.

Review [Unit 5](05-probability-softmax-and-loss.md), then [the held-out metrics lesson](../10-native-ai/measure-held-out-token-loss-and-accuracy.md).
