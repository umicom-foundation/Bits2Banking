# Mathematics for AI — Unit 22: Low-rank residuals and frozen models

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Learning objectives

Understand a rank-limited matrix product, compute a low-rank residual step by step and explain why a trainable output adapter can change predictions while its original decoder weights remain frozen.

## 1. An ordinary matrix can be expensive to change

A dense matrix mapping **100 inputs to 100 outputs** contains `100 × 100 = 10,000` weights. Training all those weights requires gradients and often optimiser state for every element.

Instead of updating the original matrix, we can learn two smaller matrices:

- **D** has shape `[inputChannels, rank]`.
- **U** has shape `[rank, outputChannels]`.

The product **D × U** has the original `[inputChannels, outputChannels]` shape. For rank **4**, the two trainable matrices need `100×4 + 4×100 = 800` weights: **92% fewer than 10,000**.

This counts trainable weights only. It does not include temporary activations, gradients, checkpoint metadata or the still-retained frozen base model.

## 2. Worked example with two numbers

Let the input be row vector `x = [2, 1]`. Choose a rank-one down matrix:

```
D = [ 0.5 ]
    [−0.2 ]
```

The reduced value is `xD = 2×0.5 + 1×(−0.2) = 0.8`.

Let the up matrix be `U = [0.1, −0.3]`. The low-rank residual is:

`(xD)U = 0.8×[0.1, −0.3] = [0.08, −0.24]`.

Suppose the frozen base output is `[1.5, 0.5]`. Add the residual:

`adaptedOutput = [1.5, 0.5] + [0.08, −0.24] = [1.58, 0.26]`.

The base has not changed. Only the adapter controls how much is added.

## 3. What this means for a language-model head

A language model normally emits logits for each token position. In the new bounded teaching experiment, the existing Umicom decoder produces a matrix of frozen logits `Z` of shape `[tokenCount, vocabularySize]`. A separate adapter applies:

`Z_adapted = Z + (Z × D) × U`.

For vocabulary size **260**, adapter rank **4**, the trainable count is `260×4 + 4×260 = 2,080`. A dense 260×260 transformation would need **67,600** trainable weights. The residual adapter uses approximately **96.9% fewer weights** for this output transformation.

**This is not the same operation as inserting LoRA into each Transformer attention projection.** It is an experimental *logit-residual head*. The decoder remains an unchanged feature producer; the adapter learns only a correction to its output scores. Calling the two methods identical would confuse distinct model architectures.

## 4. Why the up matrix often begins at zero

At creation, the Framework can initialise **U = 0**. Then `(Z × D) × U = 0`, so the adapted output initially equals the original decoder output. After backpropagation and optimiser updates, the residual may become nonzero. This gives a useful test: before any training, compare the output of the original decoder with the adapter's output.

## 5. Exercise with answer

A frozen projection maps **32 input channels to 64 outputs**, using rank **8**. Calculate dense versus low-rank trainable weights.

**Answer:** a dense matrix has `32×64 = 2,048` elements. Down matrix `32×8 = 256`; up matrix `8×64 = 512`; combined **768**, a reduction of `2,048 − 768 = 1,280` or **62.5%**. The reduction is smaller than in a 100×100 example because the selected rank is proportionally larger.

**Takeaway:** parameter efficiency is a property of the matrix shapes. Model quality still requires measured held-out evaluation and correct lifetime rules.

[Mathematics index](index.md) · [Previous: token loss](21-cross-entropy-for-native-fine-tuning.md) · [Native adapter lesson](../10-native-ai/train-a-frozen-decoder-logit-adapter.md)
