# Why attention work grows quadratically

**Mathematics for AI · Umicom Foundation**  
**Author:** Sammy Hegab

## A plain-English foundation

Full attention compares each of T queries with up to T keys. Before causal masking, this is an area of T² score positions per head.

## Worked example

For T=32, a single head has 1,024 score positions. Doubling length to 64 yields 4,096—four times as many.

## Why this matters when learning C23

The program must check dimensions and capacity before allocating storage or calling the Framework's numerical services. A correctly calculated theoretical value does not mean a complete training system can run with that amount of memory. Shape checks, loss calculations and optimiser updates belong in Umicom Framework; the arithmetic shown here is educational.

## Try it yourself

How many score positions exist for four heads with T=16?

<details><summary>Show the solution</summary>

4 × 16 × 16 = 1,024.

</details>

For extra practice, review [mathematics foundations](index.md) and the [native LLM course](../10-native-ai/index.md).
