# Mathematics for AI — Unit 31: Shuffle Training Examples Without Repeating Them

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## What is a permutation?

A permutation changes the order of a group without adding or removing members. Imagine four fictional training examples labelled A, B, C and D. One valid permutation is `C, A, D, B`. Every example appears exactly once.

By contrast, drawing at random **with replacement** could produce `A, A, C, B`: example A appears twice and D is missing. Such a draw can be useful for some stochastic algorithms, but it does **not** satisfy a strict once-per-epoch traversal.

## Count the possible orders

Four distinct examples have:

`4! = 4 × 3 × 2 × 1 = 24` possible arrangements.

The exclamation mark in `4!` is pronounced “four factorial”; it means multiply positive integers from four down to one. Three distinct examples have `3! = 6` possible arrangements.

This count grows quickly. An application should not build a list of every possible permutation. It only needs one valid shuffled order at a time.

## Fisher–Yates in everyday language

Start with the list `[A, B, C, D]`. Choose one of the four remaining positions at random, swap it with the last position, then choose one of the first three positions and swap with the new last-unfixed position. Continue until every position is fixed.

Because each remaining position has an equal chance when the integer random selection is unbiased, the procedure produces a valid random permutation. Umicom uses the **existing Framework integer RNG**, not a second application-specific random-number algorithm.

A fixed seed and the same epoch index reproduce the same shuffle under the Framework's deterministic contract. Changing the epoch yields a different deterministically derived random state. That does not imply every pair of epoch orders must differ: two seeds can happen to produce the same permutation.

## Connect the mathematics to model training

Suppose the training subset contains four approved examples and the plan requests three complete epochs. The Framework attempts `4 × 3 = 12` adapter updates, each epoch visiting the four examples once.

Held-out evaluation examples do not appear in this training permutation. They remain separate because their job is to measure model behaviour on previously unseen approved targets.

The new native API is `UmiAiTrainingSupervisedDatasetOrder`. It returns **global dataset indexes** for one selected partition, checks the output buffer's capacity and leaves the caller's array untouched on error.

## Practice

1. How many permutations exist for three distinct examples? **Six.**
2. Five examples across four complete epochs means how many training updates? **Twenty**, assuming no failures or early stopping.
3. Is `[A, A, C, D]` a permutation of `[A, B, C, D]`? **No, B is missing and A repeats.**
4. Does a fixed seed prove a model improves? **No; it helps reproduce the order, not the quality.**

See [the deterministic-epoch lesson](../10-native-ai/train-with-deterministic-epochs.md).
