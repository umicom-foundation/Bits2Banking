# Distributed Learning — Lesson 01: What a distributed training worker actually computes

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Track:** Introduction to Distributed Learning and Verifiable AI

## Learning objective

Explain **what a distributed training worker actually computes** in plain English, perform a small worked calculation or thought experiment, and distinguish a research hypothesis from a demonstrated system behaviour.

## Understand the idea

A learning worker receives an authorised example shard and the same model checkpoint as its collaborators. It tokenises, performs a forward pass, computes a loss, differentiates using the established training tape and takes local optimiser steps. Its output is a **weight update**, not a blockchain hash or a mere inference score.

Three essential questions guide every distributed-learning design: *What useful model change was attempted?* *How were data, compute and communication coordinated?* *What evidence supports the final claim?* A training protocol, a blockchain ledger and a model-evaluation procedure answer different questions.

## Worked practical example

One worker with 100 examples can compute a local scalar delta of +0.05 relative to base 1.000. A second worker’s delta must be expressed relative to the **same base** for straightforward FedAvg. The coordinator cannot infer honest computation just from reported values.

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

**Question:** Why is repeating a prompt-generation loop not the same as a training step?

<details><summary>Reveal the answer and reasoning</summary>

Inference does not derive a loss gradient or update the model parameters. Training changes weights under an explicit objective.

</details>

## Further reading

- [FedAvg — McMahan et al. (AISTATS 2017)](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Follow the connected course

[LLM Lesson 377](../10-native-ai/377-separate-distributed-learning-from-inference-scheduling.md) · [Mathematics learning route](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Distributed Learning course homepage](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
