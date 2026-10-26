# Mathematics for AI — Unit 107: Understand frozen checkpoint fingerprints

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with the idea

No specialist mathematics qualification is required. Each numerical symbol is tied to a concrete tensor, amount or test.

An SHA-256 digest has 256 bits, or 32 bytes. It is normally displayed as 64 hexadecimal digits because one hexadecimal digit encodes four bits. Hashing the portable bytes of a checkpoint detects a changed checkpoint, even if all model dimensions remain the same.

Do not confuse integrity with authenticity. A self-consistent checksum cannot establish who supplied the model; a separate trusted signature and approval process is required. Nor does a hash prove that a model has acceptable safety, fairness or accuracy.

For a 32-byte digest, the textual representation needs a 65-byte C array when a terminating zero byte is required: 64 printable characters plus one terminator.

## Your turn

**Exercise:** How many bits and hexadecimal characters represent a 32-byte SHA-256 digest?

## Why this matters for a real native model

The Umicom Framework owns the actual model mathematics, K/V storage and numeric validation. The lesson calculates a small independent reference so a learner can recognise incorrect dimensions, wrong interpretation of results or numerical errors in a C23 regression. Nothing in this worked exercise claims that a production LLM has been trained or accelerated.

<details><summary>Reveal the calculation</summary>

It contains `32×8=256` bits and is normally formatted as `256/4=64` hexadecimal digits.

</details>

[Previous unit](106-compare-multilayer-prefix-rows.md) · [Next unit](108-measure-error-without-claiming-speed.md) · [Browser version](../../courses/maths-for-ai/lessons/107-interpret-frozen-checkpoint-identities.html) · [K/V mathematics reading path](projection-trace-mathematics.md).
