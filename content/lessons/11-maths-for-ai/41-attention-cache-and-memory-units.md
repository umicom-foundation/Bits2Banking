# Compute KV cache memory

**Mathematics for AI · Umicom Foundation**  
**Author:** Sammy Hegab

## A plain-English foundation

With L layers, S sequences, T tokens, C channels and b bytes per value, storing both keys and values requires L × S × T × C × 2 × b bytes.

## Worked example

For 2 layers, 1 stream, 4 tokens, 8 channels and 4-byte values: 2×1×4×8×2×4=512 bytes.

## Why this matters when learning C23

The program must check dimensions and capacity before allocating storage or calling the Framework's numerical services. A correctly calculated theoretical value does not mean a complete training system can run with that amount of memory. Shape checks, loss calculations and optimiser updates belong in Umicom Framework; the arithmetic shown here is educational.

## Try it yourself

What if there are three concurrent streams?

<details><summary>Show the solution</summary>

The estimate becomes 1,536 bytes.

</details>

For extra practice, review [mathematics foundations](index.md) and the [native LLM course](../10-native-ai/index.md).
