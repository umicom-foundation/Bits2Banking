# Mathematics for AI — Unit 110: Check layer-major address arithmetic

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with the idea

No specialist mathematics qualification is required. Each numerical symbol is tied to a concrete tensor, amount or test.

A flattened tensor is a one-dimensional buffer containing a multidimensional object. The address of a K/V scalar in `[layer][token][channel]` order is `((layer × context) + token) × channels + channel`. The same formula applies to values when values are stored in a separate contiguous array.

For `L=2`, `context=4`, `channels=6`, layer index 1, token index 2 and channel index 5, the scalar index is `(1×4+2)×6+5=41`. It is within the 48 float elements of each key/value array. Use checked integer multiplication before memory allocation; do not assume mathematical integers fit C `size_t`.

Changing a tensor's layout requires updating every producer, consumer and test. The correct count alone does not guarantee a correct flat offset.

## Your turn

**Exercise:** Compute the index for layer 2, token 1, channel 3 with context 5 and channels 4.

## Why this matters for a real native model

The Umicom Framework owns the actual model mathematics, K/V storage and numeric validation. The lesson calculates a small independent reference so a learner can recognise incorrect dimensions, wrong interpretation of results or numerical errors in a C23 regression. Nothing in this worked exercise claims that a production LLM has been trained or accelerated.

<details><summary>Reveal the calculation</summary>

`(2×5+1)×4+3=47`. Zero-based indexing puts that at the 48th float.

</details>

[Previous unit](109-separate-stored-from-executed-token-rows.md) · [Next unit](111-understand-memory-rollback-and-peak.md) · [Browser version](../../courses/maths-for-ai/lessons/110-check-layer-major-address-arithmetic.html) · [K/V mathematics reading path](projection-trace-mathematics.md).
