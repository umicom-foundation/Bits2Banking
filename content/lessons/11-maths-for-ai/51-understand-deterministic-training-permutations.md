# Understand deterministic training permutations

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Gentle mathematics for native AI

## Why changing example order can matter

An SGD trainer updates parameters after each example. The result of training on A then B can differ from training on B then A because B sees weights that have already changed after A. A reproducible experiment must therefore preserve not only its random seed, but the algorithm and iteration order derived from that seed.

A Fisher–Yates shuffle starts from an array such as `[0,1,2,3]`. It selects an index uniformly from the currently unshuffled prefix, swaps that value into the final available slot and repeats with one fewer slot. With an unbiased integer sampler, every permutation is equally likely under the ideal generator. The Umicom Framework supplies a deterministic native integer sampler; we do not create another RNG implementation.

## What an epoch means

An epoch visits every authorised training example once. The held-out examples are not included in this permutation. A model trained for three epochs over two training examples performs six example-level SGD updates. If the starting completed-step count is zero, the final count should be six after all operations succeed.

## Why a seed alone is insufficient to resume

For mid-epoch recovery we need the exact current epoch and next item position, as well as the shuffle seed, dataset identity and restored model weights. Recreating the same initial permutation but restarting it from the beginning would repeat examples and change the final model.

## Practice

There are seven training examples and three complete epochs. How many updates occur with one SGD step per example?

<details><summary>Worked answer</summary>

`7 × 3 = 21` updates. This assumes each example succeeds and no gradient accumulation groups several examples into one optimiser step.

</details>

---

[Mathematics reading path](stacked-transformer-mathematics.md) · [Native LLM course](../10-native-ai/stacked-transformer-learning-path.md)
