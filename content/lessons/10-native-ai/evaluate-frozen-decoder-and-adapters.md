# Evaluate Frozen Decoder Adapters Against Held-Out Examples

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Purpose

A supervised run is not complete when the training loss falls. We need an
independent assessment of the model's predictions on examples it did not use
for parameter updates. This chapter explains what evidence Umicom's native AI
experiments must retain before an adapter can be considered for an application.

## 1. Preserve the three identities

A trustworthy comparison distinguishes the **frozen base decoder**, the
**trainable adapter** and the **evaluation dataset**.

The base decoder is identified by its actual canonical checkpoint bytes and
SHA-256. The adapter has its selected projection roles, rank, initial seed,
training step count and learned low-rank matrices. The dataset must have
source-level provenance, training-use approval and a train/evaluation split.

A matching model shape is not enough to identify a decoder; two models can
have the same dimensions but different weights. A matching data filename is
not enough to prove identical contents. In the Framework, independent SHA-256
checks and reviewed-source admission address those distinct risks.

## 2. Compare the same objective fairly

For a supervised response-only example, only mask-selected completion and EOS
targets contribute to the mean cross-entropy. Hold the byte-token vocabulary,
context length, token IDs and mask constant when comparing the frozen base with
an adapted model. Changing the test conditions invalidates the comparison.

A useful result table might contain:

| Evidence | Frozen model | Adapted model |
| --- | --- | --- |
| Base checkpoint identity | Same digest | Same digest |
| Selected adapter roles | None | Explicitly recorded |
| Target-token mask | Same | Same |
| Held-out mean cross-entropy | Measured value | Measured value |
| Source-level split | Unchanged | Unchanged |
| Wall-clock inference | Separate measured observation | Separate measured observation |

A lower held-out loss is meaningful for that **specific distribution and
objective**. It does not prove that the model provides correct financial
answers, safe code, unbiased recommendations or accurate citations.

## 3. Keep source groups together

Suppose a video and its caption transcript come from the same original
recording. Putting one into training and the other into evaluation leaks
source information. The Framework's reviewed-source services group records
by original-asset identity so exact derivatives share one partition.
Near-duplicates, paraphrases and overlapping edited excerpts still need
separate scrutiny. The audit alone cannot prove there is no leakage.

Synthetic classroom data is preferable for the first tests. Never put private
communications, credentials, customer records or unreleased documents into
public repositories or model-training corpora without explicit approval and
appropriate controls.

## 4. Check the learning curve honestly

Report training and held-out loss independently at known adapter step counts.
A gap between them may indicate overfitting. A small model can memorise a few
responses while performing poorly on even slight variations.

When training a logit-residual adapter, say so. When training low-rank
Transformer projections, say so. These are not interchangeable model
architectures, even when both use cross-entropy and AdamW or SGD.

Also record the toolchain, training seeds, context rules, precision and test
results. An incomplete or `Not Run` CTest cannot be claimed as a successful
qualification.

## 5. Practical exercise

Assume two held-out examples each contain two supervised target tokens.
Their **summed** negative log-likelihoods are `1.0` and `3.0`. The correct
weighted mean over all selected tokens is `(1.0 + 3.0) / 4 = 1.0`.

If the second example has eight selected tokens instead of two, averaging
per-example means without weighting by token count would not be the same as a
single mean over all selected tokens. Always state the denominator.

**Study next:** [projection-level response-only adaptation](train-transformer-projections-with-response-only-loss.md),
[Mathematics Unit 27](../11-maths-for-ai/27-selected-gradient-paths-in-transformers.md)
and [Mathematics Unit 28](../11-maths-for-ai/28-parameter-budgets-and-evaluation-loss.md).

**Key point:** A release-quality claim requires exact model identity,
approved held-out data, reproducible measurements and clear limitations.
