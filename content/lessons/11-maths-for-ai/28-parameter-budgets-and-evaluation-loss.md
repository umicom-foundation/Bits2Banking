# Mathematics for AI — Unit 28: Parameter Budgets and Evaluation Loss

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## A clear reason to use low-rank adapters

Large dense matrices contain many weights. Training all of them requires
storage for parameters, gradients and, for optimisers such as AdamW, additional
moment values. A low-rank adapter reduces the **trainable subset**, while the
original matrix can remain frozen.

## 1. Count the original matrix

Suppose a Transformer projection has eight input channels and eight output
channels. It contains:

`8 × 8 = 64` base weights.

Its full matrix still must be stored for inference; freezing does **not** make
those 64 values disappear.

## 2. Count the adapter

With rank `r = 2`, the adapter contains two matrices:

- Down projection: `8 × 2 = 16` values.
- Up projection: `2 × 8 = 16` values.

The trainable adapter therefore contains `16 + 16 = 32` values, or
`r × (inputChannels + outputChannels)`.

Relative to training the entire dense matrix, the adapter trains half as many
parameters in this **particular** small example. Not every chosen rank saves
parameters; for an `8 × 8` matrix with rank four, the adapter also has
`4 × (8 + 8) = 64` values.

For four projections—Query, Key, attention output and feed-forward reduction—
with channel width eight, hidden width sixteen and rank two, the totals are:

`32 + 32 + 32 + 48 = 144 trainable values`.

These values are **additional to** the frozen base weights. Memory use also
includes the training tape, activations, gradients, caches and allocation
overhead. A parameter count is not process-resident memory (RSS).

## 3. The meaning of held-out loss

A held-out evaluation set is a collection of approved examples whose targets
were not used to update the adapter. Its purpose is to test whether a learned
change generalises beyond the training examples.

For next-token language modelling, cross-entropy is the average negative log
probability of the correct selected token. A lower value usually means the
model assigns higher probability to the held-out correct targets, **under the
same evaluation protocol**.

Suppose an example has target probabilities `0.5` and `0.25`. Its mean loss is:

`L = (−ln(0.5) − ln(0.25)) / 2`

`≈ (0.693147 + 1.386294) / 2 ≈ 1.039721`.

If another candidate was evaluated on different targets, the two numerical
losses would not be a fair direct comparison.

## 4. The source-level split matters

If an original video appears in training and its transcript appears in
validation, the same knowledge may leak across partitions. Hashing or tagging
only the derived filenames is insufficient; the original source identity must
be retained by the review service. Near-duplicate content also needs human or
independently qualified automated review.

## Worked exercises

1. **An original `16 × 8` projection uses rank two. How many adapter values?**
   `2 × (16 + 8) = 48`.
2. **An `8 × 8` projection uses rank one. How many additional trainable values?**
   `1 × (8 + 8) = 16`.
3. **If the training loss falls but the held-out loss increases, what might be
   happening?** The adapter may be overfitting. Check source separation and
   the evaluation protocol before drawing conclusions.
4. **Does a lower held-out loss prove financial-answer accuracy?** No. It
   measures the selected predictive objective on the declared data, not the
   truth of every generated response.

Continue with [evaluation and provenance](../10-native-ai/evaluate-frozen-decoder-and-adapters.md)
or [Mathematics Unit 27](27-selected-gradient-paths-in-transformers.md).
