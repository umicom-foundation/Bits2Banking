# Distributed Learning — Lesson 02: Understand gradients and immutable checkpoints

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Track:** Introduction to Distributed Learning and Verifiable AI

## Learning objective

Explain **understand gradients and immutable checkpoints** in plain English, perform a small worked calculation or thought experiment, and distinguish a research hypothesis from a demonstrated system behaviour.

## Understand the idea

A gradient indicates local sensitivity of the training loss to trainable model parameters. Optimisers convert gradients into updates. A checkpoint fixes model and often optimiser state so future computations begin from a known baseline.

Three essential questions guide every distributed-learning design: *What useful model change was attempted?* *How were data, compute and communication coordinated?* *What evidence supports the final claim?* A training protocol, a blockchain ledger and a model-evaluation procedure answer different questions.

## Worked practical example

For toy weight theta=2 and derivative g=0.5, an SGD step at rate 0.1 gives theta_new=2−0.1×0.5=1.95. This is only a local update, not the federation result.

A learner can reproduce the arithmetic using a calculator and study the relevant native C23 model-delta laboratory. Where a complete distributed protocol is not implemented, the example is explicitly a simulation or design exercise rather than a claim of running remote worker nodes.

## Build the conceptual model

1. Identify the starting model/checkpoint and what the worker actually receives.
2. Separate source permissions, sample counts and numerical parameters.
3. Name the expected output and its ownership: a delta, a candidate model or an evidence receipt.
4. Introduce one realistic failure: stale updates, packet loss, heterogeneous hardware, adversarial claims or evaluation leakage.
5. Decide what the native Framework can validate automatically and what demands a trusted reviewer or independent experiment.

## Think about privacy and trust

A source checksum, signature, network message and model-quality score are separate pieces of evidence. Private or financial data cannot be admitted for training merely because a worker has access to it. Federated learning does not, by itself, guarantee that a released update reveals nothing about local data.

## Self-assessment

**Question:** Why do workers need exact base-checkpoint agreement?

<details><summary>Reveal the answer and reasoning</summary>

A delta is relative to its own starting parameters; combining incompatible bases can produce meaningless results.

</details>

## Further reading

- [FedAvg — McMahan et al. (AISTATS 2017)](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Follow the connected course

[LLM Lesson 379](../10-native-ai/379-pin-model-dataset-and-training-round-identities.md) · [Mathematics learning route](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Distributed Learning course homepage](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
