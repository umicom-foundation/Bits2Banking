# Unit 58 — Left-padding and token position indices

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Begin with familiar quantities

This is a self-contained numerical lesson for new contributors to Umicom Framework. A symbol is explained as it appears; the example contains artificial values rather than banking customer data. Native C23 code must preserve the stated formula, shape, memory ownership and numerical acceptance conditions.

## A worked mathematical explanation

With a fixed-length learned-position decoder, adding a beginning-of-sequence token on the left changes the positions assigned to real tokens. A five-slot context holding two real tokens has the layout `[BOS,BOS,BOS,A,B]`, placing A at index 3 and B at index 4. If one token is generated, the next full context becomes `[BOS,BOS,A,B,C]`; A now occupies index 2. Its positional embedding generally differs from the previous step. This is why a cache retaining earlier keys may no longer be mathematically valid when the context rolls. The numerical data type may be the same size, but the meaning of each position has changed. A model family using rotary positions would need separately qualified training and checkpoint rules.

## Move from numbers to C23

When implementing a mathematical rule, first identify the input types and units, then compute a small result independently. Only after that should you compare it against a Framework API. Floating-point agreement uses a justified tolerance; token IDs, array capacities and SHA-256 byte representations require exact checking.

The associated native implementation is in `framework/src/ai/training/` and its public declarations are in `framework/include/umicom/ai/training/`. In particular, the stacked inference, evaluation and model-selection APIs reuse the existing Transformer, training tape, optimiser and tokeniser rather than duplicating those calculations in Bits2Banking.

## Practice

**Question:** In a context of eight slots with five real prompt tokens, what is the first real token's position?

<details>
<summary>Show the worked result</summary>

Three BOS tokens precede it, so its zero-based position is 3.

</details>

Continue with the [mathematics learning path for stacked inference](stacked-inference-mathematics.md), or return to the [native AI inference course](../10-native-ai/stacked-inference-learning-path.md). All examples are educational and do not represent live trades, payments or investment advice.
