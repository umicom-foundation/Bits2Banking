# Working out optimiser storage

**Mathematics for AI · Umicom Foundation**  
**Author:** Sammy Hegab

## A plain-English foundation

Parameter values, gradients and optimiser moments are separate arrays. Multiplying the value count by each array element width estimates their raw storage.

## Worked example

For 100 parameters, FP32 values require 400 bytes, FP32 gradients 400 bytes, and two FP64 AdamW moments 1,600 bytes.

## Why this matters when learning C23

The program must check dimensions and capacity before allocating storage or calling the Framework's numerical services. A correctly calculated theoretical value does not mean a complete training system can run with that amount of memory. Shape checks, loss calculations and optimiser updates belong in Umicom Framework; the arithmetic shown here is educational.

## Try it yourself

What total do these arrays require?

<details><summary>Show the solution</summary>

400+400+1,600 = 2,400 bytes, excluding all other allocations.

</details>

For extra practice, review [mathematics foundations](index.md) and the [native LLM course](../10-native-ai/index.md).
