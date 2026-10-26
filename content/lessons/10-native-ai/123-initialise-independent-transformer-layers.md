# Initialise independent Transformer layers reproducibly

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## One random seed, many independently owned weights

An educational Transformer should give repeatable experiments. The existing Framework provides `UmiAiTrainingRandomSeed` and `UmiAiTrainingRandomFillUniform`. The stacked constructor advances this *one caller-owned RNG state* as it creates every parameter tensor in a defined order. This makes two fresh models with the same configuration and seed produce the same initial logits on a qualifying build.

Every layer owns separate attention matrices, layer-normalisation scales/biases, and feed-forward matrices/biases. Normalisation scales begin at 1; ordinary biases begin at 0; dense projections and embedding tables receive seeded finite initial values. These are transparent laboratory initialisation rules, not a claim that this scheme is optimal for billion-parameter training.

## Why independent weights matter

If all six layers accidentally referenced one set of weights, the resulting system would repeatedly apply the same transformation rather than a stack of independently parameterised blocks. In some model families intentional sharing is possible, but that is a different architecture and must be declared, trained and checkpointed explicitly.

The constructor uses the tape's `UmiAiTrainingTensorCreate` for every leaf, so ownership is clear. On an allocation or validation failure, it destroys the partially constructed tape and leaves the caller's model pointer unchanged.

## Check it yourself

Create two models with identical settings, call `UmiAiTrainingStackedDecoderLogits` on the same full context, and compare all logits. Then create a model with a different seed or layer count and compare again. Changing a seed should change initialisation; changing layer count changes the architecture, so numeric parity is not expected.

## Practice

Why is reproducing the same seed insufficient for exact continuation after 100 SGD updates?

<details><summary>Worked answer</summary>

The seed recreates *initial* weights only. Training changes the weight values; continuation needs the actual updated parameters, training-step identity and the original sequence of data/update choices. For AdamW, moments are also necessary. A seed is not a replacement for a checkpoint.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
