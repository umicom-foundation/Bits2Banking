# Unit 61 — Hash ordered tokens independently of the CPU word size

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Begin with familiar quantities

This is a self-contained numerical lesson for new contributors to Umicom Framework. A symbol is explained as it appears; the example contains artificial values rather than banking customer data. Native C23 code must preserve the stated formula, shape, memory ownership and numerical acceptance conditions.

## A worked mathematical explanation

A prompt is an ordered sequence of token IDs. To hash it portably, the encoder must choose one explicit byte representation; directly hashing native `size_t` memory is unsafe because that type can be four or eight bytes and may use different byte orders. In the Umicom evidence service, each token ID is represented by an unsigned 64-bit little-endian value, preceded by a fixed domain string and encoded token count. Token sequences `[1,2]` and `[2,1]` then have different ordered byte streams even though they contain the same IDs. SHA-256 helps detect changes to the represented bytes, but anyone can compute a new unkeyed digest, so it is not an authenticated release signature.

## Move from numbers to C23

When implementing a mathematical rule, first identify the input types and units, then compute a small result independently. Only after that should you compare it against a Framework API. Floating-point agreement uses a justified tolerance; token IDs, array capacities and SHA-256 byte representations require exact checking.

The associated native implementation is in `framework/src/ai/training/` and its public declarations are in `framework/include/umicom/ai/training/`. In particular, the stacked inference, evaluation and model-selection APIs reuse the existing Transformer, training tape, optimiser and tokeniser rather than duplicating those calculations in Bits2Banking.

## Practice

**Question:** How many data bytes are used to encode six token IDs as unsigned 64-bit values, excluding the count and domain label?

<details>
<summary>Show the worked result</summary>

Six IDs × eight bytes per ID gives 48 bytes. The full hash input additionally includes its count and domain prefix.

</details>

Continue with the [mathematics learning path for stacked inference](stacked-inference-mathematics.md), or return to the [native AI inference course](../10-native-ai/stacked-inference-learning-path.md). All examples are educational and do not represent live trades, payments or investment advice.
