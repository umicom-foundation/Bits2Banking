# The arithmetic of low-rank adapters

**Mathematics for AI · Umicom Foundation**  
**Author:** Sammy Hegab

## A plain-English foundation

A [m,n] dense matrix has mn values. Two rank-r factors of shapes [m,r] and [r,n] contain r(m+n) values.

## Worked example

With m=32, n=64 and r=4, the original has 2,048 weights and its two adapter factors have 4(32+64)=384 trainable weights.

## Why this matters when learning C23

The program must check dimensions and capacity before allocating storage or calling the Framework's numerical services. A correctly calculated theoretical value does not mean a complete training system can run with that amount of memory. Shape checks, loss calculations and optimiser updates belong in Umicom Framework; the arithmetic shown here is educational.

## Try it yourself

For m=16, n=32 and r=2, how many adapter weights exist?

<details><summary>Show the solution</summary>

2(16+32)=96.

</details>

For extra practice, review [mathematics foundations](index.md) and the [native LLM course](../10-native-ai/index.md).
