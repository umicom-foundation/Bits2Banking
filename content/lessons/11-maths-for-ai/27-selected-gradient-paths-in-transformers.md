# Mathematics for AI — Unit 27: Selected Gradients Through a Transformer

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Start with an ordinary numerical example

Imagine three predictions, but only the second and third are part of the
answer we want the model to learn. We mark the rows to supervise:

`lossMask = [0, 1, 1]`.

The zero means **ignore this row's direct prediction error**. It does not
remove that token from the Transformer's input context.

## 1. How do we average only the selected terms?

Suppose the negative log-likelihood of the correct target at the three
positions is `[0.9, 0.2, 0.4]`.

An ordinary three-row average would be:

`(0.9 + 0.2 + 0.4) / 3 = 0.5`.

For response-only learning, the first row is ignored:

`(0.2 + 0.4) / 2 = 0.3`.

The denominator **must be two**, because there are two supervised targets.
Dividing by all three would shrink the gradient unintentionally.

## 2. Why a selection matrix has useful gradients

The Framework's existing selected-loss service uses a fixed matrix to choose
rows from the original logits before calling its existing cross-entropy
operator. For three input rows and two selected rows, one suitable selector is:

```text
S = [0 1 0]
    [0 0 1]
```

If the original logits are `Z` with shape `[3, vocabulary]`, then
`S × Z` has shape `[2, vocabulary]`.

Backward propagates gradients through the same matrix multiplication.
Therefore the direct gradient of the loss with respect to the ignored first
logit row is zero. The two selected rows receive meaningful derivatives.

**Important distinction:** A prompt token can still influence the later
selected predictions **through causal attention**. An ignored prompt-position
logit does not imply that its input representation is irrelevant. This is why
we retain prompts in the input sequence while excluding their prediction
errors from the supervised objective.

## 3. How gradients reach a low-rank projection

Consider one Transformer dense operation with a low-rank residual:

`Y = XW + (XA)B`.

`X` is the input feature matrix. `W` is the frozen base. `A` and `B` are
trainable adapter matrices. Reverse-mode differentiation sends the selected
loss gradient backwards through the output logits, Transformer operations and
the two adapter multiplications. The optimiser updates `A` and `B`, not `W`.

At initialisation, `B = 0`, so the adapter output contributes no residual.
Its gradient need not be zero: it receives a derivative proportional to `XA`.
Meanwhile, the gradient for `A` through `(XA)B` is initially zero because
it contains `B`. After `B` begins changing, both factors may learn. This is
an expected consequence of the chain rule, not a training failure.

## 4. Try the calculation

A masked example has five rows with loss contributions
`[0.8, 0.6, 0.3, 0.2, 0.1]` and mask `[0, 0, 1, 1, 1]`.

The selected mean is `(0.3 + 0.2 + 0.1) / 3 = 0.2`.

If you changed the mask to `[1, 1, 1, 1, 1]`, the mean becomes
`(0.8 + 0.6 + 0.3 + 0.2 + 0.1) / 5 = 0.4`.

Those are **different objectives**, not different measurements of the same
objective.

## Engineering connection

Read [selected-token cross-entropy](../10-native-ai/selected-token-cross-entropy-in-c23.md)
and [Transformer projection response-only training](../10-native-ai/train-transformer-projections-with-response-only-loss.md).
The numerical implementation belongs to Umicom Framework; these examples
explain its existing C23 contracts rather than introducing new application
logic.
