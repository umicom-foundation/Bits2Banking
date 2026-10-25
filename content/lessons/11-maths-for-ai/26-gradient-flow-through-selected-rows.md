# Mathematics for AI — Unit 26: Gradient Flow Through Selected Rows

**Umicom Foundation · Author: Sammy Hegab**  
**Prerequisites:** [Matrix multiplication](04-matrices-and-shapes.md), [chain rule](06-derivatives-and-chain-rule.md), [loss masks](25-loss-masks-and-next-token-alignment.md)

## 1. A matrix can select a row

Suppose the original logits table has three token positions and two vocabulary entries:

`X = [[1,0], [2,3], [4,5]]`, shape `3 × 2`.

We want to supervise only the second and third positions. Construct a **nontrainable** selection matrix:

`S = [[0,1,0], [0,0,1]]`, shape `2 × 3`.

Matrix multiplication gives:

`Y = SX = [[2,3], [4,5]]`, shape `2 × 2`.

The matrix does not change the values; it picks the selected rows. The first row of `X` was excluded. This is easy to inspect by hand and suits small teaching models.

## 2. What happens during backpropagation?

Suppose a scalar loss `L` depends on `Y`. The chain rule for `Y = SX` gives, in ordinary matrix notation:

`∂L/∂X = Sᵀ (∂L/∂Y)`.

`Sᵀ` means transpose: swap the rows and columns. If the gradient for the two selected rows is:

`G = [[0.1, -0.1], [0.2, -0.2]]`,

then:

`SᵀG = [[0,0], [0.1,-0.1], [0.2,-0.2]]`.

The ignored first row receives exactly zero gradient *through this loss selection*, while the selected rows receive their original gradients. This statement does not mean the first input token is absent from attention: earlier context can still influence selected predictions through the causal model.

## 3. Why a dense selector is not a production optimisation

If there are `T` sequence rows and `K` selected targets, the selector contains `K × T` float elements. For `T=8` and `K=3`, that is `3 × 8 = 24` elements, or 96 bytes for FP32 numbers before accounting for tensor metadata and gradients.

A production-scale Transformer often uses thousands of tokens. Constructing a dense selector would waste both time and memory. A later *fused* native tape operator could apply the same mathematically qualified selection directly without materialising a dense matrix. It must still prove the same forward loss and backward gradients independently before replacing this teaching composition.

## 4. Check the result numerically

An independent regression can compare the selected loss with a direct reference calculation using stable log-sum-exp and test that excluded logit rows have zero gradients.

For probabilities `0.8` and `0.5` at the selected target positions, the mean loss is about `0.4581`. Multiplying this by three (the total context rows) is not the correct loss; the mean is over *two supervised rows*.

## 5. Practice and answers

**Practice:** For `X` with shape `5 × 4` and three selected rows, what is the shape of the selector `S`? **Answer:** `3 × 5`. The selected result `SX` has shape `3 × 4`.

**Practice:** If only row `2` is selected from five input rows, how many rows of `X` receive zero direct gradient from the row-selector operation? **Answer:** four.

**Practice:** Does a zero *direct* gradient on a prompt-only logit row guarantee that an earlier prompt embedding has zero gradient? **Answer:** no. The prompt embedding can still affect supervised later predictions through causal attention.

## Where it lives in Umicom

The code belongs to `UmiAiTrainingSelectedCrossEntropy` in Umicom Framework and reuses its canonical `Matmul`, `CrossEntropy` and `Backward` operations. Continue with the [native exercise](../10-native-ai/selected-token-cross-entropy-in-c23.md).
