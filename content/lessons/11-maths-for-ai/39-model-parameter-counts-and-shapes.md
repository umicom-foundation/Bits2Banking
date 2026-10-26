# Counting neural network parameters

**Mathematics for AI · Umicom Foundation**  
**Author:** Sammy Hegab

## A plain-English foundation

For a row-major matrix of shape [m,n], the number of weights is m × n. Add n biases only if the layer includes them.

## Worked example

A 6 × 4 weight matrix has 24 weights. With four output biases it contains 28 trainable scalar values.

## Why this matters when learning C23

The program must check dimensions and capacity before allocating storage or calling the Framework's numerical services. A correctly calculated theoretical value does not mean a complete training system can run with that amount of memory. Shape checks, loss calculations and optimiser updates belong in Umicom Framework; the arithmetic shown here is educational.

## Try it yourself

How many parameters does an 8 × 3 dense layer with a 3-element bias have?

<details><summary>Show the solution</summary>

8 × 3 + 3 = 27.

</details>

For extra practice, review [mathematics foundations](index.md) and the [native LLM course](../10-native-ai/index.md).
