# How a native Transformer reuses keys and values

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Format:** Educational narration and visual storyboard; not a completed recording.

## Opening narration

Welcome to our native C23 language-model course. This episode develops one idea carefully and checks it using ordinary numerical examples. All neural execution, model ownership and checkpoint logic belong to Umicom Framework.

## Main narration

Introduce token positions and Q/K/V. Show a table with three stored rows. Demonstrate that the fourth token needs its new query plus earlier keys and values, not earlier queries. Pause on why a causal mask makes this possible. Include the formula dot(query,key)/sqrt(head width).

## Visual storyboard

Animate a 1×8 query row against three stored 1×8 keys, then a fourth newly computed key. Label all vectors by layer and absolute position. Show all four values entering the Framework-owned attention operator.

## Guided classroom exercise

Ask learners to calculate the 3×2×8 K/V raw-value count for a three-layer, two-token prompt with eight channels, then convert to bytes. Answer: 96 floats, 384 bytes.

## Responsible closing

The example is designed for understanding, not for establishing performance or model quality in financial applications. Real acceptance needs the canonical decoder, relevant regression tests, fixed sampling policies and honest hardware measurements. Continue with the [LLM browser route](../../../courses/llm-from-scratch/incremental-attention-learning-path.html) and its [mathematics companion](../../../courses/maths-for-ai/incremental-attention-mathematics.html).

*Service to Many Leads to Greatness.*
