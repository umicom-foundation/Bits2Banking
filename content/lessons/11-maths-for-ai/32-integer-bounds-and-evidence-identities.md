# Mathematics for AI — Unit 32: Count Safely and Identify Experiments

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Why integer arithmetic belongs in an AI lesson

A training plan multiplies counts: number of examples × epochs, token rows × vocabulary width, and elements × bytes per value. If a program stores one of those products in a bounded unsigned integer, a result that is too large can wrap around. A wrapped allocation size could produce a buffer smaller than the calculation actually needs.

The solution is to validate **before multiplying**, not after the overflow has happened.

## One ordinary calculation

A fictional dataset contains 16 approved training examples, and a plan requests 8 complete epochs. The requested number of training calls is:

`16 × 8 = 128`.

The calculation is well inside the limits of our small educational laboratory. If a program were allowed arbitrary counts, it would need to check both values fit its integer type and that multiplication cannot overflow.

For positive unsigned integers `a` and `b`, a portable C23 check is:

```c
if (b != 0U && a > SIZE_MAX / b) {
    /* Reject the calculation: a*b cannot fit into size_t. */
}
```

`SIZE_MAX` is the largest value representable by `size_t`. The division produces an upper bound for `a` without computing the risky product first. Include `<stdint.h>` or a suitable standard header for `SIZE_MAX` in a complete program.

## Model identity is not just a step count

Suppose two experiments report 128 completed updates. They may still use different frozen models, training data, learning rates or random seeds. The integer 128 alone does not identify what happened.

Umicom binds a run report to two separate 256-bit digests:

- The **ordered corpus digest**, which changes when the reviewed examples, sequence order, source grouping or partition evidence changes.
- The **frozen decoder checkpoint digest**, which identifies the precise original model bytes.

A SHA-256 digest has 256 bits, normally shown as 64 hexadecimal characters. Hexadecimal uses digits `0–9` and letters `a–f`; each hexadecimal character represents four bits because `16 = 2⁴`.

The two identities are not interchangeable. A model may be unchanged while the dataset is corrected, or the dataset may be unchanged while the model weights differ.

## A run receipt and its limits

The Framework writes a fixed 208-byte, little-endian experimental receipt. Its trailing SHA-256 detects an unintentional byte change. This does **not** prove a trusted signer authored the record, and it does not save adapter weights or optimiser moments.

A valid unsigned receipt is metadata for review, not an automatic deployment approval or recovery checkpoint.

## Practice with worked answers

1. Three supervised tokens per example across four examples: how many selected targets? **12.**
2. Each value occupies four bytes. How much raw storage do 40 values require? **160 bytes**, excluding metadata.
3. How many hexadecimal characters display a 256-bit digest? **64**, because `256/4=64`.
4. The corpus hash changes but the model hash stays identical. Is it the same experiment? **No; the approved input changed.**
5. Does a CRC-like checksum establish who published a model? **No; authentication requires a separately trusted signature or provenance.**

Continue with [source/model receipt evidence](../10-native-ai/bind-run-receipts-to-source-and-model.md).
